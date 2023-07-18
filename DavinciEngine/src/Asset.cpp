#include "Asset.h"
#include "AssetManager.h"

using namespace DavinciEngine;

Asset::Asset(AssetType type) : type(type)
{
	m_bIsCached = false;
	m_iRefCount = 0;
	type = ASSET_UNDEFINED;
}

void Asset::AddReference()
{
	m_iRefCount++;

	//Debug::Log("referenceCount increased for: " + filename);
	//Debug::Log(referenceCount);
}

void Asset::RemoveReference()
{
	m_iRefCount--;

	Log("Reference Count decreased for: %s", m_sFilename.c_str());

	if (m_iRefCount == 0)
	{
		if (!m_bIsCached)
		{
			Unload();
			AssetManager::GetInstance()->RemoveAsset(this);
		}
	}
}

std::string Asset::GetName()
{
	const size_t size = AssetManager::GetInstance()->GetContentPath().size();
	return m_sFilename.substr(size, m_sFilename.size() - size);
}

std::string Asset::GetExtension()
{
	std::string fn = GetName();
	return fn.substr(fn.find_last_of(".") + 1);
}
