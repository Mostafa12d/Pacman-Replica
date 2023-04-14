#include "Score.h"


//pacmanFont.loadFromFile("pacman font.ttf");
//scoreStream << "Score: " << score;
//scoreText.setCharacterSize(20);
//scoreText.setPosition(845, 20);
//scoreText.setFont(pacmanFont);
//scoreText.setString(scoreStream.str());

Score::Score()
{
	score = 0;
	font.loadFromFile("pacman font.ttf");
	stream << "Score:" << score;
	text.setCharacterSize(20);
	text.setPosition(845, 415);
	text.setFont(font);
	text.setString(stream.str());

	font.loadFromFile("pacman font.ttf");
	stream2 << "Score:" << score;
	menuText.setCharacterSize(30);
	menuText.setPosition(400, 415);
	menuText.setFont(font);
	menuText.setString(stream.str());
}

void Score::incrementScore(int n)
{
	score = score + n;
	stream.str("");
	stream << "Score:" << score;
	text.setString(stream.str());
}
unsigned int Score::getScore()
{
	return score;
}

void Score::resetScore()
{
	score = 0;
}

void Score::drawOnWindow(RenderWindow& window)
{
	window.draw(text);
}

//(n)
void Score::drawOnMenu(RenderWindow& window)
{
	window.draw(menuText);
}