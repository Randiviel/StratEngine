#include "pchstrat.h"
#include "OpenGL_Renderer.h"
#include "StratConfig.h"

namespace StratEngine 
{
    OpenGL_Renderer::OpenGL_Renderer() : m_Shader(nullptr)
    {
        InitFrameBuffer();
        glGenTextures(1, &m_DefaultTexture);
        glBindTexture(GL_TEXTURE_2D, m_DefaultTexture);

        unsigned char magenta[] = {255, 0, 255, 255}; // Fioletowy
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, 
                    GL_RGBA, GL_UNSIGNED_BYTE, magenta);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGL_Renderer::~OpenGL_Renderer()
    {
        std::cout << "Destroying OpenGL_Renderer" << std::endl;
    }

    void OpenGL_Renderer::BeginScene(Camera& camera)
    {       
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);     
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            glUseProgram(m_Shader->GetShader());
        if(m_EditorCamera == nullptr)
            m_Shader->CalculateMartix(camera);
        else
            m_Shader->CalculateMartix(*m_EditorCamera);

    }

    void OpenGL_Renderer::EndScene()
    {
        glUseProgram(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }

    void OpenGL_Renderer::RenderModel(Model& model)
    {
        auto& transform = model.GetTransformComponent();
            for(auto & [name, mesh] : model.GetMeshes())
            {
                mesh.VAO.Bind();
                
                if(mesh.Texture != 0)
                    glBindTexture(GL_TEXTURE_2D, mesh.Texture);
                else
                    glBindTexture(GL_TEXTURE_2D, m_DefaultTexture);

                glm::mat4 matrixModel        = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                matrixModel = glm::translate(matrixModel, transform.GetPosition());
                matrixModel = glm::scale(matrixModel, transform.GetScale());
                m_Shader->setMat4("model", matrixModel);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }   
    }

    void OpenGL_Renderer::SetShader(Shader &shader)
    {
        m_Shader = &shader;
    }

    void OpenGL_Renderer::InitFrameBuffer()
    {
    // Stwórz teksturę
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH, 
                 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Stwórz framebuffer
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                           GL_TEXTURE_2D, m_Texture, 0);
    
    // Renderbuffer dla głębi
    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 
                          StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 
                              GL_RENDERBUFFER, m_RBO);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer nie jest kompletny!\n");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

