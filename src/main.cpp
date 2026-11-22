#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <cstddef>
#include <cstddef>
#include <iostream>
#include <cmath>
using namespace std;



// vertex shader 
// R--- raw string in cpp
const char* vSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vColor;

void main(){
    vColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fSrc = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main(){
    FragColor = vec4(vColor, 1.0);
}
)";

//  compiler function
GLuint compileShader(GLenum type, const char* source){
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    // checkin for errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        cout << "shader compilation error:: " << (type == GL_VERTEX_SHADER? "vertex" : "frag") << "::\n"<<log<<endl;
    }
    return shader;
}





// helper: it links both shaders to a program, that is than used to draw

GLuint createProgram(const char* Vsrc, const char* Fsrc){
    GLuint vs = compileShader(GL_VERTEX_SHADER, Vsrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, Fsrc);
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success){
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        cout << "program link error:: \n"<<log<< endl;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}



int main (){
    // start GLFW
    if (!glfwInit()){
        cout<<"Failed to init GLFW\n";
        return 1;
    }
    // ask for context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Minecraft", nullptr, nullptr);
    if(!window){
        cout<<"failed to create window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // time to use glew: loading opengl functions
    GLenum error = glewInit();
    if(error!= GLEW_OK && error!= GLEW_ERROR_NO_GLX_DISPLAY){
        cout << "failed to init glew: "<< glewGetErrorString(error)<<endl;
        glfwTerminate();
        return 1;
    }
    cout << "OpenGl: "<< glGetString(GL_VERSION)<<endl;




    // making program
    GLuint shaderProg = createProgram(vSrc ,fSrc);

    float v[]={
        //     pos                           color
        -1.0f, -1.0f, .0f,  0.5f,   0.5f, 0.5f, 
        .0f, 1.0f,   .0f,    0.5f,  0.5f, 0.5f, 
        .5f, -.5f, .0f, 0.5f, 0.5f, 0.5f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO); // start
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); //end




    // game loop

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents(); // handles input and window events

        if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        glClearColor(sin(glfwGetTime()), 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProg);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); 


        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProg);
    glfwDestroyWindow(window);
    glfwTerminate();
    


    return 0;
}