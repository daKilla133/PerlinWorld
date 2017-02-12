#include "Input.h"
#include <vector>
#include <GLFW\glfw3.h>

static std::vector<KeyCB> keyList;
static std::vector<MouseCB> mouseBList;
static std::vector<CPCB> cursorPosList;
static Camera* cam;

void KeyCallBck(GLFWwindow *win, int kc, int sc, int act, int mod)
{
	for (KeyCB key : keyList) 
	{
		key(*cam, kc, act);
	}
}
void MouseCallBck(GLFWwindow *win, int bc, int act, int mod)
{
	for (MouseCB btn : mouseBList)
	{
		btn(*cam, bc, act);
	}
}
void CursorCallBck(GLFWwindow *win, double x, double y)
{
	for (CPCB pos : cursorPosList)
	{
		pos(*cam, x, y);
	}
}
void initInput(GLFWwindow *win, Camera* cam) 
{
	glfwSetKeyCallback(win, KeyCallBck);
	glfwSetMouseButtonCallback(win, MouseCallBck);
	glfwSetCursorPosCallback(win, CursorCallBck);
	::cam = cam;
}
void RegisterKCB(KeyCB cb)
{
	keyList.emplace_back(cb);
}
void RegisterMCB(MouseCB cb)
{
	mouseBList.emplace_back(cb);
}
void RegisterCCB(CPCB cb)
{
	cursorPosList.emplace_back(cb);
}