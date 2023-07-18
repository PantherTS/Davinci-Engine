#include "XMLFileNode.h"
#include <sstream>
#include "Vec2D.h"
#include <format>

using namespace DavinciEngine;

XMLFileNode::XMLFileNode()
	: element(nullptr)
{

}

XMLFileNode::XMLFileNode(tinyxml2::XMLElement *element)
	: element(element)
{

}

/// WRITE
void XMLFileNode::Write(const std::string &name, const int &value)
{
	element->SetAttribute(name.c_str(), value);
}

void XMLFileNode::Write(const std::string &name, const float &value)
{
	element->SetAttribute(name.c_str(), value);
}

void XMLFileNode::Write(const std::string &name, const double &value)
{
	element->SetAttribute(name.c_str(), value);
}

void XMLFileNode::Write(const std::string &name, const std::string &value)
{
	element->SetAttribute(name.c_str(), value.c_str());
}

void XMLFileNode::Write(const std::string &name, const char *&value)
{
	element->SetAttribute(name.c_str(), value);
}

void XMLFileNode::Write(const std::string& name, const Vec2D& value)
{
	std::string buffer = std::format("{} {}", value.x, value.y);
	element->SetAttribute(name.c_str(), buffer.c_str());
}

//void XMLFileNode::Write(const std::string &name, const Color &value)
//{
//	std::ostringstream os;
//	os << value.r << " " << value.g << " " << value.b << " " << value.a;
//	element->SetAttribute(name, os.str());
//}

void XMLFileNode::Write(const std::string &name, const bool &value)
{
	element->SetAttribute(name.c_str(), (int)value);
}


/// READ
void XMLFileNode::Read(const std::string &name, int &value)
{
	if (element->Attribute(name.c_str()))
	{
		element->QueryIntAttribute(name.c_str(), &value);
	}
}

void XMLFileNode::Read(const std::string &name, float &value)
{
	if (element->Attribute(name.c_str()))
	{
		element->QueryFloatAttribute(name.c_str(), &value);
	}
}

void XMLFileNode::Read(const std::string &name, double &value)
{
	if(element->Attribute(name.c_str()))
	{
		element->QueryDoubleAttribute(name.c_str(), &value);
	}
}

void XMLFileNode::Read(const std::string &name, char *&value)
{
	if (element->Attribute(name.c_str()))
	{
		value = _strdup(element->Attribute(name.c_str()));
	}
}

void XMLFileNode::Read(const std::string &name, std::string &value)
{
	if (element->Attribute(name.c_str()))
	{
		value = element->Attribute(name.c_str());
	}
}

void XMLFileNode::Read(const std::string &name, Vec2D &value)
{
	if (element->Attribute(name.c_str()))
	{
		std::istringstream read(element->Attribute(name.c_str()));
		read >> value.x >> value.y;
	}
}

//void XMLFileNode::Read(const std::string &name, Color &value)
//{
//	if (element->Attribute(name))
//	{
//		std::string string = *element->Attribute(name);
//		std::istringstream read(string);
//		if (string.find('#') != std::string::npos)
//		{
//			// TODO: read hex color
//		}
//		else
//		{
//			read >> value.r >> value.g >> value.b >> value.a;
//		}
//	}
//}

void XMLFileNode::Read(const std::string &name, bool &value)
{
	if (element->Attribute(name.c_str()))
	{
		element->QueryBoolAttribute(name.c_str(), &value);
	}
}