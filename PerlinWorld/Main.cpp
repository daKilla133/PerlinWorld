#include "Window.h"
#include "TerrainMesh.h"
#include "Shader.h"
#include "Camera.h"
#include <GLFW\glfw3.h>
#include <windows.h>
#include <glm\gtx\rotate_vector.hpp>
#include "Input.h"
#include "PerlinGenerator.h"

const float scalar = .5;
static bool pressed = false;

void cbone(Camera& cam, int kc, int act)
{
	if (act == GLFW_PRESS || act == GLFW_REPEAT)
	{
		switch (kc)
		{
		case GLFW_KEY_W:
		{
			glm::vec3 pos = cam.getPosition();
			glm::vec3 dir = cam.getLook();
			dir *= scalar;
			pos += dir;
			cam.updatePosition(pos);
		}
		break;
		case GLFW_KEY_A:
		{
			glm::vec3 pos = cam.getPosition();
			glm::vec3 up = cam.getUp();
			glm::vec3 dir = cam.getLook();
			dir *= scalar;
			dir = glm::normalize(glm::cross(dir, up)) * -scalar;
			pos += dir;
			cam.updatePosition(pos);
		}
		break;
		case GLFW_KEY_S:
		{	
			glm::vec3 pos = cam.getPosition();
			glm::vec3 dir = cam.getLook();
			dir *= scalar;
			pos -= dir;
			cam.updatePosition(pos);
		}
		break;
		case GLFW_KEY_D:
		{
			glm::vec3 pos = cam.getPosition();
			glm::vec3 up = cam.getUp();
			glm::vec3 dir = cam.getLook();
			dir = glm::normalize(glm::cross(dir, up)) * scalar;
			pos += dir;
			cam.updatePosition(pos);
		}
		break;
		}
	}
}

void cbtwo(Camera& cam, double x, double y)
{
	static double xSave = 0;
	static double ySave = 0;
	static bool first = true;

	if (!first && pressed)
	{
		double dx = x - xSave;
		double dy = y - ySave;

		glm::vec3 look = cam.getLook();

		look = glm::rotateY(look, (float)glm::radians(dx/8));
		look = glm::rotateX(look, (float)glm::radians(dy/8));

		cam.updateLook(look);
	}
	first = false;
	xSave = x;
	ySave = y;
}

void cbthree(Camera& cam, int bc, int act)
{
	if (act == GLFW_PRESS && bc == GLFW_MOUSE_BUTTON_1)
	{
		pressed = true;
	}
	else if (act == GLFW_RELEASE && bc == GLFW_MOUSE_BUTTON_1)
	{
		pressed = false;
	}
}

int main()
{
	Window win(1200, 800, "nigr");
	win.showit();
	
	BasicShader s;
	TerrainMesh mesh;
	Camera cam(1);/*
	PerlinGenerator noise();*/
	initInput(win.getWindow(), &cam);

	RegisterKCB(cbone);
	RegisterCCB(cbtwo);
	RegisterMCB(cbthree);

	mesh.addData(-2.f, 0.6f, 300, 300);
	


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
