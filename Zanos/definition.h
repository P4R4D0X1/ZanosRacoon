#ifndef DEFINITION_H
#define DEFINITION_H

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

#define CASE_LINE_AMOUNT 10
#define CASE_COLUMN_AMOUNT 10
#define CASE_TYPE_AMOUNT 17

#define SDL_ANIMATION_FRAMETIME 5
#define SDL_ANIMATION_SLIDE_FRAMEAMOUNT 10

#define PARTICLE_LIFETIME_MAX 10
#define PARTICLE_LIFETIME_MIN 5
#define PATRICLE_SYSTEM_LIFETIME 10
#define PARTICLE_AMOUNT 200

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