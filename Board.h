//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


enum tile_type { empty, pellet, power, wall, ghost };

struct Fruit
{
	Sprite f;
	Texture fruitTexture;
	bool edible;
};

struct cell {
	RectangleShape r; //Board tiles
	tile_type t;
	//bool standable;	  //A bool flag to check whether pacman can step over this cell or no.
	//bool eaten;		  //A bool flag to check whether a pellet was eaten or not.
};

class Board
{
private:
	ifstream input;
	cell board[21][17];
	Fruit fruit;
	Texture bricktexture;
	Texture pelletTexture;
	Texture superPelletTexture;
	Texture ghostChamberDoorTexture;

public:
	int arr[21][17];

	Board();
	bool isStandable(int row, int col) const;
	bool isEaten(int row, int col);
	bool ispower(int row, int col);

	void setFruitEdible(bool condition);
	bool isFruitEdible() const;
	RectangleShape getRectangle(int row, int col);
	void eaten(int row, int col);
	Sprite getFruit();
	void drawOnWindow(RenderWindow& window);
	void drawFruit(RenderWindow& window);
	//void resetPellets();
};

