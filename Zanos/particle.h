#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "definition.h"
#include "metric.h"
#include "map.h"

#include "include\SDL2\SDL.h"


typedef struct s_particle {
	int lifeTime;

	SDL_Rect position;
	sVelocity velocity;
}sParticle;

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