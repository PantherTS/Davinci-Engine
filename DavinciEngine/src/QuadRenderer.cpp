#include "QuadRenderer.h"
#include "LowLevelSystem.h"
#include "AssetManager.h"
#include "ShaderAsset.h"
#include <glad/gl.h>

static unsigned int VAO = 0;
static unsigned int VBO = 0;
static unsigned int EBO = 0;


namespace DavinciEngine
{
	static ShaderAsset* s_shader = nullptr;

	void QuadRenderer::Init()
	{
		s_shader = AssetManager::GetInstance()->RequestShader(
			"assets/shaders/textured_quad.vert",
			"assets/shaders/textured_quad.frag"
		);

		float vertices[] = {
			// pos      // uv
			-0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glDisable(GL_CULL_FACE);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	void QuadRenderer::Shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void QuadRenderer::DrawQuad(
		const glm::mat4& vp, const glm::mat4& model, unsigned int texture, const glm::vec2& uvOffset, const glm::vec2& uvScale)
	{
		s_shader->Bind();

		// Use hardcoded locations (matches shader layout)
		glUniformMatrix4fv(0, 1, GL_FALSE, &vp[0][0]);
		glUniformMatrix4fv(1, 1, GL_FALSE, &model[0][0]);
		glUniform2fv(2, 1, &uvOffset[0]);
		glUniform2fv(3, 1, &uvScale[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(4, 0);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}