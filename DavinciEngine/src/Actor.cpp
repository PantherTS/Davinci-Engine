#include "Actor.h"
#include "AIType.h"
#include "TXMLWrapper.h"
#include "XMLFileNode.h"
#include "TextureAtlas.h"
#include "Collision.h"
#include "Scene.h"

#include <string>
#include <algorithm>
#include <regex>
#include <cctype>

/************************************************************
* Actor Class												*
*	The Actor class is a subclass of the ActorType class. It*
*	is meant for all living objects throughout the game.	*
*	Every creature or living thing exists as an Actor object*
*	with vitals, a name, and an ID. Each Actor object that	*
*	is created is placed inside the SceneObjects storage	*
*	container.												*
************************************************************/

using namespace DavinciEngine;

// Class constructor
Actor::Actor() : m_pAIType(nullptr),m_pSprite(nullptr),m_pTextureAtlas(nullptr),m_pAttributes(nullptr)
{
}

// Class copy constructor
Actor::Actor(const Actor &other)
{
	Copy(*this,other);
}

// Class destructor
Actor::~Actor()
{
	if (m_pAttributes){
		delete m_pAttributes;
		m_pAttributes = nullptr;
	}
	if (m_pAIType){
		m_pAIType->Destroy();
		m_pAIType = nullptr;
	}
	if (m_pSprite)
	{
		delete m_pSprite;
		m_pSprite = nullptr;
	}
	if(m_pTextureAtlas){
		// Deleted when SpriteAnimation object was deleted.
		m_pTextureAtlas = nullptr;
	}
}

void Actor::Copy(Actor &newActor, const Actor &other)
{
	newActor.m_sActorType = other.m_sActorType;
	newActor.m_sObjectName = Scene::GetInstance()->GetNewID("Actor_" + other.m_sActorType);
	newActor.m_pAttributes = new Attributes(*other.m_pAttributes);
	newActor.m_pAIType = AIType::AI_GetAIType(other.m_pAIType->m_sName);
	newActor.CopyTags(other);
	newActor.m_pSprite = new SpriteAnimation(*other.m_pSprite);
	newActor.m_pTextureAtlas = newActor.m_pSprite->m_pTextureAtlas;
	newActor.SetCollider(other.GetCollider()->Clone());
	newActor.SetGraphic(newActor.m_pSprite);
	newActor.scale = other.scale;
	newActor.m_pInput = other.m_pInput;
	newActor.m_iLayer = other.m_iLayer;
	Log("Actor duplicated successfully for actor type [%s].",newActor.m_sActorType.c_str());
}

bool Actor::LoadActor(const char *actorType, float xPos, float yPos)
{
	Log("Loading new actor of [%s] type.",actorType);

	// Check for duplicate Actors present in the scene and create a copy if there is one.
	// This will save from having to reload the XML file over and over again.
	Actor *pActor = nullptr;
	pActor = dynamic_cast<Actor*>(&Scene::Duplicate(actorType));

	if(pActor == nullptr){
		pActor = new Actor();
		// Lowercase the incoming actorType so as not to have issues with LUA input.
		std::string file = actorType;
		std::transform(file.begin(), file.end(), file.begin(), ::tolower);
		// Try to load the XML file for the Actor here.
		std::string xmlPath = "../data/actors/" + file + ".xml";
		if( !pActor->LoadXML(xmlPath) ){
			delete pActor;
			pActor = nullptr;
			return false;
		}
		Log("XML file loaded successfully for Actor Type %s.",pActor->m_sActorType.c_str());
	}
	// Duplicate actor of same type found. Copy relevant data.
	else{
		pActor = new Actor(*pActor);
	}

	pActor->objectType = ACTOR;
	pActor->position.x = xPos;
	pActor->position.y = yPos;
	pActor->m_iLayer = 0;

	// Add the Actor object to the scene.
	Scene::GetInstance()->Add(pActor);

	return true;
}

