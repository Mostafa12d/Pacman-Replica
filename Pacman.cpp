//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN
#include "Pacman.h"

Pacman::Pacman()
{
	playerTexture.loadFromFile("pacman.png");
	pacmanDeathTexture.loadFromFile("pacman death.png");

	//These coordinates are chosen to place pacman under the ghost room initially.
	currentRow = 13;
	currentColumn = 8;
	isSuper = false;
	extraLife = true;
	//score = 0;
	lives = 3;

	width = 48 / 3;
	height = 64 / 4;
	x = y = 0;
	player.setTexture(playerTexture);
	player.setTextureRect(IntRect(width * 0, height * 0, width, height));
	player.setPosition(20 + 48 * currentColumn, 20 + 48 * currentRow);
	player.setScale(3.0f, 3.0f); //Pacman was 16*16 pixels, so a scale of 3 was chosen to fit pacman into the size of the cell, which is 48.
	d = ' ';
}
void Pacman::move(char direction, bool standable)
{
	if (direction == 'U' || direction == 'u')
	{
		if (standable)
		{
			currentRow--;
			player.move(0, -48);

			//Handeling Animation.
			y = 2;
			x++;
			x %= 3;
			player.setTextureRect(IntRect(width * x, height * y, width, height));
		}
	}
	else if (direction == 'D' || direction == 'd')
	{
		if (standable)
		{
			currentRow++;
			player.move(0, 48);

			//Handeling Animation.
			y = 3;
			x++;
			x %= 3;
			player.setTextureRect(IntRect(width * x, height * y, width, height));
		}
	}
	else if (direction == 'R' || direction == 'r')
	{
		if (currentRow == 10 && currentColumn >= 16)
		{
			player.setPosition(20 + 48 * 0, 20 + 48 * 10); //10 is the index of the other portal
			currentColumn = 0;
			return;
		}
		else if (standable)
		{
			currentColumn++;
			player.move(48, 0);

			//Animation handeling
			y = 0;
			x++;
			x %= 3;
			player.setTextureRect(IntRect(width * x, height * y, width, height));
		}
	}
	else if (direction == 'L' || direction == 'l')
	{
		if (currentRow == 10 && currentColumn == 0)
		{
			player.setPosition(20 + 48 * 16, 20 + 48 * 10); //10 is the index of the other portal
			currentColumn = 16;
			return;
		}
		else if (standable)
		{
			//Animation handeling
			currentColumn--;
			player.move(-48, 0);
			y = 1;
			x++;
			x %= 3;
			player.setTextureRect(IntRect(width * x, height * y, width, height));
		}
	}
}

void Pacman::resetPosition()
{
	currentRow = 13;
	currentColumn = 8;
	player.setPosition(20 + 48 * currentColumn, 20 + 48 * currentRow);
	d = 'U'; // to prevent pacman from moving when position is reset (n)
}

int Pacman::getCurrentRow() const
{
	return currentRow;
}
int Pacman::getCurrentColumn() const
{
	return currentColumn;
}
Sprite Pacman::getPlayer()
{
	return player;
}

void Pacman::setSuper(bool flag)
{
	isSuper = flag;
}
bool Pacman::getSuper() const
{
	return isSuper;
}

void Pacman::collide(Ghost& ghost, bool issuper, Score& score, bool& scoreFlag, bool start)
{
	if (start == true)
	{
		if (issuper == false)
		{
			if (player.getGlobalBounds().intersects(ghost.getEnemy().getGlobalBounds()))
	
				{
					audio.playDeathSound(); //(n)
					ghost.resetPosition();
					resetPosition();
					lives--;
				}
					
				//}
		}
		else if (issuper == true)
		{
			if (player.getGlobalBounds().intersects(ghost.getEnemy().getGlobalBounds()))
			{
				if (ghost.getFrightMode() == false)
				{
					audio.playDeathSound(); //(n)
					ghost.resetPosition();
					resetPosition();
					lives--;
				}
				else 
				{ 
					audio.playGhostSound();//(n)
					score.incrementScore(200);
					ghost.resetPosition();
					ghost.frightModeOff();
					ghost.setFrightMode(false);
				}
				if (score.getScore() >= 1500 && scoreFlag == true)
				{
					incrementLives();
					scoreFlag = false;
				}
			}
		}
	}
	else return;
}

int Pacman::getLives()
{
	return lives;
}
void Pacman::setLives(int numberOfLives)
{
	lives = numberOfLives;
}
void Pacman::incrementLives()
{
	audio.playExtraLifeSound(); //(n)
	lives++;
}

void Pacman::drawOnBoard(RenderWindow& window)
{
	window.draw(player);
}

