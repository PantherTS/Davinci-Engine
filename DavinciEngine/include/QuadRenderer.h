#pragma once

#include <glm/glm.hpp>

namespace DavinciEngine
{
	class QuadRenderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void DrawQuad(
			const glm::mat4& vp,
			const glm::mat4& model,
			unsigned int texture,
			const glm::vec2& uvOffset,
			const glm::vec2& uvScale);

	};
}