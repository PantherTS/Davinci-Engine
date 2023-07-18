#ifndef XMLFILENODE_H
#define XMLFILENODE_H

#include "FileNode.h"
#include "SystemTypes.h"
#include "tinyxml2.h"

namespace DavinciEngine
{
	class XMLFileNode : public FileNode
	{
	public:
		XMLFileNode();
		XMLFileNode(tinyxml2::XMLElement *element);

		void Write(const std::string &name, const int &value);
		void Write(const std::string &name, const float &value);
		void Write(const std::string &name, const double &value);
		void Write(const std::string &name, const char *&value);
		void Write(const std::string &name, const std::string &value);
		void Write(const std::string &name, const Vec2D &value);
		//void Write(const std::string &name, const Color &value);
		void Write(const std::string &name, const bool &value);

		void Read(const std::string &name, int &value);
		void Read(const std::string &name, float &value);
		void Read(const std::string &name, double &value);
		void Read(const std::string &name, char *&value);
		void Read(const std::string &name, std::string &value);
		void Read(const std::string &name, Vec2D &value);
		//void Read(const std::string &name, Color &value);
		void Read(const std::string &name, bool &value);

		tinyxml2::XMLElement *element;
	};
}
#endif