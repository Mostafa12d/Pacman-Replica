#pragma once
#include <iostream>
#include "Score.h"
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Menu
{
private:
	int selectedItem;
	Font font;
	Text text1; //Press Enter to play
	Text text2; //cs
	//Text score;
	//Score s;
	Text life;
	//Sprite lives[4];
	//Texture livesTexture;
	Text gameOverText;
	Text win;
	ostringstream stream;
	Sprite image1;
	Texture image1_Texture;
	Sprite image2;
	Texture image2_Texture;
	Sprite gameOverImage;
	Texture gameOver_Texture;

public:
	Menu();
	void drawOnWindow(RenderWindow& window);
	void drawGameover(RenderWindow& window);
	void drawWin(RenderWindow& window);
	//void drawScore(RenderWindow& window);
	//void drawLives(RenderWindow& window, int l); //(n)
	//void setScore(int s); // (n)
};


