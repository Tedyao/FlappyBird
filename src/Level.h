#pragma once
#include "GameSettings.h"
#include "Bird.h"
#include "Pipe.h"
#include "vector"
#include "Background.h"
#include "Font.h"
#include "GameOver.h"


template<typename T>
T genObject(float width, float height, const std::string& shaderPath, const std::string& texturePath)
{
	float position[] = {
		-width / 2.0f, -height / 2.0f, 0.0f, 0.0f,
		width / 2.0f, -height / 2.0f, 1.0f, 0.0f,
		width / 2.0f, height / 2.0f, 1.0f, 1.0f,
		-width / 2.0f, height / 2.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
	};

	return T(width, height, shaderPath, texturePath, position, indices);
}

class Level
{
private:
	std::vector<position> pipes;
	std::vector<position> tiles;
	std::vector<fontStruct> scores;
	std::vector<fontStruct> bestScores;
	bool isGameOver;
	Background bg;
	Pipe pipe;
	Bird bird;
	Font font;
	GameOver gameOverScreen;
	float score;
	int bestScore;
public:
	Level();
	~Level();
	void render();
	void update();
	void updateBG();
	void renderBG();
	void createBG();
	void createPipes();
	void createScores();
	void updatePipes();
	void updateScores();
	void renderPipes();
	void renderScores();
	void reset();
	bool isCollision();
	bool gameOver();

	void resetScores(std::vector<fontStruct>& scores);
	void renderScores(std::vector<fontStruct>& scores);
	void updateScores(std::vector<fontStruct>& scores, int score);

	void createScores(std::vector<fontStruct>& scores, float X_POS, float Y_POS, float fontSize);

	
	inline std::vector<position> getPipes() const { return pipes; };

};
