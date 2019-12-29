#pragma once

#include "GameSettings.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "string"



class Object
{
protected:
	float x;
	float y;
	float width;
	float height;
	Shader shader;
	VertexArray vao;
	VertexBuffer vb;
	IndexBuffer ib;
	Texture texture;
	VertexBufferLayout layouts;
	Renderer renderer;
public:
	Object(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices);
	~Object();

	void update();
	void render();

	inline float getX() const { return x; };
	inline float getY() const { return y; };
	
	inline void setX(float x) { this->x = x; };
	inline void setY(float y) { this->y = y; };

	inline void setWidth(float width) { this->width = width; };
	inline void setHight(float height) { this->height = height; };


};