#include "TXMLWrapper.h"

using namespace DavinciEngine;

//////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////

TXMLWrapper::TXMLWrapper() : hDoc(nullptr), hRoot(nullptr), m_pfileName(nullptr)  {

}

TXMLWrapper::TXMLWrapper(const std::string &documentName) : hDoc(nullptr), hRoot(nullptr), m_pfileName(documentName) {
	tinyxml2::XMLError const eResult = xmlDoc.LoadFile(documentName.c_str());
	if(eResult == tinyxml2::XML_SUCCESS){
		hDoc = tinyxml2::XMLHandle(&xmlDoc);
		m_bIsOpen = true;
	}
	else{
		DavinciEngine::Warning(xmlDoc.ErrorStr());
		m_bIsOpen = false;
	}
}

TXMLWrapper::~TXMLWrapper(){}

//////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////////////////////////////////////////////////////////////////////////

tinyxml2::XMLNode* TXMLWrapper::GetRoot(){
			tinyxml2::XMLNode* pRoot;
			hRoot = tinyxml2::XMLHandle(nullptr);

			pRoot = xmlDoc.FirstChildElement();

			// We should always have a valid root node.
			if (!pRoot){
				Error("XML file %s is not formatted correctly. There is a problem with the root node.", m_pfileName.c_str());
				return nullptr;
			}

			// Save the root handle.
			hRoot = tinyxml2::XMLHandle(pRoot);
			//pRoot = hRoot.ToElement();
			return pRoot;
}

void TXMLWrapper::GetObjectName(std::string *value){
	*value = this->GetRoot()->Value();
}

void TXMLWrapper::GetAttribute(const std::string &node, const std::string &attribute, int *value){
	//this->GetRoot()->FirstChildElement(node.c_str())->Attribute(attribute.c_str(), value);
}

void TXMLWrapper::GetAttribute(const std::string &node, const std::string &attribute, float *value){
	this->GetRoot()->FirstChildElement(node.c_str())->QueryFloatAttribute(attribute.c_str(), value);
}

void TXMLWrapper::GetAttribute(const std::string &node, const std::string &attribute, std::string *value){
	//this->GetRoot()->FirstChildElement(node.c_str())->QueryStringAttribute(attribute.c_str(), value);
}
