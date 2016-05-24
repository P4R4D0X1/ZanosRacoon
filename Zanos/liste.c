#include "liste.h"

void printList(sList *p_pRoot) {
	if (!p_pRoot) {
		printf("\n");
		return;
	}

	printf("(%d,%d) ", (int)(p_pRoot->position.x), (int)(p_pRoot->position.y));
	printList((sList*)(p_pRoot->next));
}

int createListNode(sList **p_ppListNode, sPosition p_position) {
	*p_ppListNode = malloc(sizeof(sList));

	if (!*p_ppListNode)
		return 666;

	(*p_ppListNode)->position = p_position;
	(*p_ppListNode)->next = NULL;

	return 0;
}

int freeList(sList **p_ppRoot) {
	if (!*p_ppRoot)
		return 0;

	freeList(&((*p_ppRoot)->next));
	free(*p_ppRoot);

	if (*p_ppRoot) 
		return 666;

	p_ppRoot = NULL;

	return 0;
}

int addFirst(sList **p_ppRoot, sPosition p_position) {
	sList *l_node;

	if (createListNode(&l_node, p_position))
		return 666;
	
	(sList*)(l_node->next) = *p_ppRoot;
	*p_ppRoot = l_node;

	return 0;
}

int addLast(sList **p_ppRoot, sPosition p_position) {
	sList *l_lastNode = *p_ppRoot, *l_newNode = NULL;

	if (!*p_ppRoot) {
		if (createListNode(p_ppRoot, p_position))
			return 666;
		return 0;
	}
	

	while ((l_lastNode->next)) {
		l_lastNode = (sList*)(l_lastNode->next);
	}

	if (createListNode(&l_newNode, p_position))
		return 666;

	(sList*)(l_lastNode->next) = l_newNode;

	return 0;
}

int listLength(sList *p_pRoot) {
	int l_length = 0;

	while (p_pRoot) {
		++l_length;
		p_pRoot = (sList*)(p_pRoot->next);
	}

	return l_length;
}

int at(sList *p_pRoot, int p_index, sList **p_ppOutput) {
	int l_index = 0;

	if (!p_pRoot || p_index >= listLength(p_pRoot)) {
		return 666;
	}

	*p_ppOutput = p_pRoot;

	while (l_index < p_index) {
		++l_index;
		*p_ppOutput = (sList*)((*p_ppOutput)->next);
	}

	return 0;
}

int get(sList **p_ppRoot, int p_index, sList **p_ppOutput) {
	sList *l_node;

	if (!p_index) {
		if (pop(p_ppRoot, p_ppOutput))
			return 666;
		return 0;
	}

	if (at(*p_ppRoot, p_index - 1, &l_node) || at(*p_ppRoot, p_index, p_ppOutput))
		return 666;
	
	l_node->next = (*p_ppOutput)->next;
	(*p_ppOutput)->next = NULL;

	return 0;
}

int pop(sList **p_ppRoot, sList **p_ppOutput) {
	*p_ppOutput = *p_ppRoot;

	if (!*p_ppOutput)
		return 666;

	*p_ppRoot = (sList*)((*p_ppRoot)->next);
	(*p_ppOutput)->next = NULL;
	
	return 0;
}
