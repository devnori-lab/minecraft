#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <cstddef>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"
// #include <cmath>
using namespace std;


 
// resize
void resize(GLFWwindow*, int width, int height){
    //(void)window; // not needed
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


    // hides and lock the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(glfwRawMouseMotionSupported()){
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSwapInterval(1);//vsync: waiting for monitor refresh

    {
        Shader shader(ASSET_DIR "shaders/basic.vert", ASSET_DIR "shaders/basic.frag");
        
        
        
        // cube data template
        float v[] = {   
            //   x        y           z           r           g       b
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // 0 front bottom-left
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // 1 front bottom-right
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // 2 front top-right
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   // 3 front top-left
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,   // 4 back bottom-left
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,   // 5 back bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // 6 back top-right
            -0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.2f,   // 7 back top-left
        };

        // 6 faces x 2 triangles x 3 indices = 36
        // each triangle is counter-clockwise when seen from OUTSIDE the cube
        unsigned int indeces[] = {
            0, 1, 2,  2, 3, 0,   // front  (+z)
            5, 4, 7,  7, 6, 5,   // back   (-z)
            4, 0, 3,  3, 7, 4,   // left   (-x)
            1, 5, 6,  6, 2, 1,   // right  (+x)
            3, 2, 6,  6, 7, 3,   // top    (+y)
            4, 5, 1,  1, 0, 4,   // bottom (-y)
        };

















        // // making program
        // GLuint shaderProg = createProgram(vSrc ,fSrc);

        // GLint uLocation = glGetUniformLocation(shaderProg, "uTime");
        // if(uLocation==-1){
        //     cout<<"warning 'uniform -uTime- not found\n";
        // }

        



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


        glEnable(GL_DEPTH_TEST); // going 3d!!
        glEnable(GL_CULL_FACE); // back of triangle becomes invisible
        

        Camera camera(glm::vec3(0.0f,0.0f, 3.0f));
        double lastX, lastY;
        glfwGetCursorPos(window, &lastX, &lastY);
        double lastTime = glfwGetTime();

        // game loop

        while (!glfwWindowShouldClose(window)){
            glfwPollEvents(); // handles input and window events

            // camera control
            double time = glfwGetTime();
            float dt = (float)(time-lastTime);
            lastTime=time;
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            camera.MouseControl((float)(mx-lastX), (float)(my-lastY));
            lastX = mx;
            lastY = my;

            // player movements
            float f=0.0f, r=0.0f, u=0.0f;
            if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS) f+=1.0f;
            if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS) f-=1.0f;
            if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS) r+=1.0f;
            if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS) r-=1.0f;
            if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS) u+=1.0f;
            if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS) u-=1.0f;
            camera.move(f,r,u,dt);

            //

            if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
                glfwSetWindowShouldClose(window, true);
            }
            glClearColor(0.5f, 0.8f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // pipe means both buffer get delete simultaneously

            // glUseProgram(shaderProg);
            shader.use(); // program is used here // every update comes after this

            // glUniform1f(uLocation, (float)glfwGetTime());
            // shader.setFloat("uTime", (float)glfwGetTime());

            int fbw, fbh; // frame buffer width/height
            glfwGetFramebufferSize(window, &fbw, &fbh);
            // float aspect = fbw/fbh;
            float aspect = (fbh>0) ? (float)fbw/(float)fbh : 1.0f;

            // glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); // vec3 is the axis of rotation

            // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // camera at a distance
            glm::mat4 view = camera.getViewMatrix();
        
            glm::mat4 projection = glm::perspective(glm::radians(camera.fov), aspect, 0.1f, 100.0f);



            // shader.setMat4("uModel", model);
            shader.setMat4("uView", view);
            shader.setMat4("uProjection", projection);

            glBindVertexArray(VAO);
            for (int x = -5; x < 5; x++) {
                for (int z = -5; z < 5; z++) {
                    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((float)x, -2.0f, (float)z));
                    shader.setMat4("uModel", model);
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
                }
            }
            glDrawElements(GL_TRIANGLES , 36, GL_UNSIGNED_INT, nullptr); 


            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    
    // glDeleteProgram(shaderProg);
    glfwDestroyWindow(window);
    glfwTerminate();
    


    return 0;
}