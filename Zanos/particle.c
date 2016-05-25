#include "particle.h"

int initParticleSystem(sParticleSystem *p_particleSystem, int p_lifeTime, int p_particleAmount, SDL_Rect p_position){
	int l_i;
	
	srand(time(NULL));

	p_particleSystem = malloc(sizeof(sParticleSystem));

	p_particleSystem->lifeTime = p_lifeTime;
	p_particleSystem->particleAmount = p_particleAmount;
	p_particleSystem->particleAliveAmount = p_particleAmount;
	p_particleSystem->alive = TRUE;
	p_particleSystem->position = p_position;

	p_particleSystem->particle = malloc(sizeof(sParticle*) * p_particleAmount);

	for (l_i = 0; l_i < p_particleSystem->particleAmount; ++l_i) {
		initParticle(p_particleSystem, p_particleSystem->particle[l_i]);
	}

	return 0;
}

int initParticle(sParticleSystem *p_particleSystem, sParticle **p_particle) {
	p_particle = malloc(sizeof(sParticle));

	(*p_particle)->lifeTime = (rand() % (PARTICLE_LIFETIME_MAX - PARTICLE_LIFETIME_MIN)) + PARTICLE_LIFETIME_MIN;
	(*p_particle)->position = p_particleSystem->position;
	(*p_particle)->velocity.x = (rand() % 2) - 1;
	(*p_particle)->velocity.y = (rand() % 2) - 1;
	return 0;
}

int updateParticle(sParticleSystem *p_particleSystem, sInterface *p_interface) {
	int l_i;

	if (p_particleSystem->alive) {
		for (l_i = 0; l_i < p_particleSystem->particleAmount; ++l_i) {
			if (p_particleSystem->particle[l_i]) {
				SDL_RenderDrawPoint(p_interface->renderer, p_particleSystem->particle[l_i]->position.x, p_particleSystem->particle[l_i]->position.y);
				//on update la particule
				p_particleSystem->particle[l_i]->position.x += p_particleSystem->particle[l_i]->velocity.x;
				p_particleSystem->particle[l_i]->position.x += p_particleSystem->particle[l_i]->velocity.y;
				//On baisse son temps de vie
				p_particleSystem->particle[l_i]->lifeTime--;
				//si il est nul et que le system est en vie on reinit la particule sinon on la tue
				if (p_particleSystem->particle[l_i]->lifeTime == 0) {
					if (p_particleSystem->alive) {
						free(p_particleSystem->particle[l_i]);
						initParticle(p_particleSystem, &(p_particleSystem->particle[l_i]));
						p_particleSystem->lifeTime--;
					}
					else {
						p_particleSystem->particleAliveAmount--;
						free(p_particleSystem->particle[l_i]);
					}
				}
			}
		}
	}

	if (p_particleSystem->particleAliveAmount == 0)
		p_particleSystem->alive = FALSE;

	return 0;
}