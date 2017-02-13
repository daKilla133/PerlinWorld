#include "Texture.h"
#include <iostream>
#include <FreeImage.h>

BYTE* loadImage(const char* filename, GLsizei* width, GLsizei* height)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = nullptr;

	fif = FreeImage_GetFileType(filename, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	if (fif == FIF_UNKNOWN)
		return nullptr;

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	if (!dib)
		return nullptr;

	BYTE* pixels = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
	int bits = FreeImage_GetBPP(dib);

	int size = *width * *height * (bits / 8);
	BYTE* result = new BYTE[size];
	memcpy(result, pixels, size);
	FreeImage_Unload(dib);

	return result;
}

Texture::Texture(const string& path, glm::vec4& c)
	: fileName(path), color(c)
{
	if (fileName.compare(""))
		tid = load();

	this->specularIntensity = 2;
	this->specularPower = 32;
}

Texture::Texture(const string& path, glm::vec4& c, float specularIntensity, float specularPower)
	: Texture(path, c)
{
	this->specularIntensity = specularIntensity;
	this->specularPower = specularPower;
}

Texture::~Texture()
{

}

GLuint Texture::load()
{
	BYTE* pixels = loadImage(fileName.c_str(), &width, &height);
	GLenum err;
	err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cout << err;
		std::cout << "Error loading texture. 1" << std::endl;
		system("pause");

	}
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	err = glGetError();
	glBindTexture(GL_TEXTURE_2D, 0);
	if (err != GL_NO_ERROR)
	{
		std::cout << err << std::endl << result << std::endl;
		std::cout << "Error loading texture. 2" << std::endl;
		system("pause");
	}

	delete[] pixels;
	return result;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tid);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}