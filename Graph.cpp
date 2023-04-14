#include "Graph.h"

Graph::Graph(int arr[21][17])
{
	int target = 0;

	//Initializes all the graph to 0s.
	for (int i = 0; i < COUNT; i++)
		for (int j = 0; j < COUNT; j++)
			graph[i][j] = 0;

	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 17; j++)
		{
			if (arr[i][j] != -1)
			{
				//checking for an edge with the upward tile
				if (i - 1 >= 0 && arr[i - 1][j] != -1) //if not out of the bounds of the board, and the tile above it is not -1, create an edge.
					graph[arr[i][j]][arr[i - 1][j]] = 1;

				//checking for an edge with the downward tile
				if (i + 1 <= 20 && arr[i + 1][j] != -1)
					graph[arr[i][j]][arr[i + 1][j]] = 1;

				//checking for an edge with the right tile
				if (j + 1 <= 16 && arr[i][j + 1] != -1)
					graph[arr[i][j]][arr[i][j + 1]] = 1;

				//checking for an edge with the left tile
				if (j - 1 >= 0 && arr[i][j - 1] != -1)
					graph[arr[i][j]][arr[i][j - 1]] = 1;
			}

			//Creating edges with the portals.
			graph[83][97] = 1;
			graph[97][83] = 1;

		}
}

int Graph::findShortestPath(const Ghost& ghost, const Pacman& pacman, const Board& board, int pathIndex)
{
	//if (ghost.getCurrentColumn() != pacman.getCurrentColumn() && ghost.getCurrentRow() != pacman.getCurrentRow())
	if ((ghost.getCurrentColumn() + 1 != pacman.getCurrentColumn() && pacman.d != 'L' && ghost.getCurrentRow() != pacman.getCurrentRow()) ||
		(ghost.getCurrentColumn() - 1 != pacman.getCurrentColumn() && pacman.d != 'R' && ghost.getCurrentRow() != pacman.getCurrentRow()) ||
		(ghost.getCurrentColumn() != pacman.getCurrentColumn() && pacman.d != 'U' && ghost.getCurrentRow() - 1 != pacman.getCurrentRow()) ||
		(ghost.getCurrentColumn() != pacman.getCurrentColumn() && pacman.d != 'D' && ghost.getCurrentRow() + 1 != pacman.getCurrentRow()))
	{
		int temp[COUNT][COUNT], costs[COUNT], previous[COUNT];
		bool visited[COUNT];

		////initializing temp
		for (int i = 0; i < COUNT; i++)
			for (int j = 0; j < COUNT; j++)
				if (graph[i][j] == 0)
					temp[i][j] = INFINITY;
				else
					temp[i][j] = graph[i][j];

		////1st row
		////initializing costs, previous, visited
		for (int i = 0; i < COUNT; i++)
		{
			costs[i] = temp[board.arr[ghost.getCurrentRow()][ghost.getCurrentColumn()]][i];
			previous[i] = board.arr[ghost.getCurrentRow()][ghost.getCurrentColumn()];
			visited[i] = false;
		}
		costs[board.arr[ghost.getCurrentRow()][ghost.getCurrentColumn()]] = 0;
		visited[board.arr[ghost.getCurrentRow()][ghost.getCurrentColumn()]] = true;

		////rest of the rows
		int count = 1, nextNode = 0, minimumCost;
		while (count < COUNT)
		{
			minimumCost = INFINITY;
			for (int i = 0; i < COUNT; i++)
			{
				if ((costs[i] < minimumCost) && visited[i] == false)
				{
					minimumCost = costs[i];
					nextNode = i;
				}
			}
			visited[nextNode] = true;
			for (int i = 0; i < COUNT; i++)
				if ((minimumCost + temp[nextNode][i] < costs[i]) && (visited[i] == false))
				{
					costs[i] = minimumCost + temp[nextNode][i];
					previous[i] = nextNode;
				}
			count++;
		}

		int j;
		vector<vector<int>> paths;
		paths.resize(COUNT);
		for (int i = 0; i < COUNT; i++)
		{
			paths[i].push_back(i);
			if (i != board.arr[ghost.getCurrentRow()][ghost.getCurrentColumn()])
			{
				j = i;
				do
				{
					j = previous[j];
					paths[i].insert(paths[i].begin(), j);
					//paths[i].push_back(j);
				} while (j != board.arr[ghost.getCurrentRow()][ghost.getCurrentColumn()]);
			}
		}

		//returning the number of the first tile in the shortest path to pacman.
		int firstMovement = paths[pathIndex][1];
		return firstMovement;
	}
}
