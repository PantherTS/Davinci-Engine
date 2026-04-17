#pragma once

#include "Graphic.h"

namespace DavinciEngine
{
	class SpriteGraphic : public Graphic
	{
	public:
		unsigned int textureID = 0;

		glm::vec2 size = { 100.0f, 100.0f };
		glm::vec2 uvOffset = { 0.0f, 0.0f };
		glm::vec2 uvScale = { 1.0f, 1.0f };

		virtual void Render(const glm::mat4& vp, const glm::mat4& model) override;
		virtual glm::vec2 GetSize() override;
	};
}