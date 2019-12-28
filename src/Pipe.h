#pragma once
#include "GameSettings.h"
#include "Object.h"

class Pipe
	:public Object
{
private:
	Direction direction;
public:
	Pipe(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices);
	~Pipe();
	void update();
	void render();
	inline void setDirection(Direction direction) { this->direction = direction; };
	inline int getDirection() const { return direction; };
};
