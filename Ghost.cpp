//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN
#include "Ghost.h"

Ghost::Ghost(int row, int col, int xIndex, int yIndex)
{
	ghostTexture.loadFromFile("Ghost spritesheet.png");
	currentRow = row;
	currentColumn = col;

	width = 28 / 2;
	height = 280 / 20;
	x = xIndex;
	y = yIndex;
	isFrightMode = false;

	enemy.setTexture(ghostTexture);
	enemy.setTextureRect(IntRect(width * x, height * y, width, height));
	enemy.setScale(3.0f, 3.0f);
	enemy.setPosition(20 + 48 * currentColumn, 20 + 48 * currentRow);
}

void Ghost::move(char direction, int yIndex, bool standable) //direction is a random number from 1 to 4, 1:up, 2:down, 3:right, 4:left
{
	if (direction == 'U' || direction == 'u')
	{
		if (standable)
		{
			currentRow--;
			enemy.move(0, -48);

			if (isFrightMode == false)
			{
				x++;
				x = x % 2;
				enemy.setTextureRect(IntRect(width * x, height * yIndex, width, height));
			}
			else
				enemy.setTextureRect(IntRect(width * 0, height * 18, width, height));
		}
	}
	else if (direction == 'D' || direction == 'd')
	{
		if (standable)
		{
			currentRow++;
			enemy.move(0, 48);

			//Animation Handeling.
			if (isFrightMode == false)
			{
				x++;
				x = x % 2;
				enemy.setTextureRect(IntRect(width * x, height * yIndex, width, height));
			}
			else
				enemy.setTextureRect(IntRect(width * 0, height * 18, width, height));
		}
	}
	else if (direction == 'R' || direction == 'r')
	{
		if (currentRow == 10 && currentColumn >= 16)
		{
			enemy.setPosition(20 + 48 * 0, 20 + 48 * 10); //10 is the index of the other portal
			currentColumn = 0;
			return;
		}
		if (standable)
		{
			currentColumn++;
			enemy.move(48, 0);

			//Animation Handeling
			if (isFrightMode == false)
			{
				x++;
				x = x % 2;
				enemy.setTextureRect(IntRect(width * x, height * yIndex, width, height));
			}
			else
				enemy.setTextureRect(IntRect(width * 0, height * 18, width, height));
		}
	}
	else if (direction == 'L' || direction == 'l')
	{
		if (currentRow == 10 && currentColumn == 0)
		{
			enemy.setPosition(20 + 48 * 16, 20 + 48 * 10); //10 is the index of the other portal
			currentColumn = 16;
			return;
		}
		if (standable)
		{
			currentColumn--;
			enemy.move(-48, 0);

			//Animation Handeling
			if (isFrightMode == false)
			{
				x++;
				x = x % 2;
				enemy.setTextureRect(IntRect(width * x, height * yIndex, width, height));
			}
			else
				enemy.setTextureRect(IntRect(width * 0, height * 18, width, height));
		}
	}
}
Sprite Ghost::getEnemy() const
{
	return enemy;
}

int Ghost::getCurrentRow() const
{
	return currentRow;
}
int Ghost::getCurrentColumn() const
{
	return currentColumn;
}

void Ghost::resetPosition()
{
	currentRow = currentColumn = 8;
	enemy.setPosition(20 + 48 * currentColumn, 20 + 48 * currentRow);
}

void Ghost::drawOnBoard(RenderWindow& window)
{
	window.draw(enemy);
}
void Ghost::frightModeOn()
{
	//cout << "fright mode called" << endl;
	enemy.setTextureRect(IntRect(width * 0, height * 18, width, height));
}

void Ghost::frightModeOff()
{
	enemy.setTextureRect(IntRect(width * x, height * y, width, height));
}
void Ghost::setFrightMode(bool flag)
{
	isFrightMode = flag;
}
bool Ghost::getFrightMode() const
{
	return isFrightMode;
}
