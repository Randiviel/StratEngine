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

    void OpenGL_Renderer::RenderModel(Model& model)
    {
        auto& transform = model.GetTransformComponent();
            for(auto & [name, mesh] : model.GetMeshes())
            {
                mesh.VAO.Bind();
                glm::mat4 matrixModel        = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

                if(model.GetTransformComponent().GetMoveDirection() != glm::vec3{0.0f, 0.0f, 0.0f})
                {
                    matrixModel = glm::translate(matrixModel, transform.GetMoveDirection());
                }
                m_Shader->setMat4("model", matrixModel);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        transform.SetMoveDirection(glm::vec3{0.0f, 0.0f, 0.0f});
    }

    void OpenGL_Renderer::SetShader(Shader &shader)
    {
        m_Shader = &shader;
    }

}
