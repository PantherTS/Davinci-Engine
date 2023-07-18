#ifndef FILENODE_H
#define FILENODE_H

#include <string>

namespace DavinciEngine
{
	class Vec2D;
	//class Color;

	class FileNode
	{
	public:
		virtual void Write(const std::string &name, const int &value)=0;
		virtual void Write(const std::string &name, const float &value)=0;
		virtual void Write(const std::string &name, const double &value)=0;
		virtual void Write(const std::string &name, const char *&value)=0;
		virtual void Write(const std::string &name, const std::string &value)=0;
		virtual void Write(const std::string &name, const Vec2D &value)=0;
		//virtual void Write(const std::string &name, const Color &value)=0;
		virtual void Write(const std::string &name, const bool &value)=0;

		virtual void Read(const std::string &name, int &value)=0;
		virtual void Read(const std::string &name, float &value)=0;
		virtual void Read(const std::string &name, double &value)=0;
		virtual void Read(const std::string &name, char *&value)=0;
		virtual void Read(const std::string &name, std::string &value)=0;
		virtual void Read(const std::string &name, Vec2D &value)=0;
		//virtual void Read(const std::string &name, Color &value)=0;
		virtual void Read(const std::string &name, bool &value)=0;
	};
}
#endif