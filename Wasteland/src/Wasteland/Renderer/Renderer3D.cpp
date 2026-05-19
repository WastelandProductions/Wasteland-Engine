#include "wlpch.h"
#include "Renderer3D.h"

#include "Wasteland/Renderer/Renderer.h"

namespace Wasteland {

    void Renderer3D::Init()
    {
        WL_PROFILE_FUNCTION();
        // Minimal init for Renderer3D. Expand later with meshes, materials, etc.
    }

    void Renderer3D::Shutdown()
    {
        WL_PROFILE_FUNCTION();
    }

    void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
    {
        WL_PROFILE_FUNCTION();
        glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);
        Renderer::SetViewProjection(viewProj);
    }

    void Renderer3D::BeginScene(const EditorCamera& camera)
    {
        WL_PROFILE_FUNCTION();
        Renderer::SetViewProjection(camera.GetViewProjection());
    }

    void Renderer3D::EndScene()
    {
        WL_PROFILE_FUNCTION();
    }

    void Renderer3D::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        WL_PROFILE_FUNCTION();
        Renderer::Submit(shader, vertexArray, transform);
    }

}