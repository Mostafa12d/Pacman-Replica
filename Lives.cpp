#include "Lives.h"


Lives::Lives()
{
	//numberOfLives = 3;

	livesTexture.loadFromFile("super pellet.png");
	for (int i = 0; i < 4; i++)
	{
		lives[i].setPosition(836 + (i * 48), 595);
		lives[i].setTexture(livesTexture);
	}
}

void Lives::drawOnBoard(RenderWindow& window, int pacmanLives)
{
	for (int i = 0; i < pacmanLives; i++)
		window.draw(lives[i]);
}
