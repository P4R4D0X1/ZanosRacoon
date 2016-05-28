/**
* \file definition.h
* \brief Header qui contient les definitions et enumerations du programme
* \date 27 mai 2016
*
* Header qui contient les definitions et enumerations du programme
*
*/
#ifndef DEFINITION_H
#define DEFINITION_H

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 700

#define CASE_LINE_AMOUNT 10
#define CASE_COLUMN_AMOUNT 10
#define CASE_TYPE_AMOUNT 17

#define SDL_ANIMATION_FRAMETIME 10
#define SDL_ANIMATION_SLIDE_FRAMEAMOUNT 10

#define PARTICLE_LIFETIME_MAX 10
#define PARTICLE_LIFETIME_MIN 5
#define PATRICLE_SYSTEM_LIFETIME 1
#define PARTICLE_AMOUNT 50
#define PARTICLE_LOOP 0

/**
* \enum eCase_type
* \brief Représentation des différents types de case
*/
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

/**
* \enum bool
* \brief Représentation des booléens
*/
typedef enum e_bool {
	FALSE,
	TRUE
}bool;

/**
* \enum eDirection
* \brief Représentation des directions
*/
typedef enum e_direction {
	DUP,
	DRIGHT,
	DDOWN,
	DLEFT
}eDirection;

#endif