#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <cstddef>
#include <iostream>
// #include <cmath>
using namespace std;



// vertex shader 
// R--- raw string in cpp
const char* vSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;



uniform float uTime;

out vec3 vColor;

void main(){
    vColor = aColor;
    vec3 pos = aPos;
    pos.x += 0.5 * sin(uTime);
    gl_Position = vec4(pos, 1.0);
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
 
// resize
void resize(GLFWwindow* window, int width, int height){
    (void)window; // something neccessary
    glViewport(0, 0, width, height);
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
    glfwSetFramebufferSizeCallback(window, resize);
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

    GLint uLocation = glGetUniformLocation(shaderProg, "uTime");
    if(uLocation==-1){
        cout<<"warning 'uniform -uTime- not found\n";
    }

    float v[]={
        //     pos                           color
       -.5f, .5f, .0f,      0.0f, 0.5f, 0.0f,
        .5f, .5f, .0f,      0.0f, 0.5f, 0.0f,
        .5f,-.5f, .0f,  0.0f, 0.5f, 0.0f,
       -.5f,-.5f, .0f,  0.0f, 0.5f, 0.0f

    };

    unsigned int indeces[]={
        0,3, 2,
        1,0,2
    };
    



    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO); // start
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

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
        glClearColor(0.5f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProg);


        glUniform1f(uLocation, (float)glfwGetTime());


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES , 6, GL_UNSIGNED_INT, nullptr); 


        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(shaderProg);
    glfwDestroyWindow(window);
    glfwTerminate();
    


    return 0;
}