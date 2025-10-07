#pragma once

namespace StratEngine 
{
    class OpenGL_VArray : public VertexArray 
    {
        public:
            OpenGL_VArray();
            ~OpenGL_VArray();
            
            virtual void Bind() const override;
            virtual void Unbind() const override; 
            virtual void AddBuffer(VertexBuffer& vertexBuffer) override;
            virtual void BindShaderAttrib(const std::vector<ShaderAttributes>& attributes) override;
        private:
            unsigned int m_VertexArrayID;
            std::vector<ShaderAttributes> m_ShaderAttributes;
    };
}