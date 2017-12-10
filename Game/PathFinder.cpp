/*
	Utiliser  getNodesFromTo.
	Récupère une liste de Nodes représentant le chemin à prendre  ( = cases)
*/

#include "PathFinder.h"
#include <math.h>

PathFinder::PathFinder()
{
	/* Empty constructor */
}

PathFinder::~PathFinder()
{

}

// Unique méthode publique à appeler pour trouver son chemin
std::vector<Node*> PathFinder::getNodesFromTo(int** map, int map_witdh, int map_heigth, Node* from, Node* to) 
{
	// Initialisations diverses
	this->map = map;
	this->from = from;
	this->to = to;

	width = map_witdh;
	heigth = map_heigth;

	std::vector<Node*> visited; // nœuds explorés
	std::vector<Node*> to_explore; // nœuds à explorer

	to_explore.push_back(from);

	// Exploration :D
	while (!to_explore.empty() && !contains(to_explore, to)) {
		getNeighbors(getBestNode(to_explore), visited, to_explore);
	}

	// Construction d'une liste de retour
	std::vector<Node*> result;

	Node* n = to;
	while (n != from) {
		result.insert(result.begin(), n);
		n = n->getParent();
	}
}

/**
	Renvoie true si la valeur entière donnée est un obstacle. (valeur de map) à modifier
*/
bool PathFinder::isObstacle(int value)
{
	return false;
}


/**
	Ajoute les voisins du nœud à la liste à explorer, et met le nœud courant en visité
*/
void PathFinder::getNeighbors(Node* current, std::vector<Node*> visited, std::vector<Node*> to_explore)
{
	int x = current->getX;
	int y = current->getY;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			if (i == 0 && j == 0) continue;
			if (x + i < 0 || y + j < 0 || x + i >= heigth || y + j >= width) continue;
			if (isObstacle(map[x + i][y + j])) continue;

			if (x + i == to->getX && y + j == to->getY) to->setParent(current);

			Node* n = new Node(x+i, y+j, current, from, to);

			if(!contains(visited, n)) to_explore.push_back(n);
		}
	}
	visiterNode(to_explore, current);
	visited.push_back(current);

}

bool PathFinder::contains(std::vector<Node*> v, Node* n)
{
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == n) return true;
	}

	return false;
}

// Chope le nœud ayant le coût le moins élevé dans la liste des à explorer
Node* PathFinder::getBestNode(std::vector<Node*> v) 
{
	Node* n = v[0];

	for (int i = 1; i < v.size(); i++) {
		if (v[i]->getCost() < n->getCost) n = v[i];
	}

	return n;
}

// Retire un nœud exploré de la liste to_explore
void PathFinder::visiterNode(std::vector<Node*> to_explore, Node* n)
{
	int pos = -1;
	int i = 0;
	while (pos == -1) {
		if (i >= to_explore.size()) return;
		if (to_explore[i] == n) pos = i;
		i++;
	}

	to_explore.erase(to_explore.begin(), to_explore.begin() + pos)
}

//*************** Partie Node
// Constructeur de Node
Node::Node(int x_pos, int y_pos, Node* node_parent, Node* from, Node* to) 
{
	x = x_pos;
	y = y_pos;
	parent = node_parent;

	cost = distManhattan(from, this) + distManhattan(this, to);
}

Node::~Node()
{

}

// Assesseurs en lecture
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