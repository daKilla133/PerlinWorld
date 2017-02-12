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

	mesh.addData(-2.f, 0.6f, 60, 60);
	


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
