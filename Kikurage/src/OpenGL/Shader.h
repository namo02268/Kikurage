#pragma once

#include <string>

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	unsigned int m_id = 0;
	static unsigned int CurrentlyAttachedShader;

	void FreeProgram();

public:
	Shader();
	Shader(const Shader&) = delete;
	Shader(Shader&& shader) noexcept;
	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&& shader) noexcept;
	~Shader();
	 
	void Bind() const;
	void Unbind() const;
	unsigned int GetHandle() const { return this->m_id; }

	int GetUniformLocation(const char* name) const;
	void SetUniform(const char* name, const bool       value) const;
	void SetUniform(const char* name, const int        value) const;
	void SetUniform(const char* name, const float      value) const;
	void SetUniform(const char* name, const glm::vec2& value) const;
	void SetUniform(const char* name, const glm::vec3& value) const;
	void SetUniform(const char* name, const glm::vec4& value) const;
	void SetUniform(const char* name, const glm::mat4& value) const;

	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

private:
	void checkCompileErrors(unsigned int object, std::string type);
};