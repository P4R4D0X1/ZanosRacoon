#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"

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