#pragma once
#include "GameSettings.h"
#include "Object.h"

class GameOver
	:public Object
{
public:
	GameOver(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices);
	~GameOver();

	void render();
};


