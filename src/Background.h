#pragma once
#include "GameSettings.h"
#include "Object.h"
#include <vector>

class Background
	:public Object
{

public:
	Background(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices);
	~Background();

	void render();
};
