#include "pathfinding.h"

sList *dijkstra(sMap *p_map, sPosition p_startPoint) {
	int l_i, l_j, l_k;

	sNode **l_nodeList = malloc(p_map->nodeAmount * sizeof(sNode*));
	sNode *l_tmpNode = NULL, *l_theFirendOfTheFirstTMPNode = NULL;
	sList *l_solutionPath = NULL;

	p_map->path[(int)(p_startPoint.y)][(int)(p_startPoint.x)].node.poids = 0;

	l_k = 0;
	for (l_i = 0; l_i < p_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < p_map->mapDimension.width; ++l_j) {
			if (p_map->path[l_i][l_j].noded) {
				l_nodeList[l_k] = &(p_map->path[l_i][l_j].node);
				l_k++;
			}
		}
	}

	while (!(p_map->path[(int)(p_map->ending.y)][(int)(p_map->ending.x)].node.checked)) {
		l_j = 0xFFFF;
		l_k = 0;
		for (l_i = 0; l_i < p_map->nodeAmount; ++l_i) {
			if (!(l_nodeList[l_i]->checked) && l_nodeList[l_i]->poids != -1 && l_nodeList[l_i]->poids < l_j) {
				l_j = l_nodeList[l_i]->poids;
				l_k = l_i;
			}
		}

		l_nodeList[l_k]->checked = TRUE;

		if (l_nodeList[l_k]->neighbourUP) {
			l_tmpNode = (l_nodeList[l_k]->neighbourUP);
			if (!(l_tmpNode->checked) && (((l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DUP)) < l_tmpNode->poids) || (l_tmpNode->poids == -1))) {
				l_tmpNode->poids = l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DUP);
				l_tmpNode->previous = l_nodeList[l_k];
			}
		}

		if (l_nodeList[l_k]->neighbourRIGHT) {
			l_tmpNode = (l_nodeList[l_k]->neighbourRIGHT);
			if (!(l_tmpNode->checked) && (((l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DRIGHT)) < l_tmpNode->poids) || (l_tmpNode->poids == -1))) {
				l_tmpNode->poids = l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DRIGHT);
				l_tmpNode->previous = l_nodeList[l_k];
			}
		}

		if (l_nodeList[l_k]->neighbourDOWN) {
			l_tmpNode = (l_nodeList[l_k]->neighbourDOWN);
			if (!(l_tmpNode->checked) && (((l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DDOWN)) < l_tmpNode->poids) || (l_tmpNode->poids == -1))) {
				l_tmpNode->poids = l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DDOWN);
				l_tmpNode->previous = l_nodeList[l_k];
			}
		}

		if (l_nodeList[l_k]->neighbourLEFT) {
			l_tmpNode = (l_nodeList[l_k]->neighbourLEFT);
			if (!(l_tmpNode->checked) && (((l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DLEFT)) < l_tmpNode->poids) || (l_tmpNode->poids == -1))) {
				l_tmpNode->poids = l_nodeList[l_k]->poids + nodeDistance(l_nodeList[l_k], DLEFT);
				l_tmpNode->previous = l_nodeList[l_k];
			}
		}
	}

	l_tmpNode = &(p_map->path[(int)(p_map->ending.y)][(int)(p_map->ending.x)].node);
	addFirst(&l_solutionPath, p_map->path[(int)(p_map->ending.y)][(int)(p_map->ending.x)].position);
	while (l_tmpNode->previous) {
		l_theFirendOfTheFirstTMPNode = l_tmpNode->previous;
		addFirst(&l_solutionPath, l_theFirendOfTheFirstTMPNode->position);
		l_tmpNode = l_theFirendOfTheFirstTMPNode;
	}
	
	return l_solutionPath;
}

int nodeDistance(sNode *p_node, eDirection p_direction) {
	int distance;

	sPosition l_distance;
	sNode *l_tmpNode;

	switch (p_direction) {
		case(DUP) :
			l_tmpNode = p_node->neighbourUP;
			l_distance = p_node->position;
			l_distance.x -= l_tmpNode->position.x;
			l_distance.y -= l_tmpNode->position.y;
			break;
		case(DRIGHT) :
			l_tmpNode = p_node->neighbourRIGHT;
			l_distance = p_node->position;
			l_distance.x -= l_tmpNode->position.x;
			l_distance.y -= l_tmpNode->position.y;
			break;
		case(DDOWN) :
			l_tmpNode = p_node->neighbourDOWN;
			l_distance = p_node->position;
			l_distance.x -= l_tmpNode->position.x;
			l_distance.y -= l_tmpNode->position.y;
			break;
		case(DLEFT) :
			l_tmpNode = p_node->neighbourLEFT;
			l_distance = p_node->position;
			l_distance.x -= l_tmpNode->position.x;
			l_distance.y -= l_tmpNode->position.y;
			break;
	}

	distance = l_distance.x + l_distance.y;
	distance = (int)sqrt(pow(distance, 2));

	return distance;
}