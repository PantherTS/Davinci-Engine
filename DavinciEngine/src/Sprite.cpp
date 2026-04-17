#define _USE_MATH_DEFINES
#include "Sprite.h"
#include "AssetManager.h"
#include "Object.h"
#include "Timer.h"
#include "QuadRenderer.h"
#include "Window.h"
#include <cmath>

using namespace DavinciEngine;

Sprite::Sprite(const std::string& filename, float width, float height)
    : SpriteGraphic(),
    texture(nullptr),
    m_fSpeed(1.0f),
    m_bIsMoving(false),
    m_pSpriteAnimation(nullptr),
    facingDirection(INVALID_DIR),
    lastFacingDirection(INVALID_DIR),
    m_vec2Destination(glm::vec2(0.0f)),
    m_vec2Direction(glm::vec2(0.0f))
{
    texture = AssetManager::GetInstance()->RequestTexture(filename);
    if (texture != nullptr)
    {
        this->textureID = texture->GetTextureID();
        this->uvScale = glm::vec2(1.0f, 1.0f);
        this->uvOffset = glm::vec2(0.0f, 0.0f);

        if (width == -1 || height == -1)
        {
            this->size.x = static_cast<float>(texture->width);
            this->size.y = static_cast<float>(texture->height);
        }
        else
        {
            this->size = glm::vec2(width, height);
        }
    }
}

Sprite::Sprite(const std::string& filename, FilterType filter, float width, float height)
    : SpriteGraphic(),
    texture(nullptr),
    m_fSpeed(1.0f),
    m_bIsMoving(false),
    m_pSpriteAnimation(nullptr),
    facingDirection(INVALID_DIR),
    lastFacingDirection(INVALID_DIR),
    m_vec2Destination(glm::vec2(0.0f)),
    m_vec2Direction(glm::vec2(0.0f))
{
    texture = AssetManager::GetInstance()->RequestTexture(filename, filter);
    if (texture != nullptr)
    {
        this->textureID = texture->GetTextureID();
        this->uvScale = glm::vec2(1.0f, 1.0f);
        this->uvOffset = glm::vec2(0.0f, 0.0f);

        if (width == -1 || height == -1)
        {
            this->size.x = static_cast<float>(texture->width);
            this->size.y = static_cast<float>(texture->height);
        }
        else
        {
            this->size = glm::vec2(width, height);
        }
    }
}

Sprite::Sprite()
    : SpriteGraphic(),
    texture(nullptr),
    m_fSpeed(1.0f),
    m_bIsMoving(false),
    m_pSpriteAnimation(nullptr),
    facingDirection(INVALID_DIR),
    lastFacingDirection(INVALID_DIR),
    m_vec2Destination(glm::vec2(0.0f)),
    m_vec2Direction(glm::vec2(0.0f))
{
    this->uvScale = glm::vec2(1.0f, 1.0f);
    this->uvOffset = glm::vec2(0.0f, 0.0f);
    this->size = glm::vec2(0.0f, 0.0f);
}

Sprite::Sprite(const Sprite& other)
    : SpriteGraphic(),
    texture(nullptr),
    m_fSpeed(other.m_fSpeed),
    m_bIsMoving(false),
    m_pSpriteAnimation(nullptr),
    facingDirection(INVALID_DIR),
    lastFacingDirection(INVALID_DIR),
    m_vec2Destination(glm::vec2(0.0f)),
    m_vec2Direction(glm::vec2(0.0f))
{
    this->uvScale = other.uvScale;
    this->uvOffset = other.uvOffset;
    this->size = other.size;

    if (other.texture)
    {
        texture = AssetManager::GetInstance()->RequestTexture(other.texture->m_sFilename);
        if (texture) this->textureID = texture->GetTextureID();
    }
}

Sprite::~Sprite()
{
    if (texture != nullptr)
    {
        texture->RemoveReference();
        texture = nullptr;
    }
}

void Sprite::Render(const glm::mat4& vp, const glm::mat4& model) {
    if (!texture) return;

    QuadRenderer::DrawQuad(
        vp,
        model,
        texture->GetTextureID(),
        uvOffset,
        uvScale
    );
}

glm::vec2 Sprite::GetSize()
{
    return size;
}

void Sprite::SetSpriteAnimation(SpriteAnimation* animation)
{
    m_pSpriteAnimation = animation;
}

void Sprite::MoveTo(glm::vec2 targetCoordinate, glm::vec2 currentPosition)
{
    m_bIsMoving = true;
    m_vec2Destination = targetCoordinate;

    // Direction = Destination - Start
    m_vec2Direction = m_vec2Destination - currentPosition;

    if (glm::length(m_vec2Direction) > 0.0f)
        Normalize(m_vec2Direction);
}

void Sprite::Move(glm::vec2& position)
{
    if (!m_bIsMoving) return;

    float dist = glm::distance(position, m_vec2Destination);

    if (dist < (m_fSpeed * 1.0f))
    {
        m_bIsMoving = false;
        position = m_vec2Destination;
    }
    else
    {
        const float dt = static_cast<float>(Timer::GetInstance()->GetDeltaTime());
        position += m_vec2Direction * m_fSpeed * dt * 100.0f;

        float halfW = size.x * 0.5f;
        float halfH = size.y * 0.5f;

        position.x = glm::clamp(position.x, halfW, (float)Window::GetInstance()->GetWidth() - halfW);
        position.y = glm::clamp(position.y, halfH, (float)Window::GetInstance()->GetHeight() - halfH);
    }
}

void Sprite::Normalize(glm::vec2& spriteVelocity)
{
    spriteVelocity = glm::normalize(spriteVelocity);

    float radians = atan2(spriteVelocity.y, spriteVelocity.x);
    float degrees = glm::degrees(radians);

    if (degrees < 0) degrees += 360.0f;

    if (degrees >= 337.5 || degrees < 22.5)         facingDirection = EAST;
    else if (degrees >= 22.5 && degrees < 67.5)    facingDirection = SOUTHEAST;
    else if (degrees >= 67.5 && degrees < 112.5)   facingDirection = SOUTH;
    else if (degrees >= 112.5 && degrees < 157.5)   facingDirection = SOUTHWEST;
    else if (degrees >= 157.5 && degrees < 202.5)   facingDirection = WEST;
    else if (degrees >= 202.5 && degrees < 247.5)   facingDirection = NORTHWEST;
    else if (degrees >= 247.5 && degrees < 292.5)   facingDirection = NORTH;
    else if (degrees >= 292.5 && degrees < 337.5)   facingDirection = NORTHEAST;
}
