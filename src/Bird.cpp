#include "Bird.h"


Bird::Bird(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices)
	:Object(width, height, shaderPath, texturePath, positions, indices),
	delta(0.0f)
{

}

Bird::~Bird()
{

}

void Bird::update()
{
	if (KEY_DOWN(VK_SPACE)) 
	{
		delta = 8.0f;
	}
	else
	{
		delta -= 0.5f;
	}
	setY(getY() + delta);
}

void Bird::render()
{
	vao.bind();
	ib.bind();
	texture.bind(0);
	shader.bind();
	shader.setUniform1i("u_Texture", 0);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(getY() * 0.1f), glm::vec3(0.0, 0.0, 1.0));
	shader.setUniformMat4f("rot_matrix", trans);
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.0f, getY(), 0.0f));
	shader.setUniformMat4f("trans_matrix", trans);
	trans = glm::mat4(1.0f);
	trans = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	shader.setUniformMat4f("orth_matrix", trans);
	trans = glm::mat4(1.0f);
	renderer.draw(vao, ib, shader);
}
