#ifdef VertexShader

layout (location = 0) in vec4 aColor;
layout (location = 1) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{
       	gl_Position = projection * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
}

#endif

#ifdef FragmentShader

in vec2 TexCoord;

uniform sampler2D Texture;

out vec4 FragColor;

void main()
{
        vec4 texColor = texture(Texture, TexCoord);
        
        // ✅ Opcjonalnie: przyciemnij tylną stronę
        if(!gl_FrontFacing)
        {
            texColor *= 0.7;  // Ciemniejsza od tyłu
        }
        
        FragColor = texColor;
}

#endif