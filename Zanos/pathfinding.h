/**
* \file pathfinding.h
* \brief Header des fonctions de calcul du plus court chemin
* \date 27 mai 2016
*
* Header qui contient les definitions des fonctions de calcul du plus court chemin dans un graph 
*
*/
#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "definition.h"
#include "metric.h"
#include "map.h"
#include "graphe.h"
#include "liste.h"

sList *dijkstra(sMap *p_map, sPosition p_startPoint);
int nodeDistance(sNode *p_node, eDirection p_direction);


#endif
