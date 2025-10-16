#include "pchstrat.h"


namespace StratEngine 
{
    OpenGL_Renderer::OpenGL_Renderer() : m_Shader(nullptr)
    {

    }

    OpenGL_Renderer::~OpenGL_Renderer()
    {

    }

    void OpenGL_Renderer::BeginScene(Camera& camera)
    {            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            
            glUseProgram(m_Shader->GetShader());
            m_Shader->CalculateMartix(camera);

    }

    void OpenGL_Renderer::EndScene()
    {
        glUseProgram(0);
        glBindVertexArray(0);
    }

    void OpenGL_Renderer::RenderMesh(const Mesh &mesh)
    {
        mesh.VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void OpenGL_Renderer::SetShader(Shader &shader)
    {
        m_Shader = &shader;
    }

}
