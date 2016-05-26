#include "graphx.h"
#include "particle.h"


int initParticleSystem(sParticleSystem **p_particleSystem, int p_lifeTime, int p_particleAmount, SDL_Rect p_position){
	int l_i;
	
	srand((unsigned int)time(NULL));

	(*p_particleSystem) = malloc(sizeof(sParticleSystem));

	(*p_particleSystem)->lifeTime = p_lifeTime;
	(*p_particleSystem)->particleAmount = p_particleAmount;
	(*p_particleSystem)->particleAliveAmount = p_particleAmount;
	(*p_particleSystem)->alive = TRUE;
	(*p_particleSystem)->position = p_position;

	(*p_particleSystem)->particle = malloc(sizeof(sParticle*) * p_particleAmount);

	for (l_i = 0; l_i < (*p_particleSystem)->particleAmount; ++l_i) {
		initParticle(&((*p_particleSystem)->particle[l_i]), p_position);
	}

	return 0;
}

int initParticle(sParticle **p_particle, SDL_Rect p_position) {
	(*p_particle) = malloc(sizeof(sParticle));

	(*p_particle)->lifeTime = (rand() % (PARTICLE_LIFETIME_MAX - PARTICLE_LIFETIME_MIN)) + PARTICLE_LIFETIME_MIN;
	(*p_particle)->position = p_position;
	(*p_particle)->position.h = WINDOW_HEIGHT / CASE_LINE_AMOUNT;
	(*p_particle)->position.w = WINDOW_WIDTH / CASE_COLUMN_AMOUNT;
	(*p_particle)->velocity.x = (rand() % 10) - 5;
	(*p_particle)->velocity.y = (rand() % 10) - 5;
	return 0;
}

int updateParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface) {
	int l_i;

	if ((*p_particleSystem)) {
		for (l_i = 0; l_i < (*p_particleSystem)->particleAmount; ++l_i) {
			if ((*p_particleSystem)->particle[l_i]) {
				//SDL_RenderDrawPoint(p_interface->renderer, (*p_particleSystem)->particle[l_i]->position.x, (*p_particleSystem)->particle[l_i]->position.y);				
				SDL_RenderCopy(p_interface->renderer, p_interface->effect.particleSprite, NULL, &((*p_particleSystem)->particle[l_i]->position));
				//on update la particule
				(*p_particleSystem)->particle[l_i]->position.x += (*p_particleSystem)->particle[l_i]->velocity.x;
				(*p_particleSystem)->particle[l_i]->position.y += (*p_particleSystem)->particle[l_i]->velocity.y;
				//On baisse son temps de vie
				(*p_particleSystem)->particle[l_i]->lifeTime--;
				//si il est nul et que le system est en vie on reinit la particule sinon on la tue
				if ((*p_particleSystem)->particle[l_i]->lifeTime == 0) {
					if ((*p_particleSystem)->alive && PARTICLE_LOOP) {
						free((*p_particleSystem)->particle[l_i]);
						initParticle(&((*p_particleSystem)->particle[l_i]), (*p_particleSystem)->position);
						(*p_particleSystem)->lifeTime--;
					} else {
						(*p_particleSystem)->particleAliveAmount--;
						free((*p_particleSystem)->particle[l_i]);
					}
				}
			}
		}
	}else {
		return 0;
	}

	if ((*p_particleSystem)->lifeTime <= 0) {
		(*p_particleSystem)->alive = FALSE;
	}

	if ((*p_particleSystem)->particleAliveAmount <= 0) {
		//free((*p_particleSystem)->particle);
		(*p_particleSystem)->particle = NULL;
		//free((*p_particleSystem));
		(*p_particleSystem) = NULL;
		p_particleSystem = NULL;

	}

	return 0;
}

int renderParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, sMap *p_map) {
	if ((*p_particleSystem)) 
		updateParticle(p_particleSystem, p_interface);
	return 0;
}