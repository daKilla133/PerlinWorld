#include "Input.h"
#include <vector>
#include <GLFW\glfw3.h>


static std::vector<KeyCB> keyList;
static std::vector<MouseCB> mouseBList;
static std::vector<CPCB> cursorPosList;

bool InputManager::initialized = false;
InputManager* InputManager::singleton = nullptr;
InputManager InputManager::badInputManager;

void KeyCallBck(GLFWwindow *win, int kc, int sc, int act, int mod)
{
	for (KeyCB key : keyList) 
	{
		key(*InputManager::getInputManager().getCamera(), kc, act);
	}
	InputManager::getInputManager().updateKey(kc, act);
}
void MouseCallBck(GLFWwindow *win, int bc, int act, int mod)
{
	for (MouseCB btn : mouseBList)
	{
		btn(*InputManager::getInputManager().getCamera(), bc, act);
	}
	InputManager::getInputManager().updateButton(bc, act);
}
void CursorCallBck(GLFWwindow *win, double x, double y)
{
	for (CPCB pos : cursorPosList)
	{
		pos(*InputManager::getInputManager().getCamera(), x, y);
	}
	InputManager::getInputManager().updatePosition(glm::vec2((float)x, (float)y));
}

InputManager::InputManager(GLFWwindow* win, Camera* cam)
{
	glfwSetKeyCallback(win, KeyCallBck);
	glfwSetMouseButtonCallback(win, MouseCallBck);
	glfwSetCursorPosCallback(win, CursorCallBck);
	this->cam = cam;
}

InputManager::InputManager()
{}

void InputManager::initialize(GLFWwindow *win, Camera* cam)
{
	if (!initialized)
	{
		initialized = true;
		InputManager::singleton = new InputManager(win, cam);
	}
}

InputManager& InputManager::getInputManager()
{
	if (!initialized)
	{
		return badInputManager;
	}
	return *singleton;
}

void InputManager::registerKCB(KeyCB cb)
{
	keyList.emplace_back(cb);
}
void InputManager::registerMCB(MouseCB cb)
{
	mouseBList.emplace_back(cb);
}
void InputManager::registerCCB(CPCB cb)
{
	cursorPosList.emplace_back(cb);
}

void InputManager::updateKey(int kc, int act)
{
	glfwKeyStates[kc] = act;
}

void InputManager::updateButton(int bc, int act)
{
	glfwMouseStates[bc] = act;
}

void InputManager::updatePosition(glm::vec2 const& pos)
{
	cursorPosition = pos;
}