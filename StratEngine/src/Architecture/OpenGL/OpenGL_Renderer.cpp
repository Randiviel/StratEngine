#include "pchstrat.h"
#include "StratConfig.h"
#include "OpenGL_Renderer.h"

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
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            auto& entities = m_Scene->GetEntities();
            auto it = entities.find("Light");
            auto& transform = it->second.GetComponent<TransformComponent>();
            auto& light = it->second.GetComponent<LightComponent>();
            glUseProgram(m_Shader->GetShader());
            m_Shader->CalculateMartix(camera);
            m_Shader->setVec3("LightPos", transform.Position);
            m_Shader->setVec3("LightColor", light.Color);
            m_Shader->setVec3("ViewPos", camera.GetPosition());
            m_Shader->setVec3("ObjectColor", glm::vec3(0.5f, 0.2f, 0.4f));
            m_Shader->setBool("UseTexture", true);
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

    void OpenGL_Renderer::DrawMesh(Entity& entity)
    {
        auto& mesh = entity.GetComponent<MeshComponent>();
        auto& transform = entity.GetComponent<TransformComponent>();
        mesh.VAO->Bind();
        glBindTexture(GL_TEXTURE_2D, mesh.Texture);
        m_Shader->setMat4("model", transform.GetModelMatrix());
        glDrawArrays(GL_TRIANGLES, 0, mesh.Vertices.size());
    }

    void OpenGL_Renderer::DrawDebug(DrawMode mode, Entity &entity)
    {
        auto& mesh = entity.GetComponent<MeshComponent>();
        auto& transform = entity.GetComponent<TransformComponent>();
        mesh.VAO->Bind();
        m_Shader->setMat4("model", transform.GetModelMatrix());

        switch(mode)
        {
            case DrawMode::LINES:
            {
                glDrawArrays(GL_LINES, 0, mesh.Vertices.size());
                break;
            }
            case DrawMode::POINTS:
            {
                glDrawArrays(GL_POINTS, 0, mesh.Vertices.size());
                break;
            }
            case DrawMode::TRIANGLES:
            {
                glDrawArrays(GL_TRIANGLES, 0, mesh.Vertices.size());
                break;
            }
            case DrawMode::POLYGONS:
            {
                glDrawArrays(GL_POLYGON, 0, mesh.Vertices.size());
                break;
            }
            case DrawMode::QUADS:
            {
                glDrawArrays(GL_QUADS, 0, mesh.Vertices.size());
                break;
            }
            case DrawMode::LINES_STRIP:
            {
                glDrawArrays(GL_LINE_STRIP, 0, mesh.Vertices.size());
                break;
            }
        }

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

