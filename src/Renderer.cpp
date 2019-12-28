#include "Renderer.h"
#include <iostream>
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.bind();
	ib.bind();
	shader.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

}
