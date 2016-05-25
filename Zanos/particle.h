#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "definition.h"
#include "metric.h"
#include "graphx.h"

#include "include\SDL2\SDL.h"

typedef struct s_particle {
	int lifeTime;

	SDL_Rect position;
	SDL_Rect velocity;
}sParticle;

typedef struct s_particleSystem {
	int lifeTime;
	int particleAmount;
	int particleAliveAmount;
	bool alive;
	sParticle **particle;

	SDL_Rect position;
}sParticleSystem;

int initParticleSystem(sParticleSystem *p_particleSystem, int p_lifeTime, int p_particleAmount, SDL_Rect p_position);
int initParticle(sParticleSystem *p_particleSystem, sParticle **p_particle);
int updateParticle(sParticleSystem *p_particleSystem, sInterface *p_interface);

#endif