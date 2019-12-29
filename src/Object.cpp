#include "Object.h"

Object::Object(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices)
	:x(0.0f), y(0.0f), width(width), height(height), shader(Shader(shaderPath)), texture(Texture(texturePath)), vao(VertexArray()),
	layouts(VertexBufferLayout()), renderer(Renderer()), vb(VertexBuffer(positions, 4 * 4 * sizeof(float))), ib(IndexBuffer(indices, 6))
{
	layouts.Push<float>(2);
	layouts.Push<float>(2);
	vao.addBufferLayout(vb, layouts);
}

Object::~Object()
{

}

void Object::update()
{
	
}

void Object::render()
{

	vao.bind();
	ib.bind();
	texture.bind(0);
	shader.bind();
	shader.setUniform1i("u_Texture", 0);

	glm::mat4 trans = glm::mat4(1.0f);
	shader.setUniformMat4f("rot_matrix", trans);

	shader.setUniformMat4f("trans_matrix", trans);
	trans = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	shader.setUniformMat4f("orth_matrix", trans);
	renderer.draw(vao, ib, shader);

}
