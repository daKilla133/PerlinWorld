#include "TerrainMesh.h"
#define max(a,b) ((a) > (b) ? (a) : (b))


TerrainMesh::TerrainMesh()
{
	size = 0;
	data_size = 0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
}

bool FlLEQ(float lhs, float rhs, double tolerance)
{
	return (lhs < rhs) || (abs(lhs - rhs) < tolerance);
}

bool FlGEQ(float lhs, float rhs, double tolerance)
{
	return (lhs > rhs) || (abs(lhs - rhs) < tolerance);
}

void TerrainMesh::addData(float planeY, float triangleSize, int width, int height, float sign)
{
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> UVs;

	int yCounter = 0;
	float rSquared = (pow((height*triangleSize) / 2, 2) + pow((width*triangleSize) / 2, 2)) * 1.1f;

	for (float y = -(triangleSize * height) / 2; y < (triangleSize * height) / 2; y += triangleSize)
	{
		float x;
		if (yCounter % 2 == 0)
		{
			for (x = -(triangleSize * width) / 2; FlLEQ(x, (triangleSize * width) / 2, 0.00001); x += triangleSize)
			{
				float ySph = sign * 0 * sqrt(max(0, rSquared - (pow(x, 2) + pow(y, 2))));
				float ySph2 = sign * 0 * sqrt(max(0, rSquared - (pow(x, 2) + pow(y + triangleSize, 2))));
				positions.emplace_back(glm::vec3(x, ySph + planeY, y));
				positions.emplace_back(glm::vec3(x, ySph2 + planeY, y + triangleSize));
				UVs.emplace_back(glm::vec2(
					glm::clamp((x + ((triangleSize * width) / 2)) / (triangleSize * width), 0.f, 1.f),
					glm::clamp((y + ((triangleSize * height) / 2)) / (triangleSize * height), 0.f, 1.f)));
				UVs.emplace_back(glm::vec2(
					glm::clamp((x + ((triangleSize * width) / 2)) / (triangleSize * width), 0.f, 1.f),
					glm::clamp(((y + triangleSize) + ((triangleSize * height) / 2)) / (triangleSize * height), 0.f, 1.f)));
			}
		}
		else
		{
			for (x = (triangleSize * width) / 2;  FlGEQ(x, -(triangleSize * width) / 2, 0.00001); x -= triangleSize)
			{
				float ySph = sign * 0 * sqrt(max(0, rSquared - (pow(x, 2) + pow(y, 2))));
				float ySph2 = sign * 0 * sqrt(max(0, rSquared - (pow(x, 2) + pow(y + triangleSize, 2))));
				positions.emplace_back(glm::vec3(x, ySph + planeY, y));
				positions.emplace_back(glm::vec3(x, ySph2 + planeY, y + triangleSize));
				UVs.emplace_back(glm::vec2(
					glm::clamp((x + ((triangleSize * width) / 2)) / (triangleSize * width), 0.f, 1.f),
					glm::clamp((y + ((triangleSize * height) / 2)) / (triangleSize * height), 0.f, 1.f)));
				UVs.emplace_back(glm::vec2(
					glm::clamp((x + ((triangleSize * width) / 2)) / (triangleSize * width), 0.f, 1.f),
					glm::clamp(((y + triangleSize) + ((triangleSize * height) / 2)) / (triangleSize * height), 0.f, 1.f)));
			}
		}
		yCounter++;
	}
	for (int a = 0; a < positions.size(); a++)
	{
		indices.emplace_back(a);
	}

	//Loading Data
	GLfloat* data = generateDataMatrix(positions, UVs);

	size = indices.size();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(GLfloat), data, GL_STATIC_DRAW); //&data[0]

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); //TODO: indices //? too

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//-(triangleSize * width) / 2, -(triangleSize * height) / 2

	delete data;
}

void TerrainMesh::draw()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLfloat* TerrainMesh::generateDataMatrix(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& UVs)
{
	data_size = positions.size() * 5;
	GLfloat* data = new GLfloat[data_size];

	/*	if (positions.size() != uvs.size() || positions.size() != normals.size())
	{
	std::cout << "Incorrect amount of data. Should be the same number of sets of positions, uvs, and normals." << std::endl;
	system("pause");
	return NULL;
	}*/


	for (GLuint i = 0; i < positions.size(); i++)
	{
		data[i * 5 + 0] = positions[i].x;
		data[i * 5 + 1] = positions[i].y;
		data[i * 5 + 2] = positions[i].z;
		data[i * 5 + 3] = UVs[i].x;
		data[i * 5 + 4] = UVs[i].y;
	}

	return data;
}