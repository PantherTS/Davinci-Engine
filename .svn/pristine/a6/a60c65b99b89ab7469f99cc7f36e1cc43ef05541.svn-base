#include "TextureAsset.h"
#include "GL/glew.h"
#include "Framework.h"
#include <string>

#include "stb_image.h"

using namespace DavinciEngine;

TextureAsset::TextureAsset() : Asset(ASSET_TEXTURE)
{
}

TextureAsset::~TextureAsset()
{
}

void TextureAsset::Load(const std::string &filename, FilterType filter, bool repeatX, bool repeatY)
{
	filter = filter;
	repeatX = repeatX;
	repeatY = repeatY;
	m_sFilename = filename;
	std::string cPath = Framework::GetInstance()->GetDefaultContentPath();
	m_sFilename = m_sFilename.replace(0,cPath.length(),"");

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glEnable(GL_TEXTURE_2D);

	// Choose GL_NEAREST
	unsigned int glMagFilter = GL_NEAREST;
	unsigned int glMinFilter = GL_NEAREST;

	if (filter == FILTER_LINEAR)
	{
		glMagFilter = GL_LINEAR;
		glMinFilter = GL_LINEAR_MIPMAP_LINEAR;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glMinFilter);

	unsigned int glRepeatX = repeatX?GL_REPEAT:GL_CLAMP;
	unsigned int glRepeatY = repeatY?GL_REPEAT:GL_CLAMP;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glRepeatX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glRepeatY);

	int w,h,n;
	unsigned char *data = stbi_load(filename.c_str(), &w, &h, &n, STBI_rgb_alpha);

	if (data)
	{
		width = (unsigned int)w;
		height = (unsigned int)h;

		// mipmaps: OpenGL 1.4 version
		//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// Delete the pixel data since we've generated the texture in video memory already.
		delete data;

		// mipmaps: OpenGL 3.0 version
		glGenerateMipmap(GL_TEXTURE_2D);

		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

		Log("Loaded texture successfully: %s", filename.c_str());
	}
	else
	{
		Log("Texture failed to load: %s", filename.c_str());

		width = height = 64;
	}
}

void TextureAsset::Unload()
{
	Log("Removing texture from memory: %s", m_sFilename.c_str());
	glDeleteTextures(1, &texID);
	delete this;
}

void TextureAsset::Reload()
{
	Unload();
	Load(m_sFilename, filter, repeatX, repeatY);
}
