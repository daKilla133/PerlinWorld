#pragma once

#include <vector>
#include <glew\glew.h>
#include <glm\glm.hpp>

class TerrainMesh
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint size;
	GLuint data_size;
	glm::mat4 model;
public:
	TerrainMesh();
	void addData(float planeY, float triangleSize, int width, int height);
	void draw();

	glm::mat4& getModel() { return model; }
private:
	GLfloat* generateDataMatrix(std::vector<glm::vec3>& positions);
};