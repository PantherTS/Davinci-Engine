#ifndef TXMLWRAPPER_H
#define TXMLWRAPPER_H

#include "tinyxml2.h"
#include "LowLevelSystem.h"
#include <string>
#include <charconv>
// Objects that this class can populate via pointers to the objects:
#include "Object.h"

namespace DavinciEngine{
	class TXMLWrapper{
	public:
		TXMLWrapper();
		TXMLWrapper(const std::string &documentName);
		~TXMLWrapper();
		tinyxml2::XMLNode *GetRoot();
		void GetObjectName(std::string *value);
		void GetAttribute(const std::string &node, const std::string &attribute, int *value);
		void GetAttribute(const std::string &node, const std::string &attribute, float *value);
		void GetAttribute(const std::string &node, const std::string &attribute, std::string *value);

		bool m_bIsOpen;

	private:
		const std::string m_pfileName;	// The filename for the XML document.
		tinyxml2::XMLDocument xmlDoc;	// DOM for XML document.
		tinyxml2::XMLHandle hDoc;		// Handle to XML document.
		tinyxml2::XMLHandle hRoot;		// Handle to XML document root node.
	};
}
#endif