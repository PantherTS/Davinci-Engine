#include "SpriteAnimation.h"
#include "Sprite.h"
#include "LowLevelSystem.h"
#include "Timer.h"
#include "XMLFileNode.h"
#include <string>
#include <sstream>

using namespace DavinciEngine;

Animation::Animation(const std::string &name, int start, int end, float speed)
	: name(name), start(start), end(end), speed(speed), frame(static_cast<float>(start)), isPlaying(false)
{

}

void Animation::Save(FileNode *fileNode)
{
		fileNode->Write("name", name);
		fileNode->Write("start",start);
		fileNode->Write("end",end);
		fileNode->Write("speed",speed);
}

SpriteAnimation::SpriteAnimation(const std::string &filename, FilterType filter, float width, float height,TextureAtlas *textureAtlas)
	: Sprite(filename, filter, width, height), m_pTextureAtlas(textureAtlas), animation(nullptr), lastAnimation(nullptr)
{

}

SpriteAnimation::SpriteAnimation(const SpriteAnimation &other)
	: Sprite(other), m_pTextureAtlas(other.m_pTextureAtlas->GetReference()), animation(nullptr), lastAnimation(nullptr), m_sDefaultAnimation(other.m_sDefaultAnimation),
	animations(other.animations)
{
}

SpriteAnimation::~SpriteAnimation()
{
	if(m_pTextureAtlas){
		m_pTextureAtlas->Destroy();
		m_pTextureAtlas = nullptr;
	}
	if(!animations.empty())
		animations.clear();
}

void SpriteAnimation::Add(const std::string &name, int start, int end, float speed)
{
	Animation a(name, start, end, speed);
	animations.push_back(a);
}

void SpriteAnimation::Play(const std::string &name)
{
	if(!animation || name != animation->name){
		animation = GetAnimation(name);
		if (animation)
		{
			// Stop the previous animation since we're loading up a new one here.
			if(m_sLastAnimationName != ""){
				Stop(m_sLastAnimationName);
			}
			animation->isPlaying = true;
			m_sLastAnimationName = name;
		}
	}
}

void SpriteAnimation::Stop(const std::string &name)
{
	lastAnimation = GetAnimation(name);
	if (lastAnimation)
	{
		lastAnimation->isPlaying = false;
	}
}

void SpriteAnimation::Render()
{
	int x = 0;
	int y = 0;

	if(animation)
	{
		std::ostringstream oss;
		if(!m_bIsMoving && animation->end != 0){
			const size_t index = m_sLastAnimationName.rfind("_");
			std::string dir = m_sLastAnimationName.substr(index+1);
			std::string action = GetActionFromAnimation(m_sDefaultAnimation);
			m_sCurrentAction = action;
			Play(action + "_" + dir);
			oss << animation->name;
		}
		else{
			if(animation->end != 0){
				oss << animation->name << (int) animation->frame;
			}
			else{
				oss << animation->name;
			}
		}

		if(animation->isPlaying)
		{
			animation->frame += animation->speed * static_cast<float>(Timer::GetInstance()->GetDeltaTime()) * 10.0f;
			if(animation->frame > animation->end + 1) { animation->frame = static_cast<float>(animation->start); }
		}

		TextureAtlasEntry *m_pCurrentEntry = nullptr;
		m_pCurrentEntry = m_pTextureAtlas->GetEntryByName(oss.str());

		if(m_pCurrentEntry){
			textureOffset = m_pCurrentEntry->GetTextureOffset();
			textureScale = m_pCurrentEntry->GetTextureScale();
		}
	}
	else{
		//Warning("Default Animation not specified for %s",m_pTextureAtlas->GetImageName().c_str());
		textureOffset = Vec2D((x * m_fWidth) / texture->width, (y * m_fHeight) / texture->height);
		textureScale = Vec2D(m_fWidth / texture->width, m_fHeight / texture->height);
	}

	glTranslatef(position.x, position.y, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture->texID);
	OpenGLFunctions::SetBlend(blend);
	OpenGLFunctions::MakeQuad(m_fWidth, m_fHeight, textureOffset, textureScale);
}

Animation *SpriteAnimation::GetAnimation(const std::string &name)
{
	for (std::list<Animation>::iterator i = animations.begin(); i != animations.end(); ++i)
	{
		if(i->name == name)
		{
			return &(*i);
		}
	}
	return lastAnimation;
}

void SpriteAnimation::Animate()
{
	switch (facingDirection)
	{
	case NORTH: {
		Play(m_sCurrentAction + "_n");
		lastFacingDirection = NORTH;
		break;
				}
	case NORTHEAST: {
		Play(m_sCurrentAction + "_ne");
		lastFacingDirection = NORTHEAST;
		break;
					}
	case EAST: {
		Play(m_sCurrentAction + "_e");
		lastFacingDirection = EAST;
		break;
			   }
	case SOUTHEAST: {
		Play(m_sCurrentAction + "_se");
		lastFacingDirection = SOUTHEAST;
		break;
					}
	case SOUTH: {
		Play(m_sCurrentAction + "_s");
		lastFacingDirection = SOUTH;
		break;
				}
	case SOUTHWEST: {
		Play(m_sCurrentAction + "_sw");
		lastFacingDirection = SOUTHWEST;
		break;
					}
	case WEST: {
		Play(m_sCurrentAction + "_w");
		lastFacingDirection = WEST;
		break;
			   }
	case NORTHWEST: {
		Play(m_sCurrentAction + "_nw");
		lastFacingDirection = NORTHWEST;
		break;
					}
	default:
		Play(m_sDefaultAnimation);
		facingDirection = GetFacingDirFromAnimation(m_sDefaultAnimation);
		m_sCurrentAction = GetActionFromAnimation(m_sDefaultAnimation);
		lastFacingDirection = facingDirection;
		break;
	}
}

std::string SpriteAnimation::GetActionFromAnimation(const std::string &animationName){
	const size_t index = animationName.rfind("_");
	return animationName.substr(0,index);
}

Direction SpriteAnimation::GetFacingDirFromAnimation(const std::string &animationName){
	const size_t index = animationName.rfind("_");
	std::string dir = animationName.substr(index+1);

	if(dir == "n")
		return NORTH;
	else if(dir == "ne")
		return NORTHEAST;
	else if(dir == "e")
		return EAST;
	else if(dir == "se")
		return SOUTHEAST;
	else if(dir == "s")
		return SOUTH;
	else if(dir == "sw")
		return SOUTHWEST;
	else if(dir == "w")
		return WEST;
	else if(dir == "nw")
		return NORTHWEST;
	else
		return INVALID_DIR;
}

void SpriteAnimation::Save(tinyxml2::XMLDocument *document)
{
	tinyxml2::XMLElement * xmlAnimations = document->NewElement("Animations");
	XMLFileNode xmlFileNodeAnimations(xmlAnimations);
	xmlFileNodeAnimations.Write("filter",(int)texture->filter);
	xmlFileNodeAnimations.Write("width",m_fWidth);
	xmlFileNodeAnimations.Write("height",m_fHeight);

	for(std::list<Animation>::iterator i = animations.begin(); i != animations.end(); ++i)
	{
		Animation *animation = &(*i);
		tinyxml2::XMLElement * xmlAnimationEntry = document->NewElement("AnimationEntry");
		XMLFileNode xmlFileNodeAnimationEntry(xmlAnimationEntry);
		if(animation->name == "default"){
			xmlFileNodeAnimationEntry.Write("name",animation->name);
			xmlFileNodeAnimationEntry.Write("value",m_sDefaultAnimation);
		}
		else{
			animation->Save(&xmlFileNodeAnimationEntry);
		}

		xmlAnimations->InsertEndChild(xmlAnimationEntry);
	}

	document->InsertEndChild(xmlAnimations);
}

SpriteAnimation *SpriteAnimation::Load(tinyxml2::XMLElement *element,TextureAtlas *textureAtlas)
{
	SpriteAnimation *m_pSpriteAnimation = nullptr;
	XMLFileNode xmlFileNodeElement(element);

	int filter = 0;
	int width = 0;
	int height = 0;
	xmlFileNodeElement.Read("filter",filter);
	xmlFileNodeElement.Read("width",width);
	xmlFileNodeElement.Read("height",height);

	FilterType filterType = (FilterType)filter;

	m_pSpriteAnimation = new SpriteAnimation(textureAtlas->GetImageName(),filterType,static_cast<float>(width),static_cast<float>(height),textureAtlas);
	
	m_pSpriteAnimation->SetSpriteAnimation(m_pSpriteAnimation);

	tinyxml2::XMLElement *xmlAnimationEntry = element->FirstChildElement("AnimationEntry");
	while(xmlAnimationEntry)
	{
		std::string name;
		int start = 0;
		int end = 0;
		float speed = 0;
		XMLFileNode xmlFileNodeAnimationEntry(xmlAnimationEntry);
		xmlFileNodeAnimationEntry.Read("name",name);
		if(name == "default"){
			xmlFileNodeAnimationEntry.Read("value",m_pSpriteAnimation->m_sDefaultAnimation);
		}
		else{
			xmlFileNodeAnimationEntry.Read("start",start);
			xmlFileNodeAnimationEntry.Read("end",end);
			xmlFileNodeAnimationEntry.Read("speed",speed);
			m_pSpriteAnimation->Add(name,start,end,speed);
		}

		xmlAnimationEntry = xmlAnimationEntry->NextSiblingElement("AnimationEntry");
	}
	return m_pSpriteAnimation;
}
