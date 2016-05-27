/**
* \file map.h
* \brief Header des fonctions chargement de la map et du graph associé
* \date 27 mai 2016
*
* Header qui contient les definitions des fonctions et des structures de chargement de la map et de generation du graph associé
*
*/
#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "graphe.h"

/**
* \struct sMap
* \brief Structure qui représente une map 
*/
typedef struct s_map {
	FILE *recipe;
	struct s_case **path;

	sDimension mapDimension;
	int nodeAmount;
	sPosition starting;
	sPosition ending;
}sMap;

/**
* \struct sCase
* \brief Structure qui représente une case de map
*/
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