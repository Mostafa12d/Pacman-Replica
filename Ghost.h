//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
using namespace std;
using namespace sf;

class Ghost
{
private:
	int currentRow;
	int currentColumn;
	Sprite enemy;
	Texture ghostTexture;
	int width;
	int height;
	int x, y;
	bool isFrightMode;

public:
	Ghost(int row, int col, int xIndex, int yIndex);
	void drawOnBoard(RenderWindow& window);
	int getCurrentRow() const;
	int getCurrentColumn() const;
	void move(char direction, int yIndex, bool standable);
	Sprite getEnemy() const;
	void resetPosition();
	void frightModeOn();
	void frightModeOff();
	void setFrightMode(bool flag);
	bool getFrightMode() const;
	char d;
};

