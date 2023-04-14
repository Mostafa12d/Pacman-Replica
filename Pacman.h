//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ghost.h"
#include "Score.h"
#include "Audio.h"
#include "Board.h"
using namespace std;
using namespace sf;

class Pacman
{
private:
	int currentRow;
	int currentColumn;
	int lives;
	Sprite player;
	Texture playerTexture;
	Texture pacmanDeathTexture;
	Audio audio;

	bool isSuper;
	bool extraLife;

	//Pacman dimensions in pixels
	int width;
	int height;

	//sprite frames indexes to handle animation.
	int x, y;

public:
	Pacman();
	char d;
	void move(char direction, bool standable);
	void drawOnBoard(RenderWindow& window);
	int getCurrentRow() const;
	int getCurrentColumn() const;
	Sprite getPlayer();
	void resetPosition(); //When pacman collides with a ghost.
	void setSuper(bool flag);
	bool getSuper() const;
	void collide(Ghost& ghost, bool issuper, Score& score, bool& scoreFlag, bool start);
	int getLives();
	void setLives(int numberOfLives);
	void incrementLives();
	//void deathAnimation(int xValue, int yValue);
};

