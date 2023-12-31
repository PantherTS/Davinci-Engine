#include "Sprite.h"
#include "AssetManager.h"
#include "Object.h"
#include "Timer.h"

using namespace DavinciEngine;

Sprite::Sprite(const std::string &filename, float width, float height)
	: Graphic(),
	texture(nullptr),
	m_fWidth(width),
	m_fHeight(height),
	m_fSpeed(1.0f),
	textureOffset(0,0),
	textureScale(1,1),
	blend(BLEND_ALPHA),
	m_bIsMoving(false),
	m_pSpriteAnimation(nullptr),
	facingDirection(INVALID_DIR),
	lastFacingDirection(INVALID_DIR)
{
	texture = AssetManager::GetInstance()->RequestTexture(filename);
	if (texture != nullptr)
	{
		if (width == -1 || height == -1)
		{
			this->m_fWidth = static_cast<float>(texture->width);
			this->m_fHeight = static_cast<float>(texture->height);
		}
	}
}

Sprite::Sprite(const std::string &filename, FilterType filter, float width, float height)
	: Graphic(),
	texture(nullptr),
	m_fWidth(width),
	m_fHeight(height),
	m_fSpeed(1.0f),
	textureOffset(0,0),
	textureScale(1,1),
	blend(BLEND_ALPHA),
	m_bIsMoving(false),
	m_pSpriteAnimation(nullptr),
	facingDirection(INVALID_DIR),
	lastFacingDirection(INVALID_DIR)
{
	texture = AssetManager::GetInstance()->RequestTexture(filename, filter);
	if (texture != nullptr)
	{
		if (width == -1 || height == -1)
		{
			this->m_fWidth = static_cast<float>(texture->width);
			this->m_fHeight = static_cast<float>(texture->height);
		}
	}
}

Sprite::Sprite()
	: Graphic(),
	texture(nullptr),
	m_fWidth(1.0f),
	m_fHeight(1.0f),
	m_fSpeed(1.0f),
	textureOffset(0,0),
	textureScale(1,1),
	blend(BLEND_ALPHA),
	m_bIsMoving(false),
	m_pSpriteAnimation(nullptr),
	facingDirection(INVALID_DIR),
	lastFacingDirection(INVALID_DIR)
{
}

Sprite::Sprite(const Sprite &other)
	: Graphic(),
	texture(AssetManager::GetInstance()->RequestTexture(other.texture->m_sFilename)),
	m_fWidth(other.m_fWidth),
	m_fHeight(other.m_fHeight),
	m_fSpeed(other.m_fSpeed),
	textureOffset(other.textureOffset),
	textureScale(other.textureScale),
	blend(other.blend),
	m_bIsMoving(false),
	m_pSpriteAnimation(nullptr),
	facingDirection(INVALID_DIR),
	lastFacingDirection(INVALID_DIR)
{
}

Sprite::~Sprite()
{
	if (texture != nullptr)
	{
		texture->RemoveReference();
		texture = nullptr;
	}
}

void Sprite::Render(Object *object)
{
	glTranslatef(position.x, position.y, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture->texID);
	OpenGLFunctions::SetBlend(blend);
	OpenGLFunctions::MakeQuad(m_fWidth, m_fHeight, textureOffset, textureScale);
}

const Vec2D Sprite::GetWidthHeight()
{
	if(texture)
	{
		return Vec2D(m_fWidth, m_fHeight);
	}
	return Vec2D(0, 0);
}

void Sprite::SetSpriteAnimation(SpriteAnimation *animation)
{
	m_pSpriteAnimation = animation;
}

void Sprite::MoveTo(Vec2D coordinate, Vec2D currentPosition)
{	
	m_bIsMoving = true;
	m_vec2Destination.x = coordinate.x-(m_fWidth/2);
	m_vec2Destination.y = coordinate.y-(m_fHeight/2);
	m_vec2Direction.x = (m_vec2Destination.x - (currentPosition.x-(m_fWidth/2)));
	m_vec2Direction.y = (m_vec2Destination.y - (currentPosition.y-(m_fHeight/2)));
	Normalize(m_vec2Direction);
}

