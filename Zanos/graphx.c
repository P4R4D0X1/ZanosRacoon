#include "graphx.h"

int loadInterface(sInterface *p_interface) {
	p_interface = malloc(sizeof(sInterface));


}

int displayMap(sInterface *p_interface, sMap *p_map) {
	int i, j;

	for (i = 0; i < p_map->mapDimension.height; ++i) {
		for (j = 0; j < p_map->mapDimension.width; ++j) {
			p_interface->caseSprite[p_map->path[i][j].type];


		}

	}


}
