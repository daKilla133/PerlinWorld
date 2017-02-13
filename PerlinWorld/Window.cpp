#include "Window.h"
#include <glew\glew.h>
#include <gl\GL.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

bool Window::isGLFWInit = false;

void Window::initGLFW()
{
	if (!isGLFWInit)
	{
		isGLFWInit = true;
		glfwInit();
	}
}

Window::Window(int width, int height, string const& title)
{
	initGLFW();
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	glfwSwapInterval(0);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		return;
	}

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Window::showit()
{
	if (window != nullptr)
	{
		glfwShowWindow(window);
	}
	else
	{
		std::cerr << "Could not show window, window not initialized!!!!!!!!" << std::endl;
	}
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::destroy()
{
	glfwDestroyWindow(window);
	window = nullptr;
}

void Window::update()
{
	glfwSwapBuffers(window);
}

void Window::clear()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

Window::~Window()
{
	destroy();
}