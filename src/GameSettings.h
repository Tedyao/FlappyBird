#pragma once
#include <GL/glew.h>
#include <string>

#define KEY_DOWN(KEY) (GetAsyncKeyState(KEY) & 0x8000)
#define ASSERT(x) if(x) __debugbreak();
#define GLCall(x) clearGLError(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__));

void clearGLError();

bool glLogCall(const char* function, const char* file, int line);



enum Direction
{
	BOTTOM, TOP
};

struct position
{
	float x;
	float y;
	Direction direction;
};

struct fontStruct
{
	float x;
	float y;
	int character;
	float fontSize;

};

const float SPEED = 5.0f;
const int WIDTH = 1280;
const int HEIGHT = 720;
const float WIDTH_F = 1280.0f;
const float HEIGHT_F = 720.0f;

const float PIPE_HEIGHT = HEIGHT_F * 2.0F / 3.0F;
const float PIPE_WIDTH = PIPE_HEIGHT * 52.0F / 320.0F * 1.5F;

const float BIRD_SIZE = HEIGHT_F / 10.0F;
const float TOUCH_BOTTOM = HEIGHT_F / 6.0F;
const float RANDOM_BOUND = HEIGHT_F / 2.0F;

const float PIPE_DISTANCE = WIDTH_F / 3;

const float PIPE_START_X_COOR = WIDTH_F / 3.0F;

const float TOP_BOTTOM_DISTANCE = HEIGHT_F / 3.0F;

const float BG_HEIGHT = HEIGHT_F;
const float BG_WIDTH = BG_HEIGHT * 284.0F / 512.0F;
const int BG_NUMBER = WIDTH_F / BG_WIDTH + 2;

const int FONT_SIZE = BIRD_SIZE;

const float SCORE_X_POSITION = WIDTH_F / 2.0F - 5 * FONT_SIZE;
const float SCORE_Y_POSITION = HEIGHT_F / 2.0F - FONT_SIZE;
const float FONT_DISTANCE = FONT_SIZE * 0.5;

const int FONT_LENGTH = 6;

