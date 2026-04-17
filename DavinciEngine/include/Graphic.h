#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <glm/glm.hpp>
#include <glad/gl.h>

namespace DavinciEngine
{
	class Graphic
	{
	public:
		enum BlendType
		{
			BLEND_NONE = 0,
			BLEND_ALPHA,
			BLEND_ADDITIVE,
			BLEND_MULTIPLY,
		};

		BlendType blend = BLEND_ALPHA;
		glm::vec2 position = glm::vec2(0.0f);

		virtual void Render(const glm::mat4& vp, const glm::mat4& model) = 0;
		virtual glm::vec2 GetSize() = 0;
		virtual unsigned int GetTextureID() const = 0;

		virtual ~Graphic() = default;
	};
};

#endif