#pragma once
#include "Object.h"
#include "GameSettings.h"

class Font
	:public Object
{
private:
	int character;
public:
	Font(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices);
	~Font();

	void render();
	inline void setCharacter(int c) { character = c; };
};