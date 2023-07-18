#ifndef TEXTUREASSET_H
#define TEXTUREASSET_H

#include "Asset.h"
#include "LowLevelSystem.h"

namespace DavinciEngine{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Texture Asset object that holds information related to a loaded Texture. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class TextureAsset : public Asset
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TextureAsset();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~TextureAsset();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the given file.</summary>
		///
		/// <param name="filename"> Filename of the texture.</param>
		/// <param name="filter">   The filter being used on the texture.</param>
		/// <param name="repeatX">  true to repeat x coordinate.</param>
		/// <param name="repeatY">  true to repeat y coordinate.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Load(const std::string &filename, FilterType filter, bool repeatX, bool repeatY);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Reloads this object.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Reload();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Unloads this object.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Unload();

		/// <summary> The filter being used on the texture </summary>
		FilterType filter;

		/// <summary> The repeat x and y coordinates </summary>
		bool repeatX, repeatY;

		/// <summary> The width and height of the texture </summary>
		unsigned int width, height;

		/// <summary> Identifier for the texture in video memory </summary>
		unsigned int texID;
	};
}

#endif