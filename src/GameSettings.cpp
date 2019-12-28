#include "GameSettings.h"
#include <iostream>

void clearGLError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line)
{
	unsigned int flag;
	while (flag = glGetError())
	{
		std::cout << "[OpenGL Error]: " << flag << " " << function << " " << line << " " << file << std::endl;
		return true;
	}
	return false;
}