bool Actor::LoadXML(std::string &xmlDocument)
{
	TXMLWrapper xmlObj(xmlDocument);

	// Process the XML file and load the Actor's information.
	if(xmlObj.m_bIsOpen){

		// Set or retrieve a unique name for the Actor.
		xmlObj.GetObjectName(&m_sActorType);
		std::regex aType("player",std::regex_constants::icase);
		if(std::regex_match(m_sActorType.begin(),m_sActorType.end(),aType)) {
			m_sObjectName = "Actor_Player";
		}
		else{
			m_sObjectName = Scene::GetInstance()->GetNewID("Actor_" + m_sActorType);
		}

		// Load Actor Attribute information.
		tinyxml2::XMLElement *xmlAttributes = xmlObj.GetRoot()->FirstChildElement("Attributes");
		if(xmlAttributes)
		{
			m_pAttributes = new Attributes();
			m_pAttributes->Load(xmlAttributes);
		}
		else{
			Warning("Attributes not loaded for Actor Type %s!",m_sActorType.c_str());
		}

		// Load Actor Tag information.
		tinyxml2::XMLElement *xmlTags = xmlObj.GetRoot()->FirstChildElement("Tags");
		if(xmlTags)
		{
			LoadTags(xmlTags);
			if(m_sActorType == "Player" && !HasTag("PLAYER")){
				Error("PLAYER tag must be defined for Actor Type Player!");
				return false;
			}
			else if(!HasTag("ACTOR")){
				Error("ACTOR tag must be defined for Actor Type %s!",m_sActorType.c_str());
				return false;
			}
		}

		// Load Actor AI information if not Player.
		if(m_sActorType != "Player")
		{
			m_pAIType = AIType::AI_GetAIType(m_pAttributes->GetAttribute<char*>("aitype"));
			if(m_pAIType == nullptr){
				Warning("AI information was not loaded for Actor Type %s!",m_sActorType.c_str());
				return false;
			}
		}

		// Load Actor Texture information.
		tinyxml2::XMLElement *xmlTextureAtlas = xmlObj.GetRoot()->FirstChildElement("TextureAtlas");
		if(xmlTextureAtlas)
		{
			m_pTextureAtlas = new TextureAtlas();
			m_pTextureAtlas->Load(xmlTextureAtlas);
		}
		else{
			Warning("TextureAtlas not loaded for Actor Type %s!",m_sActorType.c_str());
		}

		// Load Actor Animation information. Requires TextureAtlas.
		tinyxml2::XMLElement *xmlAnimations = xmlObj.GetRoot()->FirstChildElement("Animations");
		if(xmlAnimations && m_pTextureAtlas != nullptr)
		{
			m_pSprite = SpriteAnimation::Load(xmlAnimations,m_pTextureAtlas);
			// Replace default speed if there's one in the XML config for the Actor.
			float speed = m_pAttributes->GetAttribute<float>("speed");
			if(speed != 0){m_pSprite->m_fSpeed = speed;}
			SetGraphic(m_pSprite);
		}
		else{
			Warning("Animations not loaded for Actor Type %s!",m_sActorType.c_str());
		}

		// Load Actor Collision information.
		tinyxml2::XMLElement *xmlCollision = xmlObj.GetRoot()->FirstChildElement("Collision");
		if(xmlCollision)
		{
			SetCollider(Collider::Load(xmlCollision));
		}
		else{
			Warning("Collisions not loaded for Actor Type %s!",m_sActorType.c_str());
		}

		// Load Actor Input information.
		tinyxml2::XMLElement *xmlInputs = xmlObj.GetRoot()->FirstChildElement("Inputs");
		if(xmlInputs)
		{
			m_pInput = Input::GetInstance();		// Subscribe to Input Class
			LoadInputs(xmlInputs);
		}
		else{
			Warning("Inputs not loaded for Actor Type %s!",m_sActorType.c_str());
		}

		return true;
	}
	else{
		return false;
	}
}

