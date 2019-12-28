#pragma once
#include "Object.h"
#include "GameSettings.h"
#include <windows.h>

class Bird
	:public Object
{
private:
	float delta;
public:
	Bird(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices);
	~Bird();

	void update();
	void render();
	inline void fall() { delta = -20.0f; };
};