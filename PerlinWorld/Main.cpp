#include "Window.h"
#include "TerrainMesh.h"
#include "Shader.h"
#include "Camera.h"
#include <GLFW\glfw3.h>
#include <windows.h>
#include <glm\gtx\rotate_vector.hpp>
int main()
{
	Window win(600, 600, "nigr");
	win.showit();
	BasicShader s;
	TerrainMesh mesh;
	Camera cam(1);

	std::vector<glm::vec3> pos;
	std::vector<unsigned int> ind;
	std::vector<glm::vec2> uvs;

	pos.emplace_back(glm::vec3(-1, -1, 5));
	pos.emplace_back(glm::vec3(1, -1, 5));
	pos.emplace_back(glm::vec3(-1, 1, 5));

	ind.emplace_back(0);
	ind.emplace_back(1);
	ind.emplace_back(2);

	uvs.emplace_back(glm::vec2(0, 0));
	uvs.emplace_back(glm::vec2(1, 0));
	uvs.emplace_back(glm::vec2(0, 1));

	mesh.addData(pos, ind, uvs, false);
	


	while (!win.shouldClose())
	{
		win.clear();
		glfwPollEvents();
		
		s.bind();
		s.updateUniforms(cam.getMVP() * mesh.getModel());
		mesh.draw();


		win.update();
		Sleep(1);
	}
}
