#pragma once
#include <glm/glm.hpp>
struct GLFWwindow;
class Camera;


typedef void(__cdecl *MouseCB)(Camera&, int bc, int act);
typedef void(__cdecl *KeyCB)(Camera&, int kc, int act);
typedef void(__cdecl *CPCB)(Camera&, double, double);



class InputManager
{
private:
	Camera* cam;

	static bool initialized;
	
	InputManager(GLFWwindow* window, Camera* cam);
	InputManager();

	static InputManager* singleton;
	static InputManager badInputManager;

	int glfwKeyStates[348];
	int glfwMouseStates[7];
	glm::vec2 cursorPosition;

public:
	static void initialize(GLFWwindow* window, Camera* cam);
	static InputManager& getInputManager();
	void registerKCB(KeyCB cb);
	void registerMCB(MouseCB cb);
	void registerCCB(CPCB cb);

	void updateKey(int kc, int act);
	void updateButton(int bc, int act);
	void updatePosition(glm::vec2 const& pos);

	int* getKeyStates()
	{
		return glfwKeyStates;
	}

	int* getMouseStates()
	{
		return glfwMouseStates;
	}

	glm::vec2 const& getCursorPos()
	{
		return cursorPosition;
	}

	Camera* getCamera() { return cam; }
};