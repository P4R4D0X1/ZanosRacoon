#include "map.h"
#include <time.h>

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

void mapGenerator() {
	int l_i, l_j, l_k;
	int l_type, l_allowedAmount, l_sort;
	int **l_map, *l_allowedCase;

	l_allowedCase = calloc(17, sizeof(int));

	l_map = malloc(sizeof(int*) * 10);
	for (l_i = 0; l_i < 10; ++l_i) {
		l_map[l_i] = calloc(10, sizeof(int));
	}

	for (l_i = 0; l_i < 10; ++l_i) {
		for (l_j = 0; l_j < 10; ++l_j) {
			l_map[l_i][l_j] = -1;

			if(l_i == 0 || l_j == 0)
				l_map[l_i][l_j] = 2;
		}
	}

	l_map[9][3] = 14;
	l_map[0][7] = 16;

	for (l_i = 1; l_i < 9; ++l_i) {
		for (l_j = 1; l_j < 9; ++l_j) {
			
			for (l_k = 0; l_k < 17; ++l_k)
				l_allowedCase[l_k] = 1;

			l_allowedCase[0] = 0;
			l_allowedAmount = 17 - 1;
			srand(time(NULL));
				
			l_type = l_map[l_i - 1][l_j];
			
			if (l_type == 2 || l_type == 3 || l_type == 7 || l_type == 10 || l_type == 11 || l_type == 13 || l_type == 14 || l_type == 15) {
				l_allowedCase[1] = 0;
				l_allowedCase[4] = 0;
				l_allowedCase[6] = 0;
				l_allowedCase[7] = 0;
				l_allowedCase[8] = 0;
				l_allowedCase[10] = 0;
				l_allowedCase[11] = 0;
				l_allowedCase[14] = 0;
				l_allowedAmount -= 8;
			}

			l_type = l_map[l_i][l_j + 1];

			if (l_type == 2 || l_type == 4 || l_type == 8 || l_type == 11 || l_type == 12 || l_type == 14 || l_type == 15 || l_type == 16) {
				l_allowedCase[1] = 0;
				l_allowedCase[3] = 0;
				l_allowedCase[5] = 0;
				l_allowedCase[7] = 0;
				l_allowedCase[11] = 0;
				l_allowedCase[12] = 0;
				l_allowedCase[15] = 0;
				l_allowedAmount -= 7;

			}

			l_type = l_map[l_i + 1][l_j];

			if (l_type == 2 || l_type == 3 || l_type == 5 || l_type == 9 || l_type == 12 || l_type == 13 || l_type == 15 || l_type == 16) {
				l_allowedCase[1] = 0;
				l_allowedCase[4] = 0;
				l_allowedCase[5] = 0;
				l_allowedCase[6] = 0;
				l_allowedCase[8] = 0;
				l_allowedCase[10] = 0;
				l_allowedCase[11] = 0;
				l_allowedCase[14] = 0;
				l_allowedAmount -= 8;

			}

			l_type = l_map[l_i][l_j-1];

			if (l_type == 2 || l_type == 4 || l_type == 6 || l_type == 9 || l_type == 10 || l_type == 13 || l_type == 14 || l_type == 16) {
				l_allowedCase[1] = 0;
				l_allowedCase[3] = 0;
				l_allowedCase[5] = 0;
				l_allowedCase[6] = 0;
				l_allowedCase[7] = 0;
				l_allowedCase[9] = 0;
				l_allowedCase[10] = 0;
				l_allowedCase[13] = 0;
				l_allowedAmount -= 8;
			}

			l_sort = rand() % l_allowedAmount;
			for (l_k = 0; l_k < 17; ++l_k) {
				if (l_allowedCase[l_k] == 1) {
					l_allowedAmount--;
				}
				if (l_allowedAmount == 0) {
					l_map[l_i][l_j] = l_k;
				}
			}
		}
	}



}