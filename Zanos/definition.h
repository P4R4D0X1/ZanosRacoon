#ifndef DEFINITION_H
#define DEFINITION_H

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

#define CASE_HEIGHT 10
#define CASE_WIDTH 10
#define CASE_TYPE_AMOUNT 17

#define SDL_ANIMATION_FRAMETIME 10

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