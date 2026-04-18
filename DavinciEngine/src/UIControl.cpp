#include "UIControl.h"
#include "Graphic.h"
#include "FileNode.h"
#include "XMLFileNode.h"
#include "QuadRenderer.h"
#include "glad/gl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace DavinciEngine;

UIControl::UIControl() : Transform()
{
}

UIControl::~UIControl()
{
}

void UIControl::Update()
{
	// Virtual function
}

void UIControl::Render(const glm::mat4& projection)
{
    if (!this->m_bIsEnabled)
        return;

    if (m_pGraphic)
    {
        // 1. Calculate UI Scale 
        // UI needs a size, otherwise it's just a 1x1 pixel quad.
        glm::vec2 size = m_pGraphic->GetSize() * scale;

        // 2. Build the Model Matrix
        // UI usually uses Top-Left as (0,0), so we keep the centering offset.
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position + (size * 0.5f), 0.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));

        // 3. Draw
        // Use 'projection' directly instead of camera 'vp' to keep UI static
        QuadRenderer::DrawQuad(
            projection,
            model,
            m_pGraphic->GetTextureID(),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f)
        );
    }
}

void UIControl::InputChecks()
{
	// Virtual function
}

const bool UIControl::IsEnabled() const
{
	return this->m_bIsEnabled;
}