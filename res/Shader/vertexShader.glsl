#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTextureCoords;
    out vec3 angleColor;
    out vec2 textureCoords;

    uniform mat4 projection;
    uniform mat4 model;
    uniform mat4 view;

    void main()
    {
       textureCoords = aTextureCoords;
       angleColor = aColor;
       gl_Position = projection * view * model * vec4(aPos, 1.0f);
    }