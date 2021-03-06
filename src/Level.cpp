#include "Level.h"
#include <ctime>
#include <random>

Level::Level()
	:pipe(genObject<Pipe>(PIPE_WIDTH, PIPE_HEIGHT, "res/shaders/pipe.shader", "res/images/pipe.png")), bird(genObject<Bird>(BIRD_SIZE, BIRD_SIZE, "res/shaders/basic.shader", "res/images/bird.png")),
	bg(genObject<Background>(BG_WIDTH, BG_HEIGHT, "res/shaders/pipe.shader", "res/images/bg.jpeg")), isGameOver(false),
	font(genObject<Font>(FONT_SIZE, FONT_SIZE, "res/shaders/font.shader", "res/images/character.png")), score(0.0f),
	bestScore(0), gameOverScreen(genObject<GameOver>(800.0, 400.0, "res/shaders/pipe.shader", "res/images/gameover.png"))
{
	srand((int)time(0));
	createBG();
	createPipes();
	createScores();
	
}

Level::~Level()
{

}



void Level::render()
{
	renderBG();
	renderPipes();
	renderScores();
	bird.render();
	
}

void Level::update()
{
	if (isGameOver)
	{
		bird.fall();
		if (score > bestScore)
			bestScore = score;
		resetScores(bestScores);
		createScores(bestScores, 100.0f, -100.0f, 2 * FONT_SIZE);
		updateScores(bestScores, bestScore);
		renderScores(bestScores);
		gameOverScreen.render();

	}
	else
	{
		updatePipes();
		updateScores();
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
		xPos += BG_WIDTH;
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

void Level::createScores()
{
	createScores(scores, SCORE_X_POSITION, SCORE_Y_POSITION, FONT_SIZE);

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
	score += SPEED / 240;

}

void Level::updateScores()
{
	updateScores(scores, score);
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

void Level::renderScores()
{
	renderScores(scores);
}

void Level::reset()
{

	bird.setY(0.0F);
	score = 0.1f;
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

	resetScores(scores);
	createScores();

	
}

bool Level::isCollision()
{
	if (bird.getY() < -WIDTH_F / 2.0F || bird.getY() > WIDTH_F / 2.0F)
	{
		isGameOver = true;
		return true;
	}
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

void Level::resetScores(std::vector<fontStruct>& scores)
{
	auto s_iter = scores.begin();
	while (s_iter != scores.end())
	{
		s_iter = scores.erase(s_iter);
	}
}

void Level::renderScores(std::vector<fontStruct>& scores)
{
	for (fontStruct pos : scores)
	{
		font.setX(pos.x);
		font.setY(pos.y);
		font.setCharacter(pos.character);
		font.setWidth(pos.fontSize);
		font.setHight(pos.fontSize);
		font.render();
	}
}

void Level::updateScores(std::vector<fontStruct>& scores, int score)
{
	int digit = (int)score;
	std::vector<int> digits;
	while (digit > 0)
	{
		digits.push_back(digit % 10);
		digit = digit / 10;
	}
	auto s_iter = scores.end() - 2;
	auto iter = digits.begin();
	while (iter != digits.end() && s_iter != scores.begin())
	{
		(*s_iter).character = *iter;
		iter++;
		s_iter--;
	}
}

void Level::createScores(std::vector<fontStruct>& scores, float X_POS, float Y_POS, float fontSize)
{
	float pos = X_POS;
	for (int i = 0; i < FONT_LENGTH; i++)
	{

		if (i == FONT_LENGTH - 1)
		{
			scores.push_back({ pos, Y_POS, 10 , fontSize });
		}
		else if (i == FONT_LENGTH - 2)
		{
			scores.push_back({ pos, Y_POS, 0, fontSize });

		}
		else
		{
			scores.push_back({ pos, Y_POS, 24, fontSize });

		}

		pos += FONT_DISTANCE;
	}
}
