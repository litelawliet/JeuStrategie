#pragma once

#include <vector>

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
	void getNeighbors(Node* current, std::vector<Node*> visited, std::vector<Node*> to_explore);
	bool contains(std::vector<Node*> v, Node* n); // ...
	Node* getBestNode(std::vector<Node*> v);
	void visiterNode(std::vector<Node*> to_explore, Node* n);
};

class Node
{
public:
	Node(int x, int y, Node* parent, Node* from, Node* to);
	~Node();
	int getX();
	int getY();
	Node* getParent();
	int getCost();
	void setParent(Node* n);
private:
	Node* parent; // null if is unit position
	int x;
	int y;
	int cost;
	int distManhattan(Node* a, Node* b);
};