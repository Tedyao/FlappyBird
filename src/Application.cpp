#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameSettings.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <string>
#include <vector>
#include "Texture.h"
#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Bird.h"
#include "Pipe.h"
#include "Level.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer renderer = Renderer();


	Level level = Level();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		//if (position < -5.0f || position > 5.0f) break;
		level.isCollision();
		if (level.gameOver())
		{
			if (KEY_DOWN(VK_SPACE))
			{
				level.reset();
			}
				
		}
		level.render();
		level.update();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	//glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}