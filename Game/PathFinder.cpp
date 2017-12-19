
#include "stdafx.h"
#include "PathFinder.h"
#include <iostream>

PathFinder::PathFinder()
{
	/* Empty constructor */
}

PathFinder::~PathFinder()
{

}

// Unique m�thode publique � appeler pour trouver son chemin
std::vector<Node*> PathFinder::getNodesFromTo(int** map, int map_witdh, int map_heigth, Node* from, Node* to)
{

	// Initialisations diverses
	this->map = map;
	this->from = from;
	this->to = to;

	width = map_witdh;
	heigth = map_heigth;

	std::vector<Node*> visited; // n�uds explor�s
	std::vector<Node*> to_explore; // n�uds � explorer

	to_explore.push_back(from);

	// Exploration :D
	while (!to_explore.empty() && !contains(to_explore, to)) {
		getNeighbors(getBestNode(to_explore), visited, to_explore);
	}

	// Construction d'une liste de retour
	std::vector<Node*> result;

	Node* n;

	if (to_explore.empty()) n = to->getParent(); // Le chemin est bloqu� quelque part, on essaie de rapprocher le plus possible
	else n = to; // Un chemin existe, il va direct � la destination

	// * on remonte tout le chemin *
	while (n != from) {
		result.insert(result.begin(), n);
		n = n->getParent();
	}

	return result;
}

/**
Renvoie true si la valeur enti�re donn�e est un obstacle. (valeur de map) - M�thode � modifier si besoin
*/
bool PathFinder::isObstacle(int value)
{
	if (value == 1) return true;
	return false;
}


/**
Ajoute les voisins du n�ud � la liste � explorer, et met le n�ud courant en visit�
*/
void PathFinder::getNeighbors(Node* current, std::vector<Node*> & visited, std::vector<Node*> & to_explore)
{
	int x = current->getX();
	int y = current->getY();


	// Pour chaque voisin

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			if (i == 0 && j == 0) continue; // C'est le n�ud courant
			if (x + i < 0 || y + j < 0 || x + i >= heigth || y + j >= width) continue; // Ce n�ud n'existe pas
			if (isObstacle(map[x + i][y + j])) continue; // C'est un obstacle

			to->setParent(current);

			Node* n = new Node(x + i, y + j, current, from, to);

			// le n�ud ne doit pas �tre d�j� visit� ni �tre pr�vu pour l'exploration
			if (!contains(visited, n) && !contains(to_explore, n)) to_explore.push_back(n);
		}
	}
	// le n�ud courant est mis de c�t�
	visiterNode(to_explore, current);
	visited.push_back(current);

}

// Tout est dans le nom, v�rifie si n est dans v
bool PathFinder::contains(std::vector<Node*> v, Node* n)
{
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i] == n) return true;
		if (v[i]->getX() == n->getX() && v[i]->getY() == n->getY()) return true;
	}

	return false;
}

// Chope le n�ud ayant le co�t le moins �lev� dans la liste des � explorer
Node* PathFinder::getBestNode(std::vector<Node*> v)
{
	Node* n = v[0];

	for (unsigned int i = 1; i < v.size(); i++) {
		if (v[i]->getCost() < n->getCost()) n = v[i];
	}

	return n;
}

// Retire un n�ud explor� de la liste to_explore
void PathFinder::visiterNode(std::vector<Node*> & to_explore, Node* n)
{
	int pos = -1;
	unsigned int i = 0;
	while (pos == -1) {
		if (i >= to_explore.size()) return;
		if (to_explore[i] == n || to_explore[i]->getX() == n->getX() && to_explore[i]->getY() == n->getY()) pos = i;
		i++;
	}

	to_explore.erase(to_explore.begin() + pos);
}