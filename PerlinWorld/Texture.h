#pragma once

#include "Resource.h"
#include <glm\glm.hpp>

class Texture
{
private:
	string fileName;
	GLuint tid;
	GLsizei width;
	GLsizei height;
	glm::vec4 color;
	float specularIntensity;
	float specularPower;
private:
	GLuint load();
public:
	Texture(const string& path, glm::vec4& color);
	Texture(const string& path, glm::vec4& c, float specularIntensity, float specularExponent);
	~Texture();
	void bind();
	void unbind();
	inline const bool hasImage() const { return fileName.compare(""); }
	inline const unsigned int getWidth() const { return width; }
	inline const unsigned int getHeight() const { return height; }
	inline const unsigned int getID() const { return tid; }
	inline const glm::vec4& getColor() { return color; }
	inline const float getSpecularIntensity() const { return specularIntensity; }
	inline const float getSpecularPower() const { return specularPower; }

	inline void setColor(glm::vec4& color) { this->color = color; }

	inline const void setSpecularIntensity() { this->specularIntensity = specularIntensity; }
	inline const void setSpecularPower() { this->specularPower = specularPower; }
};