#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
using namespace std;



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
        return 1;
    }
    cout << "OpenGl: "<< glGetString(GL_VERSION);

    // game loop

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents(); // handles input and window events

        if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        glClearColor(sin(glfwGetTime()), 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    


    return 0;
}