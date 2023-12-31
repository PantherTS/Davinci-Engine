#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "FileNode.h"
#include "Vec2D.h"
#include "tinyxml2.h"

#include <map>

class tinyxml2::XMLDocument;
class tinyxml2::XMLElement;

namespace DavinciEngine{

	class TextureAtlas;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> A Texture atlas entry holds coordinate information for where each
	/// 		  individual image is in a Sprite sheet. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class TextureAtlasEntry{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAtlasEntry();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Constructor.</summary>
		///
		/// <param name="textureAtlas"> [in,out] If non-null, the texture atlas.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAtlasEntry(TextureAtlas *textureAtlas);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Saves the TextureAtlas object to XML.</summary>
		///
		/// <param name="fileNode"> [in,out] If non-null, the FileNode * to save.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Save(FileNode *fileNode);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the TextureAtlas information from file.</summary>
		///
		/// <param name="fileNode"> [in,out] If non-null, the FileNode * to load.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Load(FileNode *fileNode);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the texture offset.</summary>
		///
		/// <returns> The texture offset.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vec2D GetTextureOffset();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the texture scale.</summary>
		///
		/// <returns> The texture scale.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vec2D GetTextureScale();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the width.</summary>
		///
		/// <returns> The width.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetWidth();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the height.</summary>
		///
		/// <returns> The height.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetHeight();

	private:
		friend class TextureAtlas;

		/// <summary> The name of this TextureAtlasEntry object </summary>
		std::string name;

		/// <summary> The coordinates, width, and height of the TextureAtlasEntry </summary>
		int x, y, width, height;

		/// <summary> A pointer to the TextureAtlas Object </summary>
		TextureAtlas *textureAtlas;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> The TextureAtlas object holds many TextureAtlasEntry objects defining
	/// 		  an entire Sprite sheet and its images. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class TextureAtlas
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAtlas();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~TextureAtlas();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Copy constructor.</summary>
		///
		/// <param name="other"> [in,out] The other.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAtlas(TextureAtlas &other);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destroys this object or removes a reference if still in use.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Destroy();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets a pointer to this TextureAtlas.</summary>
		///
		/// <returns> null if it fails, else the reference.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAtlas *GetReference();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets a TextureAtlasEntry by name.</summary>
		///
		/// <param name="name"> The name of the TextureAtlasEntry.</param>
		///
		/// <returns> null if it fails, else the entry by name.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAtlasEntry *GetEntryByName(const std::string &name);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Saves the entire TextureAtlas to file.</summary>
		///
		/// <param name="document"> [in,out] If non-null, the tinyxml2::XMLDocument * to save.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Save(tinyxml2::XMLDocument *document);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the TextureAtlas and TextureAtlasEntries from file.</summary>
		///
		/// <param name="element"> [in,out] If non-null, the tinyxml2::XMLElement * to load.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Load(tinyxml2::XMLElement *element);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the image name.</summary>
		///
		/// <returns> The image name.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string GetImageName();

	private:
		friend class TextureAtlasEntry;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Adds 1 to the reference count.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void AddReference();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Removes 1 from the reference count.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void RemoveReference();

		/// <summary> The image name </summary>
		std::string image;

		/// <summary> The width and height </summary>
		int width, height;

		/// <summary> Number of references </summary>
		int m_iRefCount;

	private:

		/// <summary> Storage map of TextureAtlasEntries </summary>
		std::map<std::string, TextureAtlasEntry*> entries;
	};
}
#endif