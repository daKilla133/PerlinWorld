#include "Shader.h"
#include "Texture.h"
#include <Windows.h>
//adharsh to that 
std::string read_file(const char* filepath)
{
	FILE* file = fopen(filepath, "rt");	//we read as t -> textfile bc if b -> bytes then it would all be in one line like in bytes
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file); // binary streams -> number of bytes, text streams -> number of characters

	char* data = new char[length + 1]; // + Termination character
	memset(data, 0, length + 1);	//use memset to clear away any binary text
	fseek(file, 0, SEEK_SET);	//Back to beginning
	fread(data, 1, length, file);
	fclose(file);

	std::string result(data);
	delete[] data;

	return result;
}

Shader::Shader()
{
	program = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::addVertexShader(const char* file)
{
	addProgram(file, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(const char* file)
{
	addProgram(file, GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShader(const char* file)
{
	addProgram(file, GL_FRAGMENT_SHADER);
}

void Shader::addProgram(const char* file, GLenum type)
{
	GLuint shaderID = glCreateShader(type);

	std::string shaderSourceString = read_file(file);
	const char* shaderSource = shaderSourceString.c_str();

	if (shaderID == 0)
	{
		std::cout << "Shader creation failed: Could not find valid memory location when adding shader" << std::endl;
		system("pause");
		return;
	}

	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	GLint result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(shaderID, length, &length, &error[0]);
		std::cout << "Failed to compile shader!\tType of Shader: " << type << std::endl << &error[0] << std::endl;
		glDeleteShader(shaderID);
		system("pause");
		return;
	}

	glAttachShader(program, shaderID);
	shaders.push_back(shaderID);
}

void Shader::compileShader()
{
	glLinkProgram(program);

	GLint success; GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		system("PAUSE");
	}

	glValidateProgram(program);

	for (unsigned int i = 0; i < shaders.size(); i++)
		glDeleteShader(shaders[i]);
}


GLuint Shader::load(const char* vertexShader, const char* fragShader)
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//use c_str() like this so string is not immediately destroyed and pointer is not able to be found
	std::string vertSourceString = read_file(vertexShader);
	std::string fragSourceString = read_file(fragShader);

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	//*********Vertex Shader
	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(vertex);
		system("pause");
		return EXIT_FAILURE;
	}

	//*********Fragment Shader
	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(fragment);
		system("pause");
		return EXIT_FAILURE;
	}
	std::cout << "Program: " << program << std::endl;
	std::cout << "Vertex Shader: " << vertex << std::endl;
	std::cout << "Fragment Shader: " << fragment << std::endl;

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}



void Shader::bind() const
{
	glUseProgram(program);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

GLint Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(program, name);
}

void Shader::setUniform1f(const GLchar* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1fv(const GLchar* name, float* value, int count)
{
	glUniform1fv(getUniformLocation(name), count, value);
}

void Shader::setUniform1iv(const GLchar* name, int* value, int count)
{
	glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::setUniform1i(const GLchar* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}
void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

BasicShader::BasicShader()
{
	addVertexShader("res/shaders/vertexshader.vs");
	addFragmentShader("res/shaders/fragmentshader.fs");
	compileShader();
}

void BasicShader::updateUniforms(glm::mat4& projectionMatrix, Texture& texture)
{
	if (texture.hasImage())
		texture.bind();
	//else
	//	texture.unbind();
	static long counter = 0;
	counter++;
	setUniformMat4("transform", projectionMatrix);
	setUniform1i("usingColor", 0);
	setUniform1f("time", ((float)counter) / 100.0f);
}

void BasicShader::updateUniforms(glm::mat4& projectionMatrix, glm::vec4 const& color)
{
	setUniformMat4("transform", projectionMatrix);
	setUniform4f("color", color);
	setUniform1i("usingColor", 1);
	setUniform1f("time", (float)GetTickCount() / 10000.0f);
}