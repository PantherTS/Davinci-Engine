#include "TextureAtlas.h"
#include "XMLFileNode.h"
#include <sstream>

using namespace DavinciEngine;

TextureAtlasEntry::TextureAtlasEntry()
{
}

TextureAtlasEntry::TextureAtlasEntry(TextureAtlas *textureAtlas)
	: textureAtlas(textureAtlas)
{
}

int TextureAtlasEntry::GetWidth() const
{
	return width;
}

int TextureAtlasEntry::GetHeight() const
{
	return height;
}

glm::vec2 TextureAtlasEntry::GetTextureOffset()
{
	return glm::vec2(x/float(textureAtlas->width), y/float(textureAtlas->height));
}

glm::vec2 TextureAtlasEntry::GetTextureScale()
{
	return glm::vec2(width/static_cast<float>(textureAtlas->width), height/static_cast<float>(textureAtlas->height));
}

void TextureAtlasEntry::Save(FileNode *fileNode) const
{
	fileNode->Write("name", name);
	std::ostringstream os;
	os << x << " " << y << " " << width << " " << height;
	fileNode->Write("coords", os.str());
}

void TextureAtlasEntry::Load(FileNode *fileNode)
{
	fileNode->Read("name", name);
	std::string read;
	fileNode->Read("coords", read);
	std::istringstream is(read);
	is >> x >> y >> width >> height;
}

TextureAtlas::TextureAtlas()
	: width(0), height(0), m_iRefCount(0)
{
}

TextureAtlas::~TextureAtlas()
{
}

void TextureAtlas::Destroy()
{
	if(m_iRefCount == 0){
		std::map<std::string, TextureAtlasEntry*>::iterator it = entries.begin();
		while( it != entries.end() )
		{
			delete it->second;
			it->second = nullptr;
			entries.erase(it++);
		}
		entries.clear();
		delete this;
	}
	else{
		RemoveReference();
	}
}

TextureAtlas *TextureAtlas::GetReference(){
	AddReference();
	return this;
}

void TextureAtlas::AddReference(){
	m_iRefCount++;
}

void TextureAtlas::RemoveReference(){
	m_iRefCount--;
}

TextureAtlasEntry *TextureAtlas::GetEntryByName(const std::string &name)
{
	return entries[name];
}

void TextureAtlas::Save(tinyxml2::XMLDocument *document)
{
	tinyxml2::XMLElement * xmlTextureAtlas = document->NewElement("TextureAtlas");
	XMLFileNode xmlFileNode(xmlTextureAtlas);
	xmlFileNode.Write("image", image);
	xmlFileNode.Write("width", width);
	xmlFileNode.Write("height", height);

	for (std::map<std::string, TextureAtlasEntry*>::iterator i = entries.begin(); i != entries.end(); ++i)
	{
		TextureAtlasEntry *textureAtlasEntry = (*i).second;

		tinyxml2::XMLElement * xmlAtlasEntry = document->NewElement("TextureAtlasEntry");
		XMLFileNode xmlFileNodeAtlasEntry(xmlAtlasEntry);
		textureAtlasEntry->Save(&xmlFileNodeAtlasEntry);

		xmlTextureAtlas->InsertEndChild(xmlAtlasEntry);
	}

	document->InsertEndChild(xmlTextureAtlas);
}

void TextureAtlas::Load(tinyxml2::XMLElement *element)
{
	XMLFileNode xmlFileNode(element);
	xmlFileNode.Read("image", image);
	xmlFileNode.Read("width", width);
	xmlFileNode.Read("height", height);

	tinyxml2::XMLElement *xmlAtlasEntry = element->FirstChildElement("TextureAtlasEntry");
	while (xmlAtlasEntry)
	{
		XMLFileNode xmlFileNodeAtlasEntry(xmlAtlasEntry);

		TextureAtlasEntry *textureAtlasEntry = new TextureAtlasEntry(this);
		textureAtlasEntry->Load(&xmlFileNodeAtlasEntry);
		if (textureAtlasEntry->name != "")
			entries[textureAtlasEntry->name] = textureAtlasEntry;

		xmlAtlasEntry = xmlAtlasEntry->NextSiblingElement("TextureAtlasEntry");
	}
}

std::string TextureAtlas::GetImageName()
{
	return image;
}