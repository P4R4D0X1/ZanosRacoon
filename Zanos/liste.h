#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"

typedef struct s_sList {
	sPosition position;

	struct s_sList *next;
}sList;

void printList(sList *p_pRoot);
int createListNode(sList **p_ppListNode, sPosition p_position);
int freeList(sList **p_ppRoot);	
int addFirst(sList **p_ppRoot, sPosition p_position);
int addFirstPTR(sList **p_ppRoot, sList *p_listNode);
int addLast(sList **p_ppRoot, sPosition p_position);
int addLastPTR(sList **p_ppRoot, sList *p_listNode);
int listLength(sList *p_pRoot);
int at(sList *p_pRoot, int p_index, sList **p_ppOutput);
int get(sList **p_ppRoot, int p_index, sList **p_ppOutput);
int pop(sList **p_ppRoot, sList **p_ppOutput);

#endif