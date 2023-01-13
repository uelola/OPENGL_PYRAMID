#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>
#include "src/Shader.h"
#include <stb_image/stb_image.h>
#include "stb_image/stb_image.h"


// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // Cube    
       /* Bottom position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,      
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,       
         0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        
         0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,         
        -0.5f,  0.5f, -0.5f,        1.0f, 0.0f, 1.0f,        0.0f, 1.0f,      
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,
       /* Front position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,      
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,       
         0.0f,  0.0f,  0.5f,        0.0f, 0.0f, 1.0f,        0.5f, 1.0f, 
       /* Back position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f,  0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,      
         0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,       
         0.0f,  0.0f,  0.5f,        0.0f, 0.0f, 1.0f,        0.5f, 1.0f,  
       /* Left position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,      
        -0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,       
         0.0f,  0.0f,  0.5f,        0.0f, 0.0f, 1.0f,        0.5f, 1.0f,   
       /* Right position */  /* Color for each angle */ /* Texture coordinated */ 
         0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,      
         0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,       
         0.0f,  0.0f,  0.5f,        0.0f, 0.0f, 1.0f,        0.5f, 1.0f,   
    }; 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);

unsigned int load_texture(const char* texture_path);

glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;
glm::vec3 myPos = glm::vec3(0.0f);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /* The most important part */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_cursor_position);
    glfwSetScrollCallback(window, mouse_scroll_position);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Depth for top part */
    glEnable(GL_DEPTH_TEST);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
   
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

    /* Position Attribute, at 5th place '6' because in vertices array a row now consist of 6 floats  */ 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //start from '0'
    glEnableVertexAttribArray(0);

    /* Color Attribute */ 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // last '3' is the offset from prrrevious line
    glEnableVertexAttribArray(1);

    /* Texture Attribute                                               offset, will start after position 6*/                                                      
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // last '3' is the offset from prrrevious line
    glEnableVertexAttribArray(2);

     /* Texture */
     stbi_set_flip_vertically_on_load(true);
     // unsigned int texture = load_texture("res/Texture/wooden-box.jpg"); 
     // unsigned int pyramid_texture = load_texture("res/Texture/pyramid_texture.jpg"); 
     unsigned int pyramid_texture1 = load_texture("res/Texture/pyramid_texture1.jpg"); 

     /* Shader */
    Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
    myShader.use();
    // the 1st texture (wooden container)
    // myShader.setInt("texture1", 0);
    // myShader.setInt("pyramid_texture", 1);
    myShader.setInt("pyramid_texture1", 2);


    // render game loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        userInput(window);

        // update color 
        float time = glfwGetTime();

        //prevent a delay in changing colors when going to negative, 0.0f - 1.0f
        // float xValue = std::sin(time) / 2.0f + 0.5f; 
        // float yValue = std::cos(time) / 2.0f + 0.5f; 
        // float zValue = std::cos(time) / 2.0f + 0.5f; 

        float xValue = std::cos(time) / 2.0f + 0.5f; 
        float yValue = std::sin(time) / 2.0f + 0.5f; 
        float zValue = std::cos(time) / 2.0f + 0.5f; 

        

        // vector for color
        glm::vec3 myVector;
		// myVector.x = 1.0f;
		// myVector.y = 0.5f;
		myVector.z = 0.31f;
        myVector.x = xValue;
		myVector.y = yValue;
		// myVector.z = zValue;

		// Or use this.
		myShader.setVec3("colors", myVector);

        /* Coordinates */
        // projection
        projection = glm::perspective(glm::radians(45.0f),float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
        myShader.setMat4("projection", projection);
        // view
        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f)); //negative z coord shown at the back
        myShader.setMat4("view", view);
        // model
        model = glm::mat4(1.0f);
        // for spinning around x-axis (* time)
        //model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(1.0f, 0.3f, 0.0f));
        // for spinning around x-axis diagonally (* time)
        //model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(1.0f, 0.3f, 0.7f));
        model = glm::translate(model, glm::vec3(myPos)); // position
        myShader.setMat4("model", model);

        /* render */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glBindVertexArray(VAO);
        // glActiveTexture(GL_TEXTURE0); // NOTE: GL_TEXTURE0 already activated by defualt
        // glBindTexture(GL_TEXTURE_2D, texture);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, pyramid_texture);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, pyramid_texture1);
        glDrawArrays(GL_TRIANGLES, 0, 18);
       
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glfwDestroyWindow(window);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void userInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        myPos.y += 0.02f;
    
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        myPos.y -= 0.02f;
    
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        myPos.x += 0.02f;
    
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        myPos.x -= 0.02f;
    
        
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos) {
//    std::cout << "Position : " << xpos << " " << ypos << "\n";
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset) {
    // std::cout << "Scrollhas been moved\n";
    // std::cout << "Offsets: " << xoffset << " " << yoffset << "\n";
}

unsigned int load_texture(const char* texture_path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    /* Filters Options*/

    // Note : Don't take care so much about this filters if rn, if you would like you can delete. 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth, textureHeight, innerChannels;  /* differenciate between jpg, png */
    unsigned char* data = stbi_load(texture_path, &textureWidth, &textureHeight, &innerChannels, 0);

    if(data){
        /* Note it's a better way to see that what our file is like png, jpg or jpeg */
		GLenum format;
		if (innerChannels == 1)
			format = GL_RED;
		if (innerChannels == 3) // jpg file
			format = GL_RGB;
		if (innerChannels == 4) // png file
			format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture\n";
    }

    stbi_image_free(data);

    return texture;

}

