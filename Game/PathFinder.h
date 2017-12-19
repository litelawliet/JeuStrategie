#pragma once

#pragma once

#include <vector>
#include "Node.h"

class PathFinder
{
public:
	PathFinder();
	~PathFinder();
	std::vector<Node*> getNodesFromTo(int** map, int map_width, int map_heigth, Node* from, Node* to);
private:
	Node* from;
	Node* to;
	int** map;
	int width;
	int heigth;
	bool isObstacle(int value);
	void getNeighbors(Node* current, std::vector<Node*> & visited, std::vector<Node*> & to_explore);
	bool contains(std::vector<Node*> v, Node* n); // ...
	Node* getBestNode(std::vector<Node*> v);
	void visiterNode(std::vector<Node*> & to_explore, Node* n);
};