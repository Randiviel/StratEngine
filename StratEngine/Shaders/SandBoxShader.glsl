#ifdef VertexShader

layout (location = 0) in vec3 aPos;

void main()
{
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

#endif

#ifdef FragmentShader

out vec4 FragColor;
void main()
{
        FragColor = vec4(0.2f, 0.5f, 0.2f, 1.0f);
}

#endif