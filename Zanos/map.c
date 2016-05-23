#include "map.h"

int loadMap(sMap **p_map, char *p_recipePath) {
	int l_i, l_j;
	
	sMap *l_map = malloc(sizeof(sMap));

	fopen_s(&(l_map->recipe), p_recipePath, "r");
	fscanf_s(l_map->recipe, "%d\t%d\n", &(l_map->mapDimension.height), &(l_map->mapDimension.width));
	fscanf_s(l_map->recipe, "%f\t%f\t%f\t%f\n", &(l_map->starting.y), &(l_map->starting.x), &(l_map->ending.y), &(l_map->ending.x));
	l_map->nodeAmount = 0;

	l_map->path = malloc(l_map->mapDimension.height * sizeof(sCase*));
	for (l_i = 0; l_i < l_map->mapDimension.height; ++l_i) {
		l_map->path[l_i] = malloc(l_map->mapDimension.width * sizeof(sCase));
	}

	for (l_i = 0; l_i < l_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < l_map->mapDimension.width; ++l_j) {
			fscanf_s(l_map->recipe, "\t%d", &(l_map->path[l_i][l_j].type));
			l_map->path[l_i][l_j].noded = FALSE;
			l_map->path[l_i][l_j].position.x = (float)l_j;
			l_map->path[l_i][l_j].position.y = (float)l_i;

			l_map->path[l_i][l_j].node.poids = -1;
			l_map->path[l_i][l_j].node.checked = FALSE;
			l_map->path[l_i][l_j].node.previous = NULL; 
			l_map->path[l_i][l_j].node.position.x = (float)l_j;
			l_map->path[l_i][l_j].node.position.y = (float)l_i;
		}
		fscanf_s(l_map->recipe, "\n");
	}

	//l_map->path[(int)(l_map->starting.y)][(int)(l_map->starting.x)].node.poids = 0;

	*p_map = l_map;

	fclose(l_map->recipe);
	return 0;
}

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

void printMap(sMap *p_map) {
	int l_i, l_j;

	for (l_i = 0; l_i < p_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < p_map->mapDimension.width; ++l_j) {
			if (p_map->path[l_i][l_j].noded) {
				printf("X\t");
			}
			else {
				printf("%d\t", p_map->path[l_i][l_j].type);
			}
		}
		printf("\n");
	}

	return;
}