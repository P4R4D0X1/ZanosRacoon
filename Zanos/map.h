#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "graphe.h"

typedef struct s_map {
	FILE *recipe;
	struct s_case **path;

	int height;
	int width;
	int nodeAmount;
	sPosition starting;
	sPosition ending;
}sMap;

typedef struct s_case {
	eCase_type type;
	bool noded;
	sPosition position;

	struct s_node node;
}sCase;

int loadMap(sMap **p_map, char *p_recipePath);
int generateGraph(sMap *p_map);
sNode *findNeighbour(sMap *p_map, sPosition p_position, eDirection p_direction);
void printMap(sMap *p_map);

#endif