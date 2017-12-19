#pragma once

#include <math.h>

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