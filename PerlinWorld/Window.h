#pragma once
#include "Resource.h"
#include <glm\glm.hpp>

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* window;
	static bool isGLFWInit;

	glm::mat4 projection;
public:
	static void initGLFW();

	Window(int width, int height, string const& title);
	void showit();
	bool shouldClose();
	void destroy();
	void update();
	void clear();

	GLFWwindow* getWindow() 
	{
		return window;
	}
	~Window();
};