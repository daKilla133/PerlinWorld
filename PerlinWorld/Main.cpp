#include "Window.h"
#include "TerrainMesh.h"
#include "Shader.h"
#include "Camera.h"
#include <GLFW\glfw3.h>
#include <windows.h>
#include <glm\gtx\rotate_vector.hpp>
#include "Input.h"
#include "PerlinGenerator.h"
#include "Texture.h"
#include <sstream>

const float scalar = .05;
static bool pressed = false;
#pragma region hi
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

		look = glm::rotateY(look, (float)glm::radians(-dx/8));
		look = glm::rotate(look, (float)glm::radians(-dy / 8), glm::normalize(glm::cross(look, cam.getUp())));
		//look = glm::rotateX(look, (float)glm::radians(dy/8));

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

void inputTick(InputManager& inputManager)
{
	Camera& cam = *inputManager.getCamera();
	int w = inputManager.getKeyStates()[GLFW_KEY_W], a = inputManager.getKeyStates()[GLFW_KEY_A],
		s = inputManager.getKeyStates()[GLFW_KEY_S], d = inputManager.getKeyStates()[GLFW_KEY_D];
	
	if(w & 3)
	{
		glm::vec3 pos = cam.getPosition();
		glm::vec3 dir = cam.getLook();
		dir *= scalar;
		pos += dir;
		cam.updatePosition(pos);
	}
	if (a & 3)
	{
		glm::vec3 pos = cam.getPosition();
		glm::vec3 up = cam.getUp();
		glm::vec3 dir = cam.getLook();
		dir *= scalar;
		dir = glm::normalize(glm::cross(dir, up)) * -scalar;
		pos += dir;
		cam.updatePosition(pos);
	}
	if (s & 3)
	{
		glm::vec3 pos = cam.getPosition();
		glm::vec3 dir = cam.getLook();
		dir *= scalar;
		pos -= dir;
		cam.updatePosition(pos);
	}
	if (d & 3)
	{
		glm::vec3 pos = cam.getPosition();
		glm::vec3 up = cam.getUp();
		glm::vec3 dir = cam.getLook();
		dir = glm::normalize(glm::cross(dir, up)) * scalar;
		pos += dir;
		cam.updatePosition(pos);
	}
}
#pragma endregion bye

#include <fstream>

void createPPM()
{
	string ppmString = "P3\n512 512\n255\n";
	std::ostringstream ppmStream;
	PerlinGenerator noise;
	double min = 0, max = 0;
	for (int a = 0; a < 512; a++)
	{
		for (int b = 0; b < 512; b++)
		{
			double perlinValue =  255 * (((noise.noise(((double)b / 48.0f), ((double)a / 48.0f)) + 1) / 2));
			//BYTE color = glm::clamp<BYTE>(perlinValue, 0x00, 0xFF);
			ppmStream << perlinValue << " " << perlinValue << " " << perlinValue << " ";
		}
		ppmStream << "\n";
	}
	ppmString += ppmStream.str();
	std::fstream file;
	file.open("D:\\pictures\\example.ppm", std::fstream::out);
	file << ppmString;
	file.close();
}

int main()
{
	//createPPM();
	//return 1;
	Window win(1200, 800, "nigr");
	win.showit();
	
	BasicShader s;
	TerrainMesh mesh;
	TerrainMesh mesh2;
	Camera cam(1);
	PerlinGenerator noise;
	//Texture t(noise/*"res/texture/dad.png", glm::vec4(0, 0, 0, 0)*/);
	Texture t2("res/texture/fuck3.png", glm::vec4(0, 0, 0, 0));
	
	
	
	InputManager::initialize(win.getWindow(), &cam);
	InputManager& manager = InputManager::getInputManager();

//	manager.registerKCB(cbone);
	manager.registerCCB(cbtwo);
	manager.registerMCB(cbthree);

	mesh.addData(-2.f, 0.6f, 900, 900, 1);
	mesh2.addData(-2.f, 0.6f, 30, 30, -1);
	


	while (!win.shouldClose())
	{
		win.clear();
		glfwPollEvents();
		inputTick(manager);
		s.bind();
		s.updateUniforms(cam.getMVP() * mesh.getModel(), t2);
		mesh.draw();
	//	mesh2.draw();


		win.update();
		Sleep(1);
	}
}
