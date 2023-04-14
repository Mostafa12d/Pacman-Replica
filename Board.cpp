//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN
#include "Board.h"

Board::Board()
{
	//int arr[21][17];
	input.open("Board.txt");
	if (input.is_open())
	{
		for (int i = 0; i < 21; i++)
			for (int j = 0; j < 17; j++)
				if (!input.eof())
					input >> arr[i][j];
	}
	input.close();
	//Now the text file is loaded into the 2D array

	bricktexture.loadFromFile("Blue block.jpg");
	pelletTexture.loadFromFile("small pellet.png");
	superPelletTexture.loadFromFile("super pellet.png");

	fruit.fruitTexture.loadFromFile("fruit.png");
	fruit.f.setTexture(fruit.fruitTexture);
	fruit.f.setPosition(404, 644);
	fruit.edible = false;

	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 17; j++)
		{
			board[i][j].r.setPosition(20 + 48 * j, 20 + 48 * i);  //20 is the number of pixels between the board and the left side of the window.
																  //20 is the number of pixels between the board and the upper side of the window.
			board[i][j].r.setSize(Vector2f(48.0f, 48.0f));		  //48 is the dimension of one cell.

			if (arr[i][j] == -1) //If it's a wall.
			{
				board[i][j].r.setTexture(&bricktexture);
				board[i][j].t = wall;
			}
			else if (arr[i][j] == 28 || arr[i][j] == 38 || arr[i][j] == 153 || arr[i][j] == 160) //power pellets positions.
			{
				board[i][j].r.setTexture(&superPelletTexture);
				board[i][j].t = power;
			}
			else if (arr[i][j] != 76 && arr[i][j] != 77 && arr[i][j] != 65 && arr[i][j] != 66 &&
				arr[i][j] != 80 && arr[i][j] != 89 && arr[i][j] != 90 && arr[i][j] != 91 &&
				arr[i][j] != 100 && arr[i][j] != 101 && arr[i][j] != 102 && arr[i][j] != 111 &&
				arr[i][j] != 112 && arr[i][j] != 105 && arr[i][j] != 106 && arr[i][j] != 118)
				//Excluding the ghost room, pacman's starting position, and the empty places behind the walls.
			{
				board[i][j].t = pellet;
				board[i][j].r.setTexture(&pelletTexture);
			}
			else
			{
				board[i][j].r.setFillColor(Color::Black);
				board[i][j].t = tile_type::empty;
			}

			//board[i][j].standable = true;
		}

	board[9][8].t = tile_type::empty; //The entrace of the ghost chamber

}
void Board::eaten(int row, int col) //The function changes the eaten bool in the cell to true and makes the pellet disappear.
{
	board[row][col].t = tile_type::empty;
	board[row][col].r.setFillColor(Color::Black);
}

bool Board::isStandable(int row, int col) const
{
	return (board[row][col].t != tile_type::wall);
}
bool Board::isEaten(int row, int col)
{
	return (board[row][col].t == tile_type::empty);
}
bool Board::ispower(int row, int col)
{
	return (board[row][col].t == tile_type::power);

}
RectangleShape Board::getRectangle(int row, int col)
{
	return board[row][col].r;

}
void Board::setFruitEdible(bool condition)
{
	fruit.edible = condition;
}

bool Board::isFruitEdible() const
{
	return fruit.edible;
}
Sprite Board::getFruit()
{
	return fruit.f;
}
//void Board::resetPellets()
//{
//	for (int i = 0; i < 21; i++)
//		for (int j = 0; j < 17; j++)
//			board[i][j].t = tile_type::empty;
//	for(int i = 0; i < 21; i++)
//		for (int j = 0; j < 17; j++)
//		{
//			if (arr[i][j] == 28 || arr[i][j] == 38 || arr[i][j] == 153 || arr[i][j] == 160)
//				board[i][j].t = tile_type::power;
//
//			if (arr[i][j] != 76 && arr[i][j] != 77 && arr[i][j] != 65 && arr[i][j] != 66 &&
//				arr[i][j] != 80 && arr[i][j] != 89 && arr[i][j] != 90 && arr[i][j] != 91 &&
//				arr[i][j] != 100 && arr[i][j] != 101 && arr[i][j] != 102 && arr[i][j] != 111 &&
//				arr[i][j] != 112 && arr[i][j] != 105 && arr[i][j] != 106 && arr[i][j] != 118)
//			{
//				board[i][j].t = tile_type::pellet;
//			}
//			
//		}
//
//}
void Board::drawOnWindow(RenderWindow& window)
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 17; j++)
			window.draw(board[i][j].r);

}
void Board::drawFruit(RenderWindow& window)
{
	if (fruit.edible == true)
		window.draw(fruit.f);
}