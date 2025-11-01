#ifdef VertexShader

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
       	gl_Position = projection * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;  
}

#endif

#ifdef FragmentShader

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Texture;
uniform vec3 LightPos;
uniform vec3 ViewPos;
uniform vec3 LightColor;
uniform vec3 ObjectColor;
uniform bool UseTexture; // Przełącznik

out vec4 FragColor;

void main()
{

        
        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * LightColor;
                
        // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * LightColor;
        
        // specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(ViewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * LightColor;  
        
        vec3 lighting = ambient + diffuse + specular;
        
        vec3 baseColor;
        if (UseTexture) {
            baseColor = texture(Texture, TexCoord).rgb;
        } else {
            baseColor = ObjectColor;
        }
        
        vec3 result = lighting * baseColor;
        FragColor = vec4(result, 1.0);
}

#endif

        // TYMCZASOWO - pokaż normalne jako kolory
        // FragColor = vec4(normalize(Normal) * 0.5 + 0.5, 1.0);
        // return;
        
        // TYMCZASOWO - pokaż samą teksturę bez oświetlenia
        // FragColor = vec4(texture(Texture, TexCoord).rgb, 1.0);
        // return;

        // DEBUG - pokaż wartość lighting
        // FragColor = vec4(lighting, 1.0);
        // return;