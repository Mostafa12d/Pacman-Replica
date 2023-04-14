//Group Names: ABDELRAHMAN SAID, MOSTAFA IBRAHIM, MOHAMED FAKHERLDIN
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Score.h"
#include "Lives.h"
#include "Menu.h"
#include "Graph.h"
#define ROWS 21
#define COLUMNS 17	
using namespace std;
using namespace sf;


sf::RenderWindow window(VideoMode(1200, 1080), "Pacman");
Board board;
Pacman pacman;
Ghost  Blinky(8, 8, 0, 0); //8,8
Ghost Inky(11, 7, 0, 8); //11, 7
Ghost Pinky(11, 8, 0, 12); //11,8
Ghost Clyde(11, 9, 0, 4); //11,9
Lives lives;
Score score;
Menu menu;
Audio audio;
Graph graph(board.arr);




int main()
{
	srand(time(0));
	
	int inkyrand = rand() % 182, pinkyrand = rand() % 182, blinkyrand = rand() % 182, clyderand = rand() % 182;
	Clock pacmanClock;
	pacmanClock.restart();
	Clock ghostsClock;
	ghostsClock.restart(); //movement
	Clock frightModeClock;
	frightModeClock.restart();
	Clock fruitClock;
	fruitClock.restart();
	Clock InkyClock;
	InkyClock.restart();
	//Clock menuCLock;
	//menuCLock.restart();
	audio.playMenuMusic();

	int pelletsEaten = 0; // number of pellets eaten during the game
	bool win = false; // to draw the winning screen 
	bool lose = false; // to draw the game over screen
	bool scoreFlag = true; //To increment a live when the player reaches 1500.
	bool start = false;    //Controlling the start menu
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case Keyboard::Space:
					lose = false;
					break;
				case Keyboard::Return: //Press enter to start the game
					start = true;
					break;
				case Keyboard::Up:
					if (start == true) // a condition to make pacman unmovable while in the menu
						if (board.isStandable(pacman.getCurrentRow() - 1, pacman.getCurrentColumn())) // a condition to prevent pacman to move in the direction where he could be stopped by a wall 
							pacman.d = 'U';
					break;
				case Keyboard::Down:
					if (start == true)
						if (board.isStandable(pacman.getCurrentRow() + 1, pacman.getCurrentColumn()))
							pacman.d = 'D';
					break;
				case Keyboard::Right:
					if (start == true)
						if (board.isStandable(pacman.getCurrentRow(), pacman.getCurrentColumn() + 1))
							pacman.d = 'R';
					break;
				case Keyboard::Left:
					if (start == true)
						if (board.isStandable(pacman.getCurrentRow(), pacman.getCurrentColumn() - 1))
							pacman.d = 'L';
					break;
				}
			}
		}

		if (pacmanClock.getElapsedTime().asMicroseconds() >= 220000)
		{
			pacmanClock.restart();
			switch (pacman.d)
			{
			case 'U':
				pacman.move('U', board.isStandable(pacman.getCurrentRow() - 1, pacman.getCurrentColumn()));
				break;
			case 'D':
				pacman.move('D', board.isStandable(pacman.getCurrentRow() + 1, pacman.getCurrentColumn()));
				break;
			case 'L':
				pacman.move('L', board.isStandable(pacman.getCurrentRow(), pacman.getCurrentColumn() - 1));
				break;
			case 'R':
				pacman.move('R', board.isStandable(pacman.getCurrentRow(), pacman.getCurrentColumn() + 1));
				break;
			default:
				break;
			}
		}

		//Blinky
		if (start == true)
		{
			

			if (pacman.getSuper() == true && Blinky.getFrightMode() == true)
			{
				if (blinkyrand == board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn()])
					blinkyrand = rand() % 182;

				/*if (board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn()] == 71)
					Blinky.d = 'L';
				else if (board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn()] == 70)
					Blinky.d = 'R';*/
				else
				{
					if (graph.findShortestPath(Blinky, pacman, board, blinkyrand) == board.arr[Blinky.getCurrentRow() - 1][Blinky.getCurrentColumn()] && start == true)
						if (board.isStandable(Blinky.getCurrentRow() - 1, Blinky.getCurrentColumn()))
							Blinky.d = 'U';
					if (graph.findShortestPath(Blinky, pacman, board, blinkyrand) == board.arr[Blinky.getCurrentRow() + 1][Blinky.getCurrentColumn()] && start == true)
						if (board.isStandable(Blinky.getCurrentRow() + 1, Blinky.getCurrentColumn()))
							Blinky.d = 'D';
					if (graph.findShortestPath(Blinky, pacman, board, blinkyrand) == board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn() + 1] && start == true)
						if (board.isStandable(Blinky.getCurrentRow(), Blinky.getCurrentColumn() + 1))
							Blinky.d = 'R';
					if (graph.findShortestPath(Blinky, pacman, board, blinkyrand) == board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn() - 1] && start == true)
						if (board.isStandable(Blinky.getCurrentRow(), Blinky.getCurrentColumn() - 1))
							Blinky.d = 'L';
				}
			}
			else
			{
				if (graph.findShortestPath(Blinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Blinky.getCurrentRow() - 1][Blinky.getCurrentColumn()] && start == true)
					if (board.isStandable(Blinky.getCurrentRow() - 1, Blinky.getCurrentColumn()))
						Blinky.d = 'U';
				if (graph.findShortestPath(Blinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Blinky.getCurrentRow() + 1][Blinky.getCurrentColumn()] && start == true)
					if (board.isStandable(Blinky.getCurrentRow() + 1, Blinky.getCurrentColumn()))
						Blinky.d = 'D';
				if (graph.findShortestPath(Blinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn() + 1] && start == true)
					if (board.isStandable(Blinky.getCurrentRow(), Blinky.getCurrentColumn() + 1))
						Blinky.d = 'R';
				if (graph.findShortestPath(Blinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Blinky.getCurrentRow()][Blinky.getCurrentColumn() - 1] && start == true)
					if (board.isStandable(Blinky.getCurrentRow(), Blinky.getCurrentColumn() - 1))
						Blinky.d = 'L';
			}
		}

		//Pinky
		if (start == true)
		{
			if (pacman.getSuper() == true && Pinky.getFrightMode() == true)
			{
				if (pinkyrand == board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn()])
					pinkyrand = rand() % 182;
				/*if (board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn()] == 89)
					Pinky.d = 'D';
				else if (board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn()] == 100)
					Pinky.d = 'U';*/
				else
				{
					if (graph.findShortestPath(Pinky, pacman, board, pinkyrand) == board.arr[Pinky.getCurrentRow() - 1][Pinky.getCurrentColumn()] && start == true)
						if (board.isStandable(Pinky.getCurrentRow() - 1, Pinky.getCurrentColumn()))
							Pinky.d = 'U';
					if (graph.findShortestPath(Pinky, pacman, board, pinkyrand) == board.arr[Pinky.getCurrentRow() + 1][Pinky.getCurrentColumn()] && start == true)
						if (board.isStandable(Pinky.getCurrentRow() + 1, Pinky.getCurrentColumn()))
							Pinky.d = 'D';
					if (graph.findShortestPath(Pinky, pacman, board, pinkyrand) == board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn() + 1] && start == true)
						if (board.isStandable(Pinky.getCurrentRow(), Pinky.getCurrentColumn() + 1))
							Pinky.d = 'R';
					if (graph.findShortestPath(Pinky, pacman, board, pinkyrand) == board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn() - 1] && start == true)
						if (board.isStandable(Pinky.getCurrentRow(), Pinky.getCurrentColumn() - 1))
							Pinky.d = 'L';
				}

			}
			else
			{
				if (graph.findShortestPath(Pinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Pinky.getCurrentRow() - 1][Pinky.getCurrentColumn()] && start == true)
					if (board.isStandable(Pinky.getCurrentRow() - 1, Pinky.getCurrentColumn()))
						Pinky.d = 'U';
				if (graph.findShortestPath(Pinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Pinky.getCurrentRow() + 1][Pinky.getCurrentColumn()] && start == true)
					if (board.isStandable(Pinky.getCurrentRow() + 1, Pinky.getCurrentColumn()))
						Pinky.d = 'D';
				if (graph.findShortestPath(Pinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn() + 1] && start == true)
					if (board.isStandable(Pinky.getCurrentRow(), Pinky.getCurrentColumn() + 1))
						Pinky.d = 'R';
				if (graph.findShortestPath(Pinky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Pinky.getCurrentRow()][Pinky.getCurrentColumn() - 1] && start == true)
					if (board.isStandable(Pinky.getCurrentRow(), Pinky.getCurrentColumn() - 1))
						Pinky.d = 'L';
			}

		}
	
		//Inky
		
			if (InkyClock.getElapsedTime().asSeconds() >= 15 || score.getScore() >= 1000)
			{
			
				if (pacman.getSuper() == true && Inky.getFrightMode() == true)
				{
					if (inkyrand == board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn()])
						inkyrand = rand() % 182;

					/*if (board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn()] == 90)
						Inky.d = 'D';
					else if (board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn()] == 101)
						Inky.d = 'U';*/
					else
					{
						if (graph.findShortestPath(Inky, pacman, board, inkyrand) == board.arr[Inky.getCurrentRow() - 1][Inky.getCurrentColumn()] && start == true)
							if (board.isStandable(Inky.getCurrentRow() - 1, Inky.getCurrentColumn()))
								Inky.d = 'U';
						if (graph.findShortestPath(Inky, pacman, board, inkyrand) == board.arr[Inky.getCurrentRow() + 1][Inky.getCurrentColumn()] && start == true)
							if (board.isStandable(Inky.getCurrentRow() + 1, Inky.getCurrentColumn()))
								Inky.d = 'D';
						if (graph.findShortestPath(Inky, pacman, board, inkyrand) == board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn() + 1] && start == true)
							if (board.isStandable(Inky.getCurrentRow(), Inky.getCurrentColumn() + 1))
								Inky.d = 'R';
						if (graph.findShortestPath(Inky, pacman, board, inkyrand) == board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn() - 1] && start == true)
							if (board.isStandable(Inky.getCurrentRow(), Inky.getCurrentColumn() - 1))
								Inky.d = 'L';
					}
				}
				else
				{
					if (graph.findShortestPath(Inky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Inky.getCurrentRow() - 1][Inky.getCurrentColumn()] && start == true)
						if (board.isStandable(Inky.getCurrentRow() - 1, Inky.getCurrentColumn()))
							Inky.d = 'U';
					if (graph.findShortestPath(Inky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Inky.getCurrentRow() + 1][Inky.getCurrentColumn()] && start == true)
						if (board.isStandable(Inky.getCurrentRow() + 1, Inky.getCurrentColumn()))
							Inky.d = 'D';
					if (graph.findShortestPath(Inky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn() + 1] && start == true)
						if (board.isStandable(Inky.getCurrentRow(), Inky.getCurrentColumn() + 1))
							Inky.d = 'R';
					if (graph.findShortestPath(Inky, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Inky.getCurrentRow()][Inky.getCurrentColumn() - 1] && start == true)
						if (board.isStandable(Inky.getCurrentRow(), Inky.getCurrentColumn() - 1))
							Inky.d = 'L';
				}
			
			}
			else
			{
				if (Inky.getCurrentRow() == 11 && Inky.getCurrentColumn() == 7)
					Inky.d = 'U';
				if (Inky.getCurrentRow() == 10 && Inky.getCurrentColumn() == 7)
					Inky.d = 'D';
			}
		
		////Clyde
		
			if (InkyClock.getElapsedTime().asSeconds() >= 25)
			{
			
				if (pacman.getSuper() == true && Clyde.getFrightMode() == true)
				{
					if (clyderand == board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn()])
						clyderand = rand() % 182;
					/*if (board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn()] == 91)
						Clyde.d = 'D';
					else if (board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn()] == 102)
						Clyde.d = 'U';*/
					else
					{
						if (graph.findShortestPath(Clyde, pacman, board, clyderand) == board.arr[Clyde.getCurrentRow() - 1][Clyde.getCurrentColumn()] && start == true)
							if (board.isStandable(Clyde.getCurrentRow() - 1, Clyde.getCurrentColumn()))
								Clyde.d = 'U';
						if (graph.findShortestPath(Clyde, pacman, board, clyderand) == board.arr[Clyde.getCurrentRow() + 1][Clyde.getCurrentColumn()] && start == true)
							if (board.isStandable(Clyde.getCurrentRow() + 1, Clyde.getCurrentColumn()))
								Clyde.d = 'D';
						if (graph.findShortestPath(Clyde, pacman, board, clyderand) == board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn() + 1] && start == true)
							if (board.isStandable(Clyde.getCurrentRow(), Clyde.getCurrentColumn() + 1))
								Clyde.d = 'R';
						if (graph.findShortestPath(Clyde, pacman, board, clyderand) == board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn() - 1] && start == true)
							if (board.isStandable(Clyde.getCurrentRow(), Clyde.getCurrentColumn() - 1))
								Clyde.d = 'L';
					}
				}
				else
				{
					if (graph.findShortestPath(Clyde, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Clyde.getCurrentRow() - 1][Clyde.getCurrentColumn()] && start == true)
						if (board.isStandable(Clyde.getCurrentRow() - 1, Clyde.getCurrentColumn()))
							Clyde.d = 'U';
					if (graph.findShortestPath(Clyde, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Clyde.getCurrentRow() + 1][Clyde.getCurrentColumn()] && start == true)
						if (board.isStandable(Clyde.getCurrentRow() + 1, Clyde.getCurrentColumn()))
							Clyde.d = 'D';
					if (graph.findShortestPath(Clyde, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn() + 1] && start == true)
						if (board.isStandable(Clyde.getCurrentRow(), Clyde.getCurrentColumn() + 1))
							Clyde.d = 'R';
					if (graph.findShortestPath(Clyde, pacman, board, board.arr[pacman.getCurrentRow()][pacman.getCurrentColumn()]) == board.arr[Clyde.getCurrentRow()][Clyde.getCurrentColumn() - 1] && start == true)
						if (board.isStandable(Clyde.getCurrentRow(), Clyde.getCurrentColumn() - 1))
							Clyde.d = 'L';
				}
			
			}
			else
			{
				if (Clyde.getCurrentRow() == 11 && Clyde.getCurrentColumn() == 9)
					Clyde.d = 'U';
				if (Clyde.getCurrentRow() == 10 && Clyde.getCurrentColumn() == 9)
					Clyde.d = 'D';
			}
		


		if (ghostsClock.getElapsedTime().asMicroseconds() >= 300000)
		{
			ghostsClock.restart();
			switch (Blinky.d)
			{
			case 'U':
				Blinky.move('U', 3, board.isStandable(Blinky.getCurrentRow() - 1, Blinky.getCurrentColumn()));
				break;
			case 'D':
				Blinky.move('D', 0, board.isStandable(Blinky.getCurrentRow() + 1, Blinky.getCurrentColumn()));
				break;
			case 'R':
				Blinky.move('R', 2, board.isStandable(Blinky.getCurrentRow(), Blinky.getCurrentColumn() + 1));
				break;
			case 'L':
				Blinky.move('L', 1, board.isStandable(Blinky.getCurrentRow(), Blinky.getCurrentColumn() - 1));
				break;
			default:
				break;
			}

			switch (Pinky.d)
			{
			case 'U':
				Pinky.move('U', 15, board.isStandable(Pinky.getCurrentRow() - 1, Pinky.getCurrentColumn()));
				break;
			case 'D':
				Pinky.move('D', 12, board.isStandable(Pinky.getCurrentRow() + 1, Pinky.getCurrentColumn()));
				break;
			case 'R':
				Pinky.move('R', 14, board.isStandable(Pinky.getCurrentRow(), Pinky.getCurrentColumn() + 1));
				break;
			case 'L':
				Pinky.move('L', 13, board.isStandable(Pinky.getCurrentRow(), Pinky.getCurrentColumn() - 1));
				break;
			default:
				break;
			}

			switch (Inky.d)
			{
			case 'U':
				Inky.move('U', 11, board.isStandable(Inky.getCurrentRow() - 1, Inky.getCurrentColumn()));
				break;
			case 'D':
				Inky.move('D', 8, board.isStandable(Inky.getCurrentRow() + 1, Inky.getCurrentColumn()));
				break;
			case 'R':
				Inky.move('R', 10, board.isStandable(Inky.getCurrentRow(), Inky.getCurrentColumn() + 1));
				break;
			case 'L':
				Inky.move('L', 9, board.isStandable(Inky.getCurrentRow(), Inky.getCurrentColumn() - 1));
				break;
			default:
				break;
			}

			switch (Clyde.d)
			{
			case 'U':
				Clyde.move('U', 7, board.isStandable(Clyde.getCurrentRow() - 1, Clyde.getCurrentColumn()));
				break;
			case 'D':
				Clyde.move('D', 4, board.isStandable(Clyde.getCurrentRow() + 1, Clyde.getCurrentColumn()));
				break;
			case 'R':
				Clyde.move('R', 6, board.isStandable(Clyde.getCurrentRow(), Clyde.getCurrentColumn() + 1));
				break;
			case 'L':
				Clyde.move('L', 5, board.isStandable(Clyde.getCurrentRow(), Clyde.getCurrentColumn() - 1));
				break;
			default:
				break;
			}
		}

		if (fruitClock.getElapsedTime().asSeconds() >= 20 && board.isFruitEdible() != true)
		{
			board.setFruitEdible(true);
		}
		if (fruitClock.getElapsedTime().asSeconds() >= 30 && board.isFruitEdible() == true)
		{
			board.setFruitEdible(false);
		}


		if (pacman.getPlayer().getGlobalBounds().intersects(board.getFruit().getGlobalBounds()) && board.isFruitEdible() == true)
		{
			audio.playFruitSound();
			score.incrementScore(100);
			if (score.getScore() >= 1500 && scoreFlag == true)
			{
				scoreFlag = false;
				pacman.incrementLives();
			}
			board.setFruitEdible(false);
			fruitClock.restart();
		}



		for (int i = 0; i < 21; i++)
			for (int j = 0; j < 17; j++)
				if (!board.isEaten(i, j))
				{
					if (pacman.getPlayer().getGlobalBounds().intersects(board.getRectangle(i, j).getGlobalBounds()))
					{
						if ((i == 4 && j == 3) || (i == 4 && j == 13) || (i == 17 && j == 3) || (i == 17 && j == 13)) //super pellets positions
						{
							audio.playSuperPelletSound();//(n)
							board.eaten(i, j);
							score.incrementScore(50);
							pelletsEaten++;
							if (pelletsEaten == 164)
							{
								pelletsEaten = 0;
								start = false;
								win = true;
							}
							if (score.getScore() >= 1500 && scoreFlag == true)
							{
								pacman.incrementLives();
								scoreFlag = false;
							}
							pacman.setSuper(true);
							Blinky.setFrightMode(true);
							Inky.setFrightMode(true);
							Pinky.setFrightMode(true);
							Clyde.setFrightMode(true);
							frightModeClock.restart();
						}
						else
						{
							audio.playPelletSound();//(n)
							board.eaten(i, j);
							score.incrementScore(10);
							pelletsEaten++;
							if (pelletsEaten == 164)
							{
								pelletsEaten = 0;
								start = false;
								win = true;
								
							}
							if (score.getScore() >= 1500 && scoreFlag == true)
							{
								pacman.incrementLives();
								scoreFlag = false;
							}

						}
					}

				}

		//Fright mode ends after 10 seconds
		if (pacman.getSuper() == true && frightModeClock.getElapsedTime().asSeconds() >= 10)
		{
			pacman.setSuper(false);
			Blinky.setFrightMode(false);
			Inky.setFrightMode(false);
			Pinky.setFrightMode(false);
			Clyde.setFrightMode(false);
		}

		pacman.collide(Blinky, pacman.getSuper(), score, scoreFlag, start);
		pacman.collide(Inky, pacman.getSuper(), score, scoreFlag, start);
		pacman.collide(Pinky, pacman.getSuper(), score, scoreFlag, start);
		pacman.collide(Clyde, pacman.getSuper(), score, scoreFlag, start);
		if (pacman.getLives() == 0)
		{
			start = false;
			win = false;
			lose = true;
			pacman.setLives(3);
			score.resetScore();
			pacman.resetPosition();
			Blinky.resetPosition();
			Inky.resetPosition();
			Pinky.resetPosition();
			Clyde.resetPosition();
			pacmanClock.restart();
			ghostsClock.restart();
			frightModeClock.restart();
			fruitClock.restart();
			InkyClock.restart();
			//board.resetPellets();
		}


		window.clear();
		if (start == false && win == false && lose == false)
			menu.drawOnWindow(window);
		if (start == true && win == false)
		{
			board.drawOnWindow(window);
			if (board.isFruitEdible() == true)
				board.drawFruit(window);
			pacman.drawOnBoard(window);
			Blinky.drawOnBoard(window);
			Inky.drawOnBoard(window);
			Pinky.drawOnBoard(window);
			Clyde.drawOnBoard(window);
			score.drawOnWindow(window);
			lives.drawOnBoard(window, pacman.getLives());
		}
		if (win == true && start == false)
			menu.drawWin(window);
		if (win == false && start == false && lose == true)
			menu.drawGameover(window);

		window.display();
	}
system("pause");
}





