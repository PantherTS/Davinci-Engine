#include "Attribute.h"
#include "XMLFileNode.h"

using namespace DavinciEngine;

Attribute::Attribute() : m_pAttributes(nullptr), m_pAttribType(INVALID), m_sName("")
{

}

// Copy Constructor
Attribute::Attribute(const Attribute &other){
	
	//Need to copy attributes here! Detect type?
}

Attribute::Attribute(Attributes *attributes) : m_pAttributes(attributes), m_pAttribType(INVALID), m_sName("")
{

}

Attribute::Attribute(AttributeType type, std::string name, const int &value) : m_pAttribType(type), m_sName(name)
{
	baseAttrib.m_iValue = value;
}

Attribute::Attribute(AttributeType type, std::string name, char *&value) : m_pAttribType(type), m_sName(name)
{
	baseAttrib.m_pcValue = _strdup(value);
}

Attribute::Attribute(AttributeType type, std::string name, const float &value) : m_pAttribType(type), m_sName(name)
{
	baseAttrib.m_fValue = value;
}

Attribute::Attribute(AttributeType type, std::string name, const double &value) : m_pAttribType(type), m_sName(name)
{
	baseAttrib.m_dValue = value;
}

void Attribute::Save(FileNode *fileNode)
{
	fileNode->Write("type",m_pAttribType);
	fileNode->Write("name",m_sName);
	switch (m_pAttribType)
	{
	case INT:
		fileNode->Write("value",baseAttrib.m_iValue);
		break;
	case CHARACTER:
		fileNode->Write("value",*baseAttrib.m_pcValue);
		break;
	case FLOAT:
		fileNode->Write("value",baseAttrib.m_fValue);
		break;
	case DOUBLE:
		fileNode->Write("value",baseAttrib.m_dValue);
		break;
	default :
		break;
	}
}

void Attribute::Load(FileNode *fileNode)
{
	fileNode->Read("name", m_sName);
	//switch the values here
	switch (m_pAttribType)
	{
	case INT:{
		fileNode->Read("value",baseAttrib.m_iValue);
		break;}
	case CHARACTER:{
		fileNode->Read("value",baseAttrib.m_pcValue);
		break;}
	case FLOAT:{
		fileNode->Read("value",baseAttrib.m_fValue);
		break;}
	case DOUBLE:{
		fileNode->Read("value",baseAttrib.m_dValue);
		break;}
	default:
		break;
	}
}

Attributes::Attributes(){

}

Attributes::Attributes(const Attributes &other){
	for(auto i = other.entries.begin() ; i != other.entries.end(); i++){
		std::string attribName = i->first;
		Attribute* attribute = nullptr;
		switch (i->second->m_pAttribType)
		{
		case INT:{
			attribute = new Attribute(i->second->m_pAttribType,i->first,i->second->baseAttrib.m_iValue);
			break;}
		case CHARACTER:{
			attribute = new Attribute(i->second->m_pAttribType,i->first,i->second->baseAttrib.m_pcValue);
			break;}
		case FLOAT:{
			attribute = new Attribute(i->second->m_pAttribType,i->first,i->second->baseAttrib.m_fValue);
			break;}
		case DOUBLE:{
			attribute = new Attribute(i->second->m_pAttribType,i->first,i->second->baseAttrib.m_dValue);
			break;}
		default:
			break;
		}

		if(attribute != nullptr)
			entries.insert(std::pair<std::string,Attribute*>(attribName,attribute));
	}
}

Attributes::~Attributes(){
	std::map<std::string,Attribute*>::iterator it = entries.begin();
	while (it != entries.end())
	{
		if(it->second->m_pAttribType == CHARACTER){
			free((char*)it->second->baseAttrib.m_pcValue);
		}
		delete it->second;
		it->second = nullptr;
		entries.erase(it++);
	}
	entries.clear();
} 

bool Attributes::SetAttribute(const std::string &name, const int &value)
{
	Attribute *att = entries[name];
	att->baseAttrib.m_iValue = value;
	return true;
}

bool Attributes::SetAttribute(const std::string &name, char *&value)
{
	Attribute *att = entries[name];
	att->baseAttrib.m_pcValue = value;
	return true;
}

bool Attributes::SetAttribute(const std::string &name, const float &value)
{
	Attribute *att = entries[name];
	att->baseAttrib.m_fValue = value;
	return true;
}

bool Attributes::SetAttribute(const std::string &name, const double &value)
{
	Attribute *att = entries[name];
	att->baseAttrib.m_dValue = value;
	return true;
}

void Attributes::Save(tinyxml2::XMLDocument *document)
{
	tinyxml2::XMLElement * xmlAttributes = document->NewElement("Attributes");

	for (std::map<std::string, Attribute*>::iterator i = entries.begin(); i != entries.end(); ++i)
	{
		Attribute *attributeEntry = (*i).second;

		tinyxml2::XMLElement * xmlAttributeEntry = document->NewElement("AttributeEntry");
		XMLFileNode xmlFileNode(xmlAttributeEntry);
		attributeEntry->Save(&xmlFileNode);

		xmlAttributes->InsertEndChild(xmlAttributeEntry);
	}

	document->InsertEndChild(xmlAttributes);
}

void Attributes::Load(tinyxml2::XMLElement *element)
{
	tinyxml2::XMLElement *xmlAttributeEntry = element->FirstChildElement("AttributeEntry");
	while (xmlAttributeEntry)
	{
		XMLFileNode xmlFileNode(xmlAttributeEntry);

		Attribute *attributeEntry = new Attribute(this);
		
		attributeEntry->m_pAttribType = static_cast<AttributeType>(xmlAttributeEntry->IntAttribute("type"));

		attributeEntry->Load(&xmlFileNode);
		if (attributeEntry->m_sName != "")
			entries[attributeEntry->m_sName] = attributeEntry;

		xmlAttributeEntry = xmlAttributeEntry->NextSiblingElement("AttributeEntry");
	}
}