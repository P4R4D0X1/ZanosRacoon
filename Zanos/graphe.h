/**
* \file graphe.h
* \brief Header de definition des noeuds de graphe
* \date 27 mai 2016
*
* Header qui contient la strcture d'un noeud de graphe
*
*/
#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"

/**
* \struct sNode
* \brief Structure qui un noeud de graphe
*/
typedef struct s_node {
	int poids;
	bool checked;
	sPosition position;

	struct s_node *previous;

	struct s_node *neighbourUP;
	struct s_node *neighbourRIGHT;
	struct s_node *neighbourDOWN;
	struct s_node *neighbourLEFT;
}sNode;

#endif