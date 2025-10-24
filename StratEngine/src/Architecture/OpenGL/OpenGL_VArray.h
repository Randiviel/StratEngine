#pragma once
#include "Renderer/VertexArray.h"


namespace StratEngine 
{
    class OpenGL_VArray : public VertexArray 
    {
        public:
            OpenGL_VArray();
            ~OpenGL_VArray();
            
            virtual void Bind() const override;
            virtual void Unbind() const override; 
            void BindShaderAttrib(const std::vector<ShaderAttributes>& attributes);
            void CalculateShaderAttrib();
            inline const unsigned int GetID() const { return m_VertexArrayID; };
        private:
            unsigned int m_VertexArrayID;
            std::vector<ShaderAttributes> m_ShaderAttributes;
        private:
    };
}