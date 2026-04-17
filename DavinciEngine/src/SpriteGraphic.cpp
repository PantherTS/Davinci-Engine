#include "SpriteGraphic.h"
#include "QuadRenderer.h"

namespace DavinciEngine
{
	void SpriteGraphic::Render(const glm::mat4& vp, const glm::mat4& model)
	{
		QuadRenderer::DrawQuad(vp, model, textureID, uvOffset, uvScale);
	}

	glm::vec2 SpriteGraphic::GetSize()
	{
		return size;
	}
}