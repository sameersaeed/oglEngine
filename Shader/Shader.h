#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int id;                                            // program id
    Shader(const char* vertexPath, const char* fragmentPath);   // reads and builds shader
    void use();                                                 // activates shader

    void setBool(const std::string& name, bool value) const     // loading uniform variables
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
    }

    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void setVec2(const std::string& name, float a, float b) const
    {
        glUniform2f(glGetUniformLocation(id, name.c_str()), a, b);
    }

    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string& name, float a, float b, float c) const
    {
        glUniform3f(glGetUniformLocation(id, name.c_str()), a, b, c);
    }

    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string& name, float a, float b, float c, float d) const
    {
        glUniform4f(glGetUniformLocation(id, name.c_str()), a, b, c, d);
    }

    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void setMat2(const std::string& name, const glm::mat2& value) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void setMat3(const std::string& name, const glm::mat3& value) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void setMat4(const std::string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
