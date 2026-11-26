#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

// read a whole text file into a string ("" if it can't be opened)
static string readFile(const string& path) {
    ifstream file(path);
    if (!file) {
        cout << "failed to open file: " << path << endl;
        return "";
    }
    stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// compile one shader stage; prints the info log on failure
static GLuint compileShader(GLenum type, const string& source, const string& path) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        cout << "shader compile error in " << path << ":\n" << log << endl;
    }
    return shader;
}

Shader::Shader(const string& vertPath, const string& fragPath) {
    string vCode = readFile(vertPath);
    string fCode = readFile(fragPath);

    GLuint vs = compileShader(GL_VERTEX_SHADER, vCode, vertPath);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fCode, fragPath);

    m_id = glCreateProgram();
    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);

    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(m_id, 512, nullptr, log);
        cout << "program link error (" << vertPath << " + " << fragPath << "):\n" << log << endl;
    }

    // the program keeps the compiled code; these are no longer needed
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::setFloat(const string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}