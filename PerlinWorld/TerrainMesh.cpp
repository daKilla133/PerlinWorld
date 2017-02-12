#include "TerrainMesh.h"

TerrainMesh::TerrainMesh()
{
	size = 0;
	data_size = 0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
}

void TerrainMesh::addData(float planeY, float triangleSize, int width, int height)
{
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> positions;

	for (int yCounter = 0, float y = -(triangleSize * height) / 2; y < (triangleSize * height) / 2; y += triangleSize, yCounter++)
	{
		if (yCounter % 2 == 0)
		{
			for (float x = -(triangleSize * width) / 2; x <= (triangleSize * width) / 2; x += triangleSize)
			{
				positions.emplace_back(new glm::vec3(x, planeY, y));
				positions.emplace_back(new glm::vec3(x, planeY, y + triangleSize));
			}
		}
		else
		{
			for (float x = (triangleSize * width) / 2;  x >= -(triangleSize * width) / 2; x -= triangleSize)
			{
				positions.emplace_back(new glm::vec3(x, planeY, y));
				positions.emplace_back(new glm::vec3(x, planeY, y + triangleSize));
			}
		}
	}

	for (int a = 0; a < positions.size(); a++)
	{
		indices.emplace_back(a);
	}

	//Loading Data
	GLfloat* data = generateDataMatrix(positions);

	size = indices.size();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(GLfloat), data, GL_STATIC_DRAW); //&data[0]

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); //TODO: indices //? too

	glBindVertexArray(0);

	//-(triangleSize * width) / 2, -(triangleSize * height) / 2

	//delete data;
}

void TerrainMesh::draw()
{
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));

	glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

GLfloat* TerrainMesh::generateDataMatrix(std::vector<glm::vec3>& positions)
{
	data_size = positions.size() * 3;
	GLfloat* data = new GLfloat[data_size];

	/*	if (positions.size() != uvs.size() || positions.size() != normals.size())
	{
	std::cout << "Incorrect amount of data. Should be the same number of sets of positions, uvs, and normals." << std::endl;
	system("pause");
	return NULL;
	}*/


	for (GLuint i = 0; i < positions.size(); i++)
	{
		data[i * 3 + 0] = positions[i].x;
		data[i * 3 + 1] = positions[i].y;
		data[i * 3 + 2] = positions[i].z;
	}

	return data;
}