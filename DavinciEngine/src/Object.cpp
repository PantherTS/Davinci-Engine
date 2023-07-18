#include "Object.h"
#include "Collision.h"
#include "Graphic.h"
#include "FileNode.h"
#include "XMLFileNode.h"
#include "Scene.h"

namespace DavinciEngine{

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	Object::Object() : Transform(), m_pInput(nullptr), m_pGraphic(nullptr), m_pCollider(nullptr), m_pCollision(Collision::GetInstance()), m_bIsEnabled(true), m_pScene(nullptr), m_fDepth(0.0f), m_bIsVisible(true)
	{
	}

	Object::~Object()
	{
		if (m_pCollider)
		{
			m_pCollision->RemoveCollider(m_pCollider);
			delete m_pCollider;
			m_pCollider = nullptr;
			m_pCollision->Destroy();
			m_pCollision = nullptr;
		}
		if (m_pGraphic)
		{
			m_pGraphic = nullptr;
		}
		this->Destroy();
	}

	void Object::Destroy()
	{
		if (m_pScene) {
			m_pScene->Remove(this);
			m_pScene = nullptr;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	/************************************************************
	* void Object::MouseEvent(float mX, float mY, float relX,	*
	*	float relY, bool Left,bool Right,bool Middle)			*
	*		Processes a mouse event made on the object and calls*
	*	the corresponding virtual/non-virtual method to finish	*
	*	processing the event.									*
	************************************************************/
	//void Object::MouseEvent(float mX, float mY, float relX, float relY, bool Left,bool Right,bool Middle){
	//	if( this->active == true && this->visible == true){
	//		if( ( mX > this->pos.x ) && ( mX < this->pos.x + this->width ) &&
	//			( mY > this->pos.y ) && ( mY < this->pos.y + this->height ) ){
	//				this->mouseOver = true;
	//				this->MouseOver(true);
	//				if( Left == true){
	//					this->leftMouseClicked = true;
	//				}
	//				else if( Right == true){
	//					this->rightMouseClicked = true;
	//				}
	//				else if( Middle == true){
	//
	//				}
	//		}
	//		else{
	//			this->mouseOver = false;
	//			this->MouseOver(false);
	//		}
	//	}
	//	else{
	//		this->mouseOver = false;
	//	}
	//}

	/************************************************************
	* void Object::Deactivate()								*
	*		Iterates through the GameObject map containing		*
	*	all loaded objects and sets the active boolean of		*
	*	all or ones matching objectName to false.				*
	************************************************************/
	void Object::Disable()
	{
		this->m_bIsEnabled = false;
	}

	void Object::OnAdd()
	{

	}

	void Object::OnRemove()
	{

	}

	void Object::Enable()
	{
		this->m_bIsEnabled = true;
	}

	void Object::Render()
	{
		glPushMatrix();

		if (m_vec2FollowCamera == Vec2D::zero){
			m_fDepth = 0.0f;
			glTranslatef(position.x, position.y, m_fDepth);
		}
		else
			glTranslatef((m_pScene->GetCamera()->position * m_vec2FollowCamera + position * (Vec2D::one - m_vec2FollowCamera)).x, (m_pScene->GetCamera()->position * m_vec2FollowCamera + position * (Vec2D::one - m_vec2FollowCamera)).y, m_fDepth);

		if (rotation != 0.0f)
			glRotatef(rotation, 0, 0, 1);

		glScalef(scale.x, scale.y, 1.0f);

		if (m_pGraphic != nullptr)
		{
			//Graphics::SetColor(color);
			m_pGraphic->Render();
		}

		glPopMatrix();
	}

	/************************************************************
	* void Object::Update()								*
	*		Virtual method used by derived classes to perform	*
	*	all requested tasks. This method is called once per		*
	*	frame for each object loaded in the GameObjects map.	*
	************************************************************/
	void Object::Update()
	{
		// Virtual function
	}

	const bool Object::IsEnabled()
	{
		return m_bIsEnabled;
	}

	void Object::SetGraphic(Graphic* graphic)
	{
		if (graphic == nullptr && this->m_pGraphic != nullptr)
		{
			//this->m_pGraphic->entity = NULL;
		}

		if (this->m_pGraphic != nullptr)
		{
			Error("Object %s has already been assigned a graphic.",m_sObjectName.c_str());
		}
		else
		{
			Log("Object %s has been assigned a graphic.",m_sObjectName.c_str());
			this->m_pGraphic = graphic;
		}
	}

	void Object::SetCollider(Collider *collider)
	{
		if (collider == nullptr && m_pCollider != nullptr)
		{
			Collision::GetInstance()->RemoveCollider(collider);
			collider = nullptr;
		}
		else if (m_pCollider != nullptr)
		{
			Error("Object %s already has a collider.",m_sObjectName.c_str());
		}
		else
		{
			m_pCollider = collider;
			Collision::GetInstance()->RegisterColliderWithObject(collider, this);
		}
	}

	Collider *Object::GetCollider() const
	{
		return m_pCollider;
	}

	Collider* Object::Collide(const std::string &tag, CollisionData *collisionData)
	{
		return Collision::GetInstance()->Collide(this, tag, collisionData);
	}

	const std::string& Object::GetTag(int index)
	{
		return tags[index];
	}

	void Object::AddTag(const std::string& tag)
	{
		if (!HasTag(tag))
		{
			tags.push_back(tag);
			if (m_pScene != nullptr)
				m_pScene->ObjectAddTag(this, tag);
		}
	}

	void Object::RemoveTag(const std::string& tag)
	{
		for (std::vector<std::string>::iterator i = tags.begin(); i != tags.end(); ++i)
		{
			if ((*i).compare(tag) == 0)
			{
				tags.erase(i);
				break;
			}
		}
		if (m_pScene != nullptr)
			m_pScene->ObjectRemoveTag(this, tag);
	}

	const bool Object::HasTag(const std::string& tag)
	{
		for (std::vector<std::string>::iterator i = tags.begin(); i != tags.end(); ++i)
		{
			if ((*i).compare(tag) == 0)
				return true;
		}

		return false;
	}

	const int Object::GetNumberOfTags()
	{
		return static_cast<int>(tags.size());
	}

	void Object::SaveTags(tinyxml2::XMLDocument *document)
	{
		if (document)
		{
			tinyxml2::XMLElement* xmlTags = document->NewElement("Tags");
			if (xmlTags) {
				for (std::vector<std::string>::iterator i = tags.begin(); i != tags.end(); ++i)
				{
					tinyxml2::XMLElement* xmlTagEntry = document->NewElement("TagEntry");
					XMLFileNode xmlFileNode(xmlTagEntry);
					xmlFileNode.Write("name", (*i));
					xmlTags->InsertEndChild(xmlTagEntry);
				}
				document->InsertEndChild(xmlTags);
			}
		}
		else { FatalError("Object:SaveTags() - XMLDocument cannot be written to."); }
	}

	void Object::LoadTags(tinyxml2::XMLElement *element)
	{
		if (element)
		{
			tinyxml2::XMLElement* xmlTagEntry = element->FirstChildElement("TagEntry");
			while (xmlTagEntry)
			{
				std::string name = "";
				XMLFileNode xmlFileNode(xmlTagEntry);
				xmlFileNode.Read("name", name);
				AddTag(name);
				xmlTagEntry = xmlTagEntry->NextSiblingElement("TagEntry");
			}
		}
		else { FatalError("Object:LoadTags() - XMLElement cannot be loaded from."); }
	}

	void Object::CopyTags(const Object &other)
	{
		for(int i = 0; i < static_cast<int>(other.tags.size()); i++)
		{
			this->tags.push_back(other.tags[i]);
		}
	}

	void Object::InputChecks()
	{
		// Virtual Function
	}

	void Object::LoadInputs(tinyxml2::XMLElement *element)
	{
		if (element)
		{
			tinyxml2::XMLElement* xmlInputEntry = element->FirstChildElement("InputEntry");
			while (xmlInputEntry)
			{
				std::string name = "";
				std::string action = "";
				XMLFileNode XMLFileNode(xmlInputEntry);
				XMLFileNode.Read("name", name);
				XMLFileNode.Read("action", action);
				inputs.insert(std::pair<std::string, std::string>(name, action));
				xmlInputEntry = xmlInputEntry->NextSiblingElement("InputEntry");
			}
		}
		else { FatalError("Object:LoadTags() - XMLElement cannot be loaded from."); }
	}
}