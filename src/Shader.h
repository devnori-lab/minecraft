#pragma once
#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <glm/glm.hpp>


// owns one opengl shader program (vertex + fragment), loaded from files.
class Shader {
public:
    Shader(const std::string& vertPath, const std::string& fragPath);
    ~Shader();

    // no copying: two objects would delete the same program
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void use() const;
    void setFloat(const std::string& name, float value) const;

    void setMat4(const std::string& name, const glm::mat4& value) const;

    GLuint id() const { return m_id; }

private:
    GLuint m_id = 0;
};