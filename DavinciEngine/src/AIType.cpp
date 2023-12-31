#include "AIType.h"
#include "LowLevelSystem.h"
#include "TXMLWrapper.h"
#include "tinyxml2.h"

namespace DavinciEngine{

	int AIType::AICount = 0;
	bool AIType::m_bAILoaded = false;
	std::map<const std::string, AIType*> AIType::m_mapAITypes;
	std::map<const std::string, AIType*>::iterator AIType::m_mapAITypesIter;

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	AIType::AIType() : m_fDetectRange(NULL),m_fFollowRange(NULL),m_fRoamRange(NULL) {}

	// Copy Constructor
	AIType::AIType(const AIType& orig){
		m_sName = orig.m_sName;
		m_sAttitudeToFamily = orig.m_sAttitudeToFamily;
		m_sAttitudeToOthers = orig.m_sAttitudeToOthers;
		m_sAttitudeToPlayer = orig.m_sAttitudeToPlayer;
		m_fDetectRange = orig.m_fDetectRange;
		m_fFollowRange = orig.m_fFollowRange;
		m_fRoamRange = orig.m_fRoamRange;
	}

	AIType::~AIType(){
	}

	void AIType::Destroy()
	{
		AICount--;
		if(AICount == static_cast<int>(m_mapAITypes.size())){
			m_mapAITypesIter = m_mapAITypes.begin();
			while(m_mapAITypesIter != m_mapAITypes.end()){
				delete m_mapAITypesIter->second;
				m_mapAITypes.erase(m_mapAITypesIter++);
				AICount--;
			}
			m_bAILoaded = false;
		}
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	bool AIType::AI_Load( const char* filename)
	{
		// Add loading statement to engine log.
		Log("Loading AITypes from: %s", filename);

		// Retrieve the AIType properties from the given file and store it in the AITypes map.
		if(AI_LoadProps(filename)){
			m_bAILoaded = true;
			return true;
		}
		else{
			m_bAILoaded = false;
			return false;
		}
	}

	AIType* AIType::AI_GetAIType(const std::string &AITypeName)
	{
		m_mapAITypesIter = m_mapAITypes.find(AITypeName);

		if(m_mapAITypesIter != m_mapAITypes.end()){
			AICount++;
			return new AIType(*m_mapAITypesIter->second);
		}
		else{
			if(!m_bAILoaded && AI_Load("../data/ai/aitypes.xml")){
				return AI_GetAIType(AITypeName);
			}
			Error("AITypes could not be loaded from ../data/ai/aitypes.xml.");
			return nullptr;
		}
	}

	void AIType::AI_SetProps(const float detectRange,const float followRange,const float roamRange, const char* attitudeToPlayer,const char* attitudeToFamily,const char* attitudeToOthers)
	{
		m_fDetectRange = detectRange;
		m_fFollowRange = followRange;
		m_fRoamRange = roamRange;
		m_sAttitudeToPlayer = attitudeToPlayer;
		m_sAttitudeToFamily = attitudeToFamily;
		m_sAttitudeToOthers = attitudeToOthers;
	}

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHODS
	//////////////////////////////////////////////////////////////////////////

	bool AIType::AI_LoadProps(const char* fileName){
		if(Verify_Exists(fileName,false)){

			TXMLWrapper xmlObj(fileName);
			tinyxml2::XMLElement* pElem = nullptr;
			pElem = xmlObj.GetRoot()->FirstChild()->ToElement();

			// Load All AIType information.
			for( pElem; pElem; pElem = pElem->NextSiblingElement() ){
				AIType *p_AIType = new AIType();
				p_AIType->m_sName = pElem->Value();
				p_AIType->m_sAttitudeToFamily = pElem->Attribute("attitude_to_family");
				p_AIType->m_sAttitudeToOthers = pElem->Attribute("attitude_to_others");
				p_AIType->m_sAttitudeToPlayer = pElem->Attribute("attitude_to_player");
				pElem->QueryFloatAttribute("detect_range",&p_AIType->m_fDetectRange);
				pElem->QueryFloatAttribute("follow_range",&p_AIType->m_fFollowRange);
				pElem->QueryFloatAttribute("roam_range",&p_AIType->m_fRoamRange);

				AICount++;

				// Store the AIType in the AIType Map for later retrieval.
				m_mapAITypes.insert(std::pair<const std::string,AIType*>(static_cast<const std::string>(p_AIType->m_sName),p_AIType));
			}
			return true;
		}
		else{
			// File was not found.  Return false to cancel Actor creation.
			return false;
		}
	}
};
