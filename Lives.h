#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Pacman.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Lives
{
private:
	Sprite lives[4];
	Texture livesTexture;

	//int numberOfLives;
public:
	Lives();
	void drawOnBoard(RenderWindow& window, int pacmanLives);
	//void addLife();
};

