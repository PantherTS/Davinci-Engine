#include "AssetManager.h"
#include "TextureAsset.h"
#include "Framework.h"

//#include "Audio/AudioAsset.h"
//#include "TTFFontAsset.h"

#include <stdio.h>
#include <string>

using namespace DavinciEngine;

AssetManager *AssetManager::m_pAssetManager = NULL;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

AssetManager *AssetManager::GetInstance(){
	if(!m_pAssetManager){
		m_pAssetManager = new AssetManager();
		m_pAssetManager->Init();
	}
	return m_pAssetManager;
}

void AssetManager::Destroy(){
	if(m_pAssetManager){
		delete m_pAssetManager;
		m_pAssetManager = NULL;
	}
}

void AssetManager::Init()
{
	SetContentPath(Framework::GetInstance()->GetDefaultContentPath());
}

TextureAsset *AssetManager::RequestTexture(const std::string &filename, FilterType filter /* = FILTER_LINEAR */, bool repeatX /* = false */, bool repeatY /* = false */)
{
	TextureAsset *asset = NULL;
	std::string fullFilename = contentPath + filename;

	// Check to see if we've already loaded this file.
	asset = (TextureAsset*)GetAssetByFilename(filename);

	// If we haven't, load it and store it.
	if (!asset)
	{
		asset = new TextureAsset();
		asset->Load(fullFilename, filter, repeatX, repeatY);
		StoreAsset((Asset*)asset);
	}

	if (asset)
	{
		asset->AddReference();
	}

	// Return the texture asset.
	return asset;
}

//FontAsset *AssetManager::RequestFont(const std::string &filename, float size, int textureWidth, int textureHeight)
//{
//	TTFFontAsset *asset = NULL;
//	std::string fullFilename = instance->contentPath + filename;
//
//	//Debug::Log("instance->contentPath + filename: " + fullFilename);
//
//	// check to see if we have one stored already
//	asset = (TTFFontAsset*)instance->GetAssetByFilename(fullFilename);
//
//	// if not, load it and store it
//	if (!asset)
//	{
//		asset = new TTFFontAsset();
//		if (asset->Load(fullFilename, size, textureWidth, textureHeight))
//		{
//			instance->StoreAsset((Asset*)asset);
//		}
//		else
//		{
//			delete asset;
//			asset = NULL;
//		}
//	}
//
//	if (asset)
//	{
//		asset->AddReference();
//	}
//
//	// return what we found
//	return asset;
//}
//
//AudioAsset *Assets::RequestAudio(const std::string &filename, bool streamFromDisk, std::string decodeString)
//{
//	AudioAsset *asset = NULL;
//	std::string fullFilename = instance->contentPath + filename;
//
//	//Debug::Log("instance->contentPath + filename: " + fullFilename);
//
//	// check to see if we have one stored already
//	asset = (AudioAsset*)instance->GetAssetByFilename(fullFilename);
//
//	// if not, load it and store it
//	if (!asset)
//	{
//		asset = new AudioAsset();
//		asset->SetDecodeString(decodeString);
//		asset->Load(fullFilename, streamFromDisk);
//
//		// Return NULL if there was no asset...
//		if (!asset->GetDataSize()){
//			delete asset;
//			return NULL;
//		}
//
//		instance->StoreAsset((Asset*)asset);
//	}
//
//	if (asset)
//	{
//		asset->AddReference();
//	}
//
//	// return what we found
//	return asset;
//}

void AssetManager::StoreAsset(Asset *asset)
{
	// Store a pointer to the loaded Asset object.
	assetList.push_back(asset);
}

void AssetManager::RemoveAsset(Asset *asset)
{
	this->assetList.remove(asset);
}

Asset *AssetManager::GetAssetByFilename(const std::string &filename)
{
	for(std::list<Asset*>::iterator i = assetList.begin(); i != assetList.end(); ++i)
	{
		if ((*i)->m_sFilename.compare(filename) == 0)
		{
			return (*i);
		}
	}
	return NULL;
}

void AssetManager::SetContentPath(const std::string &contentPath)
{
	m_pAssetManager->contentPath = contentPath;
}

const std::string &AssetManager::GetContentPath()
{
	return contentPath;
}

//Asset* Assets::RequestXML(AssetType assetType, const char *filename)
//{
//Asset *newAsset = NULL;
//
//switch(assetType)
//{
//case AT_TEXTURE:
//newAsset = (Asset*)new TextureAsset();
//newAsset->Load(filename);
//StoreAsset((Asset*)newAsset);
//break;
//}
//
//return newAsset;
//}