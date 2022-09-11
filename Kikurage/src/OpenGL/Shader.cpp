#include "OpenGL/Shader.h"

#include <iostream>

unsigned int Shader::CurrentlyAttachedShader = 0;

Shader::Shader() {}

Shader::Shader(Shader&& shader) noexcept {
    this->m_id = shader.m_id;
    shader.m_id = 0;
}

Shader& Shader::operator=(Shader&& shader) noexcept {
    this->m_id = shader.m_id;
    shader.m_id = 0;

    return *this;
}

Shader::~Shader() {
    this->FreeProgram();
}

void Shader::Bind() const {
    glUseProgram(this->m_id);
    Shader::CurrentlyAttachedShader = this->m_id;
}

void Shader::Unbind() const {
    glUseProgram(0);
    Shader::CurrentlyAttachedShader = 0;
}

void Shader::FreeProgram() {
    if (this->m_id != 0) {
        glDeleteProgram(this->m_id);
        this->m_id = 0;
    }
}

int Shader::GetUniformLocation(const char* name) const {
    return glGetUniformLocation(this->m_id, name);
}

void Shader::SetUniform(const char* name, const bool value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniform1i(this->GetUniformLocation(name), static_cast<int>(value));
}

void Shader::SetUniform(const char* name, const int value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniform1i(this->GetUniformLocation(name), value);
}

void Shader::SetUniform(const char* name, const float value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniform1f(this->GetUniformLocation(name), value);
}

void Shader::SetUniform(const char* name, const glm::vec2& value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniform2f(this->GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniform(const char* name, const glm::vec3& value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniform3f(this->GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniform(const char* name, const glm::vec4& value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniform4f(this->GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const char* name, const glm::mat4& value) const {
    if (this->m_id != Shader::CurrentlyAttachedShader)
        this->Bind();
    glUniformMatrix4fv(this->GetUniformLocation(name), 1, false, glm::value_ptr(value));
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    this->m_id = glCreateProgram();
    glAttachShader(this->m_id, sVertex);
    glAttachShader(this->m_id, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->m_id, gShader);
    glLinkProgram(this->m_id);
    checkCompileErrors(this->m_id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}