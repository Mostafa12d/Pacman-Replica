#pragma once
#include "Pacman.h" 
#include "Ghost.h" 
#include "Board.h" 
#include <vector>

using namespace std;
#define COUNT 182
#define INFINITY 999


class Graph
{
private:
	int graph[COUNT][COUNT];

public:
	Graph(int arr[21][17]);
	int findShortestPath(const Ghost& ghost, const Pacman& pacman, const Board& board, int pathIndex);

};