void Sprite::Move(Vec2D &position)
{
	Vec2D moveToPosition(position);
	moveToPosition.x = moveToPosition.x - (m_fWidth/2);
	moveToPosition.y = moveToPosition.y - (m_fHeight/2);
	//dt = 1;							// Used for debug purposes only.

	// Check for sprite's arrival at the destination.
	if( ( moveToPosition.x > floor(m_vec2Destination.x) - (4.0 * m_fSpeed) ) && ( moveToPosition.x < floor(m_vec2Destination.x) + (4.0 * m_fSpeed) ) &&
		( moveToPosition.y > floor(m_vec2Destination.y) - (4.0 * m_fSpeed) ) && ( moveToPosition.y < floor(m_vec2Destination.y) + (4.0 * m_fSpeed) ) )
	{		
		m_bIsMoving = false;										// Stop the sprite once it has reached its destination.
	}
	else{
		const float dt = static_cast<float>(Timer::GetInstance()->GetDeltaTime()) * 100.0f;

		moveToPosition.x += m_vec2Direction.x * dt * m_fSpeed;				// Update the location of the sprite.
		moveToPosition.y += m_vec2Direction.y * dt * m_fSpeed;				// Update the location of the sprite.
		
		if ( moveToPosition.x < 0 )
		{
			moveToPosition.x = 0;													// Keep sprite right of left side bounds of window.
			m_bIsMoving = false;
		}
		else if ( moveToPosition.y < 0 )
		{
			moveToPosition.y = 0;													// Keep sprite above the bottom of the window.
			m_bIsMoving = false;
		}
		else if ( moveToPosition.y > 768 )
		{
			moveToPosition.y = 600;													// Keep sprite above the bottom of the window.
			m_bIsMoving = false;
		}
		else if ( moveToPosition.x > 1024 )
		{
			moveToPosition.x = 900;													// Keep sprite above the bottom of the window.
			m_bIsMoving = false;
		}
	
		// Every thing's alright so go ahead and set the coordinates to the sprite.
		position.x = moveToPosition.x + (m_fHeight/2);				// Update the x coordinate of the sprite.
		position.y = moveToPosition.y + (m_fWidth/2);				// Update the y coordinate of the sprite.
	}
}

void Sprite::Normalize(Vec2D &spriteVelocity)
{
	const float speed = sqrtf(spriteVelocity.x * spriteVelocity.x + spriteVelocity.y * spriteVelocity.y);
	spriteVelocity.x /= speed;
	spriteVelocity.y /= speed;

	// Get the radian direction the sprite is facing
	float degrees = static_cast<float>(atan2(spriteVelocity.y, spriteVelocity.x));
	// Account for atan2 being off by 90 degrees which points down X-Axis while our sprites are aligned facing up Y-Axis
	degrees = degrees + static_cast<float>(-4.0f / M_PI);
	// Convert to degrees from radians
	degrees = degrees * static_cast<float>(180.0f / M_PI);
	// Account for negative degrees and keep them positive up to 360
	if(degrees < 0){
		degrees = 360 - (-degrees);
	}

	// Determine which facing direction the sprite should be assigned based on calculated degrees
	if(degrees < 22.5 || degrees > 337.5)			// Sprite moving N 45 degree span
	{
		this->facingDirection = NORTH;
	}
	else if(degrees > 22.5 && degrees < 67.5)		// Sprite moving NE 45 degree span
	{
		this->facingDirection = NORTHEAST;
	}
	else if(degrees > 67.5 && degrees < 112.5)		// Sprite moving E 45 degree span
	{
		this->facingDirection = EAST;
	}
	else if(degrees > 112.5 && degrees < 157.5)		// Sprite moving SE 45 degree span
	{
		this->facingDirection = SOUTHEAST;
	}
	else if(degrees > 157.5 && degrees < 202.5)		// Sprite moving S 45 degree span
	{
		this->facingDirection = SOUTH;
	}
	else if(degrees > 202.5 && degrees < 247.5)		// Sprite moving SW 45 degree span
	{
		this->facingDirection = SOUTHWEST;
	}
	else if(degrees > 247.5 && degrees < 292.5)		// Sprite moving W 45 degree span
	{
		this->facingDirection = WEST;
	}
	else if(degrees > 292.5 && degrees < 337.5)		// Sprite moving NW 45 degree span
	{
		this->facingDirection = NORTHWEST;
	}
}