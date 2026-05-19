#pragma once

#include "Wasteland/Renderer/Camera.h"
#include "Wasteland/Renderer/EditorCamera.h"
#include "Wasteland/Renderer/Shader.h"
#include "Wasteland/Renderer/VertexArray.h"

namespace Wasteland {

    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const glm::mat4& transform);
        static void BeginScene(const EditorCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
    };

}