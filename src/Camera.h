#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

class Camera{

    public:
        glm::vec3 position;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float speed = 5.0f;
        float sensitivity = 0.1f;
        float fov = 70.0f;

        explicit Camera(glm::vec3 startPos);

        glm::vec3 getFront() const;
        glm::mat4 getViewMatrix() const;
        void MouseControl(float dx, float dy);
        void move(float forward, float right,float up, float dt);

};