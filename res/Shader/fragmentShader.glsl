#version 330 core
    out vec4 FragColor;
    in vec3 angleColor;
    // uniform float xColor;
    // uniform float yColor;
    // uniform float zColor;
    in vec2 textureCoords;
    uniform vec3 colors;
    uniform sampler2D texture1;
    uniform sampler2D pyramid_texture;
    uniform sampler2D pyramid_texture1;
    
    void main()
    {
    // "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // "FragColor = vec4(xColor, yColor, zColor, 1.0f);
    // FragColor = vec4(xColor * angleColor.x, yColor * angleColor.y, zColor * angleColor.z, 1.0f);
    
    // FragColor = vec4(colors * angleColor ,1.0f);
    // FragColor = texture(texture1, textureCoords);
    // rainbow color effect
    // FragColor = texture(texture1, textureCoords) * vec4(angleColor, 1.0f);

    /* split into 4 could be  done from fragment shader*/
    // FragColor = texture(texture1, 2  * textureCoords) * vec4(angleColor * colors, 1.0f);
    // FragColor = texture(texture1, textureCoords) * vec4(angleColor * colors, 1.0f);
    // FragColor = texture(texture1, textureCoords);
    
    // FragColor = texture(pyramid_texture, textureCoords);
    FragColor = texture(pyramid_texture1, textureCoords);
    }