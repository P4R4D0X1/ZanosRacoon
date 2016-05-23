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
