#pragma once
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;



class Score
{
private:
	unsigned int score;
	Font font;
	ostringstream stream;
	ostringstream stream2;
	Text text;
	Text menuText;
public:
	Score();
	void incrementScore(int n);
	unsigned int getScore();
	void drawOnWindow(RenderWindow& window);
	void drawOnMenu(RenderWindow& window);
	void resetScore();
	//ghostscore() // display the score of eating the ghost on the tile itself.

};

