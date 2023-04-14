#include "Menu.h"

Menu::Menu()
{
	image1_Texture.loadFromFile("Menu.png");
	image1.setTexture(image1_Texture);
	image1.setPosition(230, 50);

	font.loadFromFile("pacman font.ttf");
	text2.setFont(font);
	text2.setCharacterSize(15);
	text2.setString("CSCE110101 - Fundamentals of Computing II - Dr.Howaida Ismail ");
	text2.setPosition(140, 270);

	image2_Texture.loadFromFile("menu image.png");
	image2.setTexture(image2_Texture);
	image2.setPosition(350, 400);

	font.loadFromFile("pacman font.ttf");
	text1.setFont(font);
	text1.setCharacterSize(20);
	text1.setString("Press Enter to play");
	text1.setPosition(400, 900);

	 //Game Over text (n)
	font.loadFromFile("pacman font.ttf");
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(20);
	gameOverText.setString("Press space to return to the menu");
	gameOverText.setPosition(270, 800);
	// game over image
	gameOver_Texture.loadFromFile("gameover.png");
	gameOverImage.setTexture(gameOver_Texture);
	gameOverImage.setScale(0.54f, 0.54f);
	gameOverImage.setPosition(110, 300);
	// wining text (n)
	font.loadFromFile("pacman font.ttf");
	win.setFont(font);
	win.setCharacterSize(40);
	win.setString("Level Cleared!");
	win.setPosition(320, 70);

}
void Menu::drawOnWindow(RenderWindow& window)
{
	window.draw(image1);
	window.draw(image2);
	window.draw(text1);
	window.draw(text2);
}
void Menu::drawGameover(RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(gameOverImage);
}
void Menu::drawWin(RenderWindow& window)
{
	window.draw(win);
	window.draw(image2);
}
//void Menu::drawScore(RenderWindow& window)
//{	
//	window.draw(score);
//}
//void Menu::setScore(int s)
//{
//	font.loadFromFile("pacman font.ttf");
//	stream << "Score:" << s;
//	score.setCharacterSize(20);
//	score.setPosition(400, 215);
//	score.setFont(font);
//	score.setString(stream.str());
//}
//void Menu::drawLives(RenderWindow& window, int l)
//{
//	livesTexture.loadFromFile("super pellet.png");
//	for (int i = 0; i < 4; i++)
//	{
//		lives[i].setPosition(836 + (i * 48), 595);
//		lives[i].setTexture(livesTexture);
//	}
//	for (int i = 0; i < l; i++)
//		window.draw(lives[i]);
//}