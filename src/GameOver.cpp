#include "GameOver.h"

GameOver::GameOver(float width, float height, const std::string& shaderPath, const std::string& texturePath, float* positions, unsigned int* indices)
	:Object(width, height, shaderPath, texturePath, positions, indices)
{

}

GameOver::~GameOver()
{

}

void GameOver::render()
{
	vao.bind();
	ib.bind();
	texture.bind(0);
	shader.bind();
	shader.setUniform1i("u_Texture", 0);
	glm::mat4 trans = glm::mat4(1.0f);
	shader.setUniformMat4f("rot_matrix", trans);
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(getX(), getY(), 0.0f));
	shader.setUniformMat4f("trans_matrix", trans);
	trans = glm::mat4(1.0f);
	trans = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	shader.setUniformMat4f("orth_matrix", trans);
	trans = glm::mat4(1.0f);
	renderer.draw(vao, ib, shader);
}