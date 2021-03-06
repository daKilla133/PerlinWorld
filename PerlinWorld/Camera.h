#pragma once
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
private:
	glm::mat4 view;
	glm::mat4 perspective;
	glm::mat4 mvpCache;

	glm::vec3 cameraPos;
	glm::vec3 cameraLook;
	glm::vec3 cameraUp;

	bool mvpCacheOOD;
public:
	Camera(float aspect)
	{
		cameraUp = glm::vec3(0, 1, 0);
		cameraLook = glm::vec3(0, 0, -1);
		cameraPos = glm::vec3(0, 0, 0);
		perspective = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
		recacheMVP();
	}

	glm::mat4 & getMVP()
	{
		if (mvpCacheOOD)
		{
			recacheMVP();
		}
		return mvpCache;
	}

	void recacheMVP()
	{
		mvpCacheOOD = false;
		view = glm::lookAt(cameraPos, cameraPos + cameraLook, cameraUp);
		mvpCache = perspective * view;
	}

	glm::vec3 const& getLook()
	{
		return cameraLook;
	}

	glm::vec3 const& getPosition()
	{
		return cameraPos;
	}

	glm::vec3 const& getUp()
	{
		return cameraUp;
	}

	void updatePosition(glm::vec3 const& pos)
	{
		cameraPos = pos;
		mvpCacheOOD = true;
	}

	void updateLook(glm::vec3 const& look)
	{
		cameraLook = look;
		mvpCacheOOD = true;
	}
};