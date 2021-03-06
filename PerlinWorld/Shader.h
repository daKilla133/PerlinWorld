#pragma once
#include <iostream>
#include <vector>

#include <glew\glew.h>
#include <glm\glm.hpp>

class Texture;

class Shader
{
private:
	GLuint program;
	std::vector<GLuint> shaders;
public:
	Shader();
	~Shader();

	void addVertexShader(const char* s);
	void addGeometryShader(const char* s);
	void addFragmentShader(const char* s);
	void addProgram(const char* s, GLenum type);
	void compileShader();

	GLuint load(const char* vertexShader, const char* fragShader);

	void setUniform1f(const GLchar* name, float value);
	void setUniform1fv(const GLchar* name, float* value, int count);
	void setUniform1i(const GLchar* name, int value);
	void setUniform1iv(const GLchar* name, int* value, int count);
	void setUniform2f(const GLchar* name, const glm::vec2& vector);
	void setUniform3f(const GLchar* name, const glm::vec3& vector);
	void setUniform4f(const GLchar* name, const glm::vec4& vector);
	void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
	void bind() const;
	void unbind() const;
private:
	GLint getUniformLocation(const GLchar* name);

};

class BasicShader : public Shader
{
public:
	BasicShader();
	void updateUniforms(glm::mat4& projectionMatrix, Texture& texture);
	void updateUniforms(glm::mat4& projectionMatrix, glm::vec4 const& color);
};