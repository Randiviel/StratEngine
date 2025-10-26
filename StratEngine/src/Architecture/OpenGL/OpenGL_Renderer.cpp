#include "pchstrat.h"
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
        STRAT_CORE_WARN("Destroying OpenGL_Renderer!");
    }

    void OpenGL_Renderer::BeginScene(Camera& camera)
    {       
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);     
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);

            glCullFace(GL_BACK);       // Ukryj tylne ściany
            glFrontFace(GL_CCW);       // Przednie ściany = counter-clockwise

            glUseProgram(m_Shader->GetShader());
            m_Shader->CalculateMartix(camera);
    }

    void OpenGL_Renderer::EndScene()
    {
        glUseProgram(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }

    void OpenGL_Renderer::BindShader(std::shared_ptr<Shader> shader)
    {
        m_Shader = shader;
    }

    void OpenGL_Renderer::DrawMesh(MeshComponent& mesh)
    {
        mesh.VAO->Bind();
        glBindTexture(GL_TEXTURE_2D, mesh.Texture);
        glm::mat4 matrixModel = glm::mat4(1.0f);
        matrixModel = glm::scale(matrixModel, glm::vec3(0.01f, 0.01f, 0.01f));
        m_Shader->setMat4("model", matrixModel);
        glDrawArrays(GL_TRIANGLES, 0, mesh.Vertices.size());
    }

    void OpenGL_Renderer::InitFrameBuffer()
    {
    // Stwórz teksturę
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, StratConfig::WINDOW_WIDTH, StratConfig::WINDOW_HEIGHT, 
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
                          StratConfig::WINDOW_WIDTH, StratConfig::WINDOW_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 
                              GL_RENDERBUFFER, m_RBO);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer nie jest kompletny!\n");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

