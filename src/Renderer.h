#pragma once
#include <GL/glew.h>
#include "GameSettings.h"

class VertexArray;
class Shader;
class IndexBuffer;


class Renderer
{
private:

public:
	Renderer();
	~Renderer();
	void clear();
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	
};