TextureAtlas *Actor::GetTextureAtlas()
{
	return m_pTextureAtlas;
}

/************************************************************
* void Actor::Update()										*
*		Every frame the Actor is asked to update itself.	*
* These updates include things such as other Actor			*
* detection, Input checking, AI Routines, etc.				*
************************************************************/
void Actor::Update()
{
	if(m_pSprite->m_bIsMoving){
		Vec2D prePosition(position);
		m_pSprite->Move(position);
		CheckCollisions(prePosition);
	}
	
	DetectOthers();
	InputChecks();

	if(!HasTag("PLAYER")){
		AIRoutine();
	}

	m_pSprite->Animate();
}

void Actor::CheckCollisions(Vec2D &prePosition)
{
	if(Collide("ACTOR")){
		position = prePosition;
		m_pSprite->m_bIsMoving = false;
	}
}

/************************************************************
* void Actor::AIRoutine()									*
*		If the actor is not a player, this function controls*
* the AI movements and actions of the actor.				*
************************************************************/
void Actor::AIRoutine()
{
	if(!nearbyPawns.empty()){
		for(std::list<Object*>::iterator i = nearbyPawns.begin(); i != nearbyPawns.end(); i++){
			// Attack the player since actor is Hostile toward the player!
			//if(static_cast<Actor*>(*i)->m_pAIType->m_sAttitudeToPlayer == "HOSTILE"){
			if ((*i)->HasTag("PLAYER")) {
				// Try to move to center of where player sprite is. If collision occurs then stop.
				if (position.DistanceBetween((*i)->position) > 80) {
					m_pSprite->m_sCurrentAction = "walking";
					m_pSprite->MoveTo((*i)->position, position);
					break;
				}
				else {
					break;
				}
			}
		}
	}
}

/************************************************************
* void Actor::DetectOthers()								*
*		Check for Actors nearby and populate the			*
* m_mapNearbyActors map. May have an issue here if an actor	*
* is deleted during the population and Attitude check.		*
************************************************************/
void Actor::DetectOthers()
{
	nearbyPawns.clear();
	if(m_pScene != nullptr && !HasTag("PLAYER")){
		m_pScene->GetNearbyObjectTypes(nearbyPawns,this,m_pAIType->m_fDetectRange);
	}
}

/************************************************************
* void Actor::CheckAttitude(const Actor* otherActor)		*
*		Compare the present Actor object type to the Actor	*
* being tested found nearby. If they same type then return  *
* the attitude the nearby Actor has towards the caller.		*
* If the caller is the player then return the attitude the	*
* nearby Actor has towards the player. If the caller is not	*
* related and is not the player then return the nearby		*
* Actor's attitude to others.								*
************************************************************/
std::string Actor::CheckAttitude(const Actor *otherActor)
{
	if(otherActor != nullptr){
		// Check if the nearby Actor is a family member
		if(this->m_sActorType == otherActor->m_sActorType){
			return this->m_pAIType->m_sAttitudeToFamily;
		}
		else if(otherActor->m_sActorType == "Player"){
			return this->m_pAIType->m_sAttitudeToPlayer;
		}
		else{
			return this->m_pAIType->m_sAttitudeToOthers;
		}
	}
	else{
		// Return a blank std::string because the Actor has been deleted.
		return "";
	}
}

void Actor::InputChecks(){
	// If the Actor has no inputs then we don't want to waste our time here.
	if(!inputs.empty() || m_pInput == nullptr){
		if(m_pInput->IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			// Implement if clicked on map or this or other object checks here.
			if(HasTag("PLAYER")){
				// Movement Routine
				m_pSprite->m_sCurrentAction = inputs["MouseClickLeftMap"];
				m_pSprite->MoveTo(m_pInput->GetMousePosition(),position);
			}
		}
	}
}

void Actor::MouseLeftClick() 
{
	int x = 0;
}