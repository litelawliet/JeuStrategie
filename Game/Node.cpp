
#include "stdafx.h"
#include "Node.h"

//*************** Partie Node
// Constructeur de Node
Node::Node(int x_pos, int y_pos, Node* node_parent, Node* from, Node* to)
{
	x = x_pos;
	y = y_pos;
	parent = node_parent;

	if (from != nullptr && to != nullptr) cost = distManhattan(from, this) + distManhattan(this, to);
	else cost = 0;
}

Node::~Node()
{

}

// Assesseurs
int Node::getX()
{
	return x;
}

int Node::getY()
{
	return y;
}

Node* Node::getParent()
{
	return parent;
}

int Node::getCost()
{
	return cost;
}

void Node::setParent(Node* n)
{
	parent = n;
}

/**
Calcule la distance de Manhattan (distance entière) entre a et b
*/
int Node::distManhattan(Node* a, Node* b)
{
	return abs(b->getX() - a->getX()) + abs(b->getY() - a->getY());
}