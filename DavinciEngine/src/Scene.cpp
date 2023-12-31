#include "Scene.h"
#include "Timer.h"
#include "Graphic.h"

using namespace DavinciEngine;

Scene *Scene::m_pScene;
std::map<std::string,Object*> Scene::SceneObjects;
std::multimap<int,Object*> Scene::LayeredSceneObjects;
std::map<std::string,Object*> Scene::toAdd;
std::map<std::string,Object*> Scene::toRemove;
std::map<std::string, std::list<Object*> > Scene::tagMap;
std::list<Camera*> Scene::cameras;

// Class constructor
Scene::Scene() : m_pWindow(Window::GetInstance()),m_pGUI(GUI::GetInstance()), m_bIsVisible(true)
{
	Camera *camera = new Camera();
	camera->position = m_pWindow->GetWindowCenter();
	AddCamera(camera);
}

// Class destructor
Scene::~Scene()
{
	SceneObjects.clear();
	DestroyAllCameras();
}

// Class Singleton reference
Scene *Scene::GetInstance(){
	if (!m_pScene){
		m_pScene = new Scene();
	}
	return m_pScene;
}

void Scene::Destroy(){
	if(m_pScene){
		m_pScene->ClearScene();
		m_pScene->ResolveObjectChanges();
		delete m_pScene;
		m_pScene = nullptr;
	}
}

void Scene::Add(Object *object)
{
	if (object)
	{
		if (object->m_pScene != nullptr)
		{
			Error("Trying to add an Object to a Scene, but the Object is already in a Scene!");
		}
		else
		{
			toAdd.insert(std::pair<std::string, Object*>(object->GetName(), object));
			UpdateLayerList(object, false);
		}
	}
}

void Scene::Remove(Object *object)
{
	if (object)
	{
		if (object->m_pScene == nullptr)
		{
			Error("Trying to remove an Object from the Scene, but the Object is not in the Scene!");
		}
		else
		{
			toRemove.insert(std::pair<std::string, Object*>(object->GetName(), object));
			UpdateLayerList(object, true);
		}
	}
}

void Scene::UpdateLayerList(Object *object, bool remove)
{
	if(!remove){
		LayeredSceneObjects.insert(std::pair<int,Object*>(object->m_iLayer, object));
	}
	else{
		std::multimap<int,Object*>::iterator i = LayeredSceneObjects.find(object->m_iLayer);
	
		while(i != LayeredSceneObjects.end() && (i->second != object || i->second->m_iLayer != object->m_iLayer))
		{
			i++;
		}
		LayeredSceneObjects.erase(i);
	}
}

Object& Scene::Duplicate(const std::string &objectType){
	Object *m_pObject = nullptr;
	std::regex oType(objectType,std::regex_constants::icase);

	for(auto i = toAdd.begin(); i != toAdd.end(); ++i){
		if(std::regex_match(i->second->GetType().begin(),i->second->GetType().end(),oType)){
			m_pObject = i->second;
			break;
		}
	}
	if(m_pObject == nullptr) {
		for(auto i = SceneObjects.begin(); i != SceneObjects.end(); ++i){
			if(std::regex_match(i->second->GetType().begin(),i->second->GetType().end(),oType)){
				m_pObject = i->second;
				break;
			}
		}
	}
	return *m_pObject;
}

void Scene::Update(){

	if (!Timer::GetInstance()->is_paused())
	{
		//Update all the Scene Objects.
		for (auto i = SceneObjects.begin(); i != SceneObjects.end(); ++i)
		{
			i->second->Update();
		}
	}

	//Resolve adds and removes
	ResolveObjectChanges();
}

void Scene::Render(){
	if (m_bIsVisible)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();
		glScalef(m_pWindow->GetWindowScale().x, m_pWindow->GetWindowScale().y, 0.0f);
		glTranslatef(m_pWindow->GetWindowCenter().x, m_pWindow->GetWindowCenter().y, 0.0f);

		//Render all the Objects based on their layer

		constexpr int MAX_LAYER = 100;
		constexpr int MIN_LAYER = -100;

		for (std::list<Camera*>::iterator camera = cameras.begin(); camera != cameras.end(); ++camera)
		{
			// Push the Camera matrix.
			glPushMatrix();
			(*camera)->ApplyMatrix();
			
			// Render according to the layer of the Objects in the scene.(Highest to Lowest)
			for (int layer = MAX_LAYER; layer >= MIN_LAYER; layer--)
			{
				std::multimap<int,Object*>::iterator i = LayeredSceneObjects.find(layer);
				while(i != LayeredSceneObjects.end() && i->first == layer){
					i->second->Render();
					i++;
				}
			}
			// Pop the Camera matrix.
			glPopMatrix();
		}
		// Show the buffered surface
		SDL_GL_SwapWindow(m_pWindow->m_pScreen);
	}
}

void Scene::ClearScene(){
	for (auto i = SceneObjects.begin(); i != SceneObjects.end(); ++i)
		Remove(i->second);
}

void Scene::ResolveObjectChanges(){
	
	//Resolve removes from the scene
	std::map<std::string,Object*>::iterator i = toRemove.begin();

	while (i != toRemove.end())
	{
		//If the tag is set, remove the entity from the tag map
		for (int j = 0; j < i->second->GetNumberOfTags(); ++j)
			ObjectRemoveTag(i->second, i->second->GetTag(j));
		
		i->second->m_pScene = nullptr;
		SceneObjects.erase(i->first);
		// May add virtual Removed function back in if I need to perform an action after an Object is removed from the scene.
		//i->second->Removed();
		delete i->second;

		toRemove.erase(i++);
	}
	toRemove.clear();

	//Resolve additions to the scene
	for (auto it = toAdd.begin(); it != toAdd.end(); ++it)
	{
		SceneObjects.insert(std::pair<std::string,Object*>(it->first,it->second));

		//If the tag is set, add the entity to the tag map
		for (int j = 0; j < it->second->GetNumberOfTags(); ++j)
			ObjectAddTag(it->second, it->second->GetTag(j));

		it->second->m_pScene = this;
		// May add virtual Added function back in if I need to perform an action after an Object is added to the scene.
		//i->second->Added();
	}
	toAdd.clear();
}

void Scene::GetNearbyObjectTypes(std::list<Object*> &objects,Object* otherObject, float range)
{
	for(auto i = SceneObjects.begin(); i != SceneObjects.end(); ++i)
	{
		if(i->second != otherObject && i->second->objectType == otherObject->objectType){
			if(i->second->position.DistanceBetween(otherObject->position) < range)
			{
				objects.push_back(i->second);
			}
		}
	}
}

std::string Scene::GetNewID(std::string objectType){

	std::string objectName;
	std::stringstream ss;
	std::string temp;
	int next_integer = 0;

	do{
		next_integer++;
		ss.clear();
		ss << next_integer;
		ss >> temp;
		objectName = objectType;
		objectName += "_";
		objectName += temp;
	} while ((toAdd.find(objectName) != toAdd.end()) || (SceneObjects.find(objectName) != SceneObjects.end()));

	return objectName;
}

bool Scene::VerifyExists(const std::string& objectName){
	auto it = SceneObjects.find(objectName);
	if(it == SceneObjects.end()){
		return false;
	}
	else{
		return true;
	}
}

Object& Scene::GetPlayer(){
	// Search the SceneObjects map to find the player object
	auto it = SceneObjects.find("Actor_Player");
	if (it == SceneObjects.end()) throw std::invalid_argument("entry not found");
	return *(it->second);
}

void Scene::ObjectAddTag(Object* object, const std::string& tag)
{
	tagMap[tag].push_back(object);
}

void Scene::ObjectRemoveTag(Object *object, const std::string& tag)
{
	tagMap[tag].remove(object);
}

Object* Scene::GetFirstTag(const std::string& tag)
{
	if (tagMap.count(tag) == 0 || tagMap[tag].size() == 0)
		return nullptr;

	return tagMap[tag].front();
}

std::list<Object*> *Scene::GetAllTags(const std::string& tag)
{
	if (tagMap.count(tag) == 0)
		return nullptr;
	else
		return &tagMap[tag];
}

const int Scene::GetTagCount(const std::string& tag)
{
	if (tagMap.count(tag) == 0) 
		return 0;

	return static_cast<int>(tagMap[tag].size());
}

void Scene::AddCamera(Camera *camera)
{
	cameras.push_back(camera);
}

const Camera *Scene::GetCamera(int cameraIndex)
{
	constexpr int c = 0;
	for (std::list<Camera*>::iterator i = cameras.begin(); i != cameras.end(); i++)
	{
		if (c == cameraIndex)
			return *i;
	}
	return nullptr;
}

void Scene::DestroyAllCameras()
{
	for (std::list<Camera*>::iterator i = cameras.begin(); i != cameras.end(); i++)
	{
		delete *i;
	}
	cameras.clear();
}