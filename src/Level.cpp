#include "Level.h"
#include <ctime>
#include <random>

Level::Level()
	:pipe(genObject<Pipe>(PIPE_WIDTH, PIPE_HEIGHT, "res/shaders/pipe.shader", "res/images/pipe.png")), bird(genObject<Bird>(BIRD_SIZE, BIRD_SIZE, "res/shaders/basic.shader", "res/images/bird.png")),
	bg(genObject<Background>(BG_WIDTH, BG_HEIGHT, "res/shaders/pipe.shader", "res/images/bg.jpeg")), isGameOver(false)
{
	srand((int)time(0));
	createBG();
	createPipes();
	
}

Level::~Level()
{

}



void Level::render()
{
	renderBG();
	renderPipes();
	bird.render();
}

void Level::update()
{
	if (isGameOver)
		bird.fall();
	else
	{
		updatePipes();
		updateBG();
	}
		
	bird.update();
}

void Level::updateBG()
{
	if ((*tiles.begin()).x + BG_WIDTH < -WIDTH_F / 2.0F)
	{
		tiles.erase(tiles.begin());
		tiles.push_back({ tiles.back().x + BG_WIDTH, 0.0f, BOTTOM });
	}

	for (position& pos : tiles)
	{
		pos.x = pos.x - SPEED * 1.1f;
	}
}

void Level::renderBG()
{
	for (position& pos: tiles)
	{
		bg.setX(pos.x);
		bg.setY(pos.y);
		bg.render();
	}
}

void Level::createBG()
{
	float xPos = -WIDTH_F / 2.0F;
	for (int i = 0; i < BG_NUMBER; i++)
	{
		tiles.push_back({ xPos, 0.0f, BOTTOM });
		xPos -= BG_WIDTH;
	}

}

void Level::createPipes()
{
	float xPos = PIPE_START_X_COOR;
	for (int i = 0; i < 10; )
	{
		float OFFSET = rand() % ((int)RANDOM_BOUND);
		pipes.push_back({ xPos, -TOUCH_BOTTOM - OFFSET, BOTTOM });
		pipes.push_back({ xPos, PIPE_HEIGHT - TOUCH_BOTTOM - OFFSET + TOP_BOTTOM_DISTANCE, TOP });
		xPos += PIPE_DISTANCE;
		i += 2;
	}

}

void Level::updatePipes()
{
	if ((*pipes.begin()).x < -WIDTH_F / 2.0F - PIPE_WIDTH)
	{
		pipes.erase(pipes.begin());
		pipes.erase(pipes.begin());
		float OFFSET = rand() % ((int)RANDOM_BOUND);
		position newPipeBottom = { pipes.back().x + PIPE_DISTANCE, -TOUCH_BOTTOM - OFFSET, BOTTOM };
		position newPipeTop = { pipes.back().x + PIPE_DISTANCE, PIPE_HEIGHT - TOUCH_BOTTOM - OFFSET + TOP_BOTTOM_DISTANCE, TOP };
		pipes.push_back(newPipeBottom);
		pipes.push_back(newPipeTop);
	}
	for (position& pos : pipes)
	{
		pos.x = pos.x - SPEED;
	}
}

void Level::renderPipes()
{
	for (position pos : pipes)
	{
		pipe.setX(pos.x);
		pipe.setY(pos.y);
		pipe.setDirection(pos.direction);
		pipe.render();
	}
}

void Level::reset()
{
	bird.setY(0.0F);
	float xPos = PIPE_START_X_COOR;
	auto iter = pipes.begin();
	for (iter; iter != pipes.end(); )
	{

		float OFFSET = rand() % ((int)RANDOM_BOUND);
		(*iter) = { xPos, -TOUCH_BOTTOM - OFFSET, BOTTOM };
		iter++;
		(*iter) = { xPos, PIPE_HEIGHT - TOUCH_BOTTOM - OFFSET + TOP_BOTTOM_DISTANCE, TOP };
		iter++;
		xPos += PIPE_DISTANCE;

	}
	isGameOver = false;
}

bool Level::isCollision()
{
	for (position pos : pipes)
	{
		float birdMinX = -BIRD_SIZE / 2.0f + 10.0f;
		float birdMaxX = BIRD_SIZE / 2.0f - 10.0f;
		float pipeMinX = -PIPE_WIDTH / 2.0f + pos.x;
		float pipeMaxX =  PIPE_WIDTH / 2.0f + pos.x;

		float birdMinY = -BIRD_SIZE / 2.0f + bird.getY() + 10.0f;
		float birdMaxY = BIRD_SIZE / 2.0f + bird.getY() - 10.0f;
		float pipeMinY = -PIPE_HEIGHT / 2.0f + pos.y;
		float pipeMaxY = PIPE_HEIGHT / 2.0f + pos.y;

		bool intersectX = birdMaxX > pipeMinX && pipeMaxX > birdMinX;
		bool intersectY = birdMaxY > pipeMinY && pipeMaxY > birdMinY;

		if (intersectX && intersectY)
		{
			isGameOver = true;
			return true;
		}
	}
	return false;
}

bool Level::gameOver()
{
	return isGameOver;
}
