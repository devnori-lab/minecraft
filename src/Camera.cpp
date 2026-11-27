#include "Camera.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <cmath>
#include <glm/trigonometric.hpp>
using namespace std;


Camera::Camera(glm::vec3 startPos){
    position = startPos;
}

glm::vec3 Camera::getFront() const{
    float y = glm::radians(yaw);
    float p = glm::radians(pitch);
    glm::vec3 front(cos(y)*cos(p), sin(p), sin(y)*cos(p));
    return glm::normalize(front);
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position+getFront(), glm::vec3(0.0f,1.0f,0.0f));
}

void Camera::MouseControl(float dx, float dy){
    yaw += dx * sensitivity;
    pitch -= dy * sensitivity;
    pitch = clamp(pitch, -89.0f, 89.0f); // to never look exactly up/down straight
}
void Camera::move(float forward, float right,float up, float dt){
    float y = glm::radians(yaw);
    glm::vec3 flatfront(cos(y), 0.0f, sin(y));
    glm::vec3 flatright(-sin(y), 0.0f, cos(y));
    glm::vec3 worldup(0.0f, 1.0f, 0.0f);
    glm::vec3 dir = flatfront*forward + flatright*right + worldup*up;
    if (glm::length(dir)>0.0f){
        dir=glm::normalize(dir);
    }
    position+=dir*speed*dt;
}