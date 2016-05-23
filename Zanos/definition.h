#ifndef DEFINITION_H
#define DEFINITION_H

typedef enum e_caseType{
	MAGICALKIWI,
	FREE, 
	CLOSED,
	UPDOWN,
	RIGHTLEFT,
	UP,
	RIGHT,
	DOWN,
	LEFT,
	UPRIGHT,
	RIGHTDOWN,
	DOWNLEFT,
	UPLEFT,
	UPRIGHTDOWN,
	RIGHTDOWNLEFT,
	UPDOWNLEFT,
	UPRIGHTLEFT
}eCase_type;

typedef enum e_bool {
	FALSE,
	TRUE
}bool;

typedef enum e_direction {
	DUP,
	DRIGHT,
	DDOWN,
	DLEFT
}eDirection;

#endif