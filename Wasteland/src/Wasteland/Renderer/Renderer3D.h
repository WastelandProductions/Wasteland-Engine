#pragma once

#include "Wasteland/Renderer/Camera.h"
#include "Wasteland/Renderer/EditorCamera.h"
#include "Wasteland/Renderer/Shader.h"
#include "Wasteland/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Wasteland {

    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const glm::mat4& transform);
        static void BeginScene(const EditorCamera& camera);
        static void EndScene();

        // Primitive 3D drawing functions mimicking 2D
        static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
        static void DrawCube(const glm::mat4& transform, const glm::vec4& color, int textureIndex = 0);

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
    };

}