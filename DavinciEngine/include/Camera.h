#pragma once
#include "Transform.h"

namespace DavinciEngine
{
    class OrthographicCamera : public Transform {
    public:
        glm::mat4 projectionMatrix;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="width">Width of camera (usually the width of the window)</param>
        /// <param name="height">Height of camera (usually the height of the window)</param>
        OrthographicCamera(float width, float height) {
            // Create an orthographic projection using GLM
            projectionMatrix = glm::ortho(0.0f, width, height, 0.0f, -100.0f, 100.0f);
        }

        // View matrix is the inverse of the camera's world transform
        glm::mat4 GetViewMatrix() const {
            // Efficient way to get camera view without manual inversion:
            // Position is negated, and rotation is applied in reverse order.
            return glm::inverse(GetModelMatrix());
        }

        glm::mat4 GetViewProjection() const {
            return projectionMatrix * GetViewMatrix();
        }
    };
}