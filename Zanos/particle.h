/**
* \file particle.h
* \brief Header des fonctions de systeme de particules
* \date 27 mai 2016
*
* Header qui contient les definitions des fonctions d'initialisation et de rendu de syteme de particules
*
*/
#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "definition.h"
#include "metric.h"
#include "map.h"

#include "include\SDL2\SDL.h"

/**
* \struct sParticle
* \brief Structure qui représente une particule
*/
typedef struct s_particle {
	int lifeTime;

	SDL_Rect position;
	sVelocity velocity;
}sParticle;

/**
* \struct sParticleSystem
* \brief Structure qui représente un systeme de particules
*/
typedef struct s_particleSystem {
	int lifeTime;
	int particleAmount;
	int particleAliveAmount;
	eDirection direction;
	bool alive;

	sParticle **particle;
	SDL_Rect position;
}sParticleSystem;

int initParticleSystem(sParticleSystem **p_particleSystem, int p_lifeTime, int p_particleAmount, SDL_Rect p_position, eDirection p_direction);
int initParticle(sParticle **p_particle, SDL_Rect p_position, eDirection p_direction);
int updateParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, bool p_followPlayer);
int renderParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, sMap *p_map, bool p_followPlayer);

#endif