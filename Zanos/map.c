/**
* \file map.c
* \brief Programme de chargement de la map et du graph associ�
* \date 27 mai 2016
*
* Programme qui realise le chargement de la map et de generation du graph associ�
*
*/
#include "map.h"
#include <time.h>

/**
* \fn int loadMap(sMap **p_map, char *p_recipePath)
* \brief Fonction de chargement de la map
*
* \param **p_map double pointeur vers un structure de type sMap repr�sentant la map de l'enigme
* \param *p_recipepath chemin du fichier de configuration de la map
* \return int repr�sentant le d�roulement de la fonction
*/
int loadMap(sMap **p_map, char *p_recipePath) {
	int l_i, l_j;
	
	sMap *l_map = malloc(sizeof(sMap));

	fopen_s(&(l_map->recipe), p_recipePath, "r");
	fscanf_s(l_map->recipe, "%d\t%d\n", &(l_map->mapDimension.height), &(l_map->mapDimension.width));
	fscanf_s(l_map->recipe, "%d\t%d\t%d\t%d\n", &(l_map->starting.y), &(l_map->starting.x), &(l_map->ending.y), &(l_map->ending.x));
	l_map->nodeAmount = 0;

	l_map->path = malloc(l_map->mapDimension.height * sizeof(sCase*));
	for (l_i = 0; l_i < l_map->mapDimension.height; ++l_i) {
		l_map->path[l_i] = malloc(l_map->mapDimension.width * sizeof(sCase));
	}

	for (l_i = 0; l_i < l_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < l_map->mapDimension.width; ++l_j) {
			fscanf_s(l_map->recipe, "\t%d", &(l_map->path[l_i][l_j].type));
			l_map->path[l_i][l_j].noded = FALSE;
			l_map->path[l_i][l_j].position.x = l_j;
			l_map->path[l_i][l_j].position.y = l_i;

			l_map->path[l_i][l_j].node.poids = -1;
			l_map->path[l_i][l_j].node.checked = FALSE;
			l_map->path[l_i][l_j].node.previous = NULL; 
			l_map->path[l_i][l_j].node.position.x = l_j;
			l_map->path[l_i][l_j].node.position.y = l_i;
		}
		fscanf_s(l_map->recipe, "\n");
	}

	*p_map = l_map;

	fclose(l_map->recipe);
	return 0;
}

/**
* \fn int generateGraph(sMap *p_map)
* \brief Fonction generation du graph associ� � une map
*
* \param *p_map pointeur vers un structure de type sMap repr�sentant la map de l'enigme
* \return int repr�sentant le d�roulement de la fonction
*/
int generateGraph(sMap *p_map) {
	int l_i, l_j;

	eCase_type l_tmpType;

	for (l_i = 0; l_i < p_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < p_map->mapDimension.width; ++l_j) {
			l_tmpType = p_map->path[l_i][l_j].type;

			p_map->path[l_i][l_j].node.neighbourUP = NULL;
			p_map->path[l_i][l_j].node.neighbourRIGHT = NULL;
			p_map->path[l_i][l_j].node.neighbourDOWN = NULL;
			p_map->path[l_i][l_j].node.neighbourLEFT = NULL;

			if (l_tmpType == RIGHT || l_tmpType == DOWN || l_tmpType == LEFT || l_tmpType == RIGHTDOWN || l_tmpType == DOWNLEFT || l_tmpType == RIGHTDOWNLEFT) {
				p_map->path[l_i][l_j].node.neighbourUP = findNeighbour(p_map, p_map->path[l_i][l_j].position, DUP);
				p_map->path[l_i][l_j].noded = TRUE;
			}
			if (l_tmpType == UP || l_tmpType == DOWN || l_tmpType == LEFT || l_tmpType == DOWNLEFT || l_tmpType == UPLEFT || l_tmpType == UPDOWNLEFT) {
				p_map->path[l_i][l_j].node.neighbourRIGHT = findNeighbour(p_map, p_map->path[l_i][l_j].position, DRIGHT);
				p_map->path[l_i][l_j].noded = TRUE;
			}
			if (l_tmpType == UP || l_tmpType == RIGHT || l_tmpType == LEFT || l_tmpType == UPRIGHT || l_tmpType == UPLEFT || l_tmpType == UPRIGHTLEFT) {
				p_map->path[l_i][l_j].node.neighbourDOWN = findNeighbour(p_map, p_map->path[l_i][l_j].position, DDOWN);
				p_map->path[l_i][l_j].noded = TRUE;
			}
			if (l_tmpType == UP || l_tmpType == RIGHT || l_tmpType == DOWN || l_tmpType == UPRIGHT || l_tmpType == RIGHTDOWN || l_tmpType == UPRIGHTDOWN) {
				p_map->path[l_i][l_j].node.neighbourLEFT = findNeighbour(p_map, p_map->path[l_i][l_j].position, DLEFT);
				p_map->path[l_i][l_j].noded = TRUE;
			}

			if (p_map->path[l_i][l_j].noded)
				p_map->nodeAmount++;		
		}
	}

	printf("[NODE AMMOUNT] %d\n", p_map->nodeAmount);

	return 0;
}

/**
* \fn sNode *findNeighbour(sMap *p_map, sPosition p_position, eDirection p_direction)
* \brief Fonction qui genere les arete d'un noeud de graph
*
* \param *p_map pointeur vers un structure de type sMap repr�sentant la map de l'enigme
* \param p_position position d'index du noeud 
* \param p_direction direction du voisin que l'on cherche
* \return sNode* pointeur vers un noeud de graph
*/
sNode *findNeighbour(sMap *p_map, sPosition p_position, eDirection p_direction) {
	int l_i, l_j;

	eCase_type l_tmpType;

	switch (p_direction) {
		case(DUP) :
			l_i = (int)p_position.y;
			l_j = (int)p_position.x;
			l_tmpType = p_map->path[l_i][l_j].type;
			while (l_tmpType != UP && l_tmpType != UPRIGHT && l_tmpType != UPLEFT && l_tmpType != UPRIGHTLEFT) {
				l_i--;
				l_tmpType = p_map->path[l_i][l_j].type;
			}
			return &(p_map->path[l_i][l_j].node);
			break;

		case(DRIGHT):
			l_i = (int)p_position.y;
			l_j = (int)p_position.x;
			l_tmpType = p_map->path[l_i][l_j].type;
			while (l_tmpType != RIGHT && l_tmpType != UPRIGHT && l_tmpType != RIGHTDOWN && l_tmpType != UPRIGHTDOWN) {
				l_j++;
				l_tmpType = p_map->path[l_i][l_j].type;
			}
			return &(p_map->path[l_i][l_j].node);
			break;

		case(DDOWN):
			l_i = (int)p_position.y;
			l_j = (int)p_position.x;
			l_tmpType = p_map->path[l_i][l_j].type;
			while (l_tmpType != DOWN && l_tmpType != RIGHTDOWN && l_tmpType != DOWNLEFT && l_tmpType != RIGHTDOWNLEFT) {
				l_i++;
				l_tmpType = p_map->path[l_i][l_j].type;
			}
			return &(p_map->path[l_i][l_j].node);
			break;

		case(DLEFT):
			l_i = (int)p_position.y;
			l_j = (int)p_position.x;
			l_tmpType = p_map->path[l_i][l_j].type;
			while (l_tmpType != LEFT && l_tmpType != DOWNLEFT && l_tmpType != UPLEFT && l_tmpType != UPDOWNLEFT) {
				l_j--;
				l_tmpType = p_map->path[l_i][l_j].type;
			}
			return &(p_map->path[l_i][l_j].node);
			break;

		default:
			return NULL;
			break;
	}
}
