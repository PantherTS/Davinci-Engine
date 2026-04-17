#pragma once
#include "FileNode.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DavinciEngine
{
	class Transform
	{
	public:
		/// <summary> The position </summary>
		glm::vec2 position = glm::vec2(0.0f);

		/// <summary> The rotation </summary>
		float rotation = 0.0f; // degrees

		/// <summary> The scale </summary>
		glm::vec2 scale = glm::vec2(1.0f);

		/// <summary> The layer that the object is to be drawn to (-100 - 100) </summary>
		int m_iLayer = 0;

		glm::mat4 GetModelMatrix() const {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0, 0, 1));
			transform = glm::scale(transform, glm::vec3(scale, 1.0f));
			return transform;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Saves the given file.</summary>
		///
		/// <param name="fileNode"> [in,out] If non-null, the FileNode * to save.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Save(FileNode* fileNode)
		{
			if (fileNode)
			{
				if (position != glm::vec2(0.0f))
					fileNode->Write("position", position);
				if (rotation != 0)
					fileNode->Write("rotation", rotation);
				if (scale != glm::vec2(1.0f))
					fileNode->Write("scale", scale);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the given file.</summary>
		///
		/// <param name="fileNode"> [in,out] If non-null, the FileNode * to load.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Load(FileNode* fileNode)
		{
			if (fileNode)
			{
				fileNode->Read("position", position);
				fileNode->Read("rotation", rotation);
				fileNode->Read("scale", scale);
			}
		}
	};
}