/**
* \file particle.c
* \brief Programme de systeme de particules
* \date 27 mai 2016
*
* Programme qui initialise et realise le rendu des particules
*
*/
#include "graphx.h"
#include "particle.h"

/**
* \fn int initParticleSystem(sParticleSystem **p_particleSystem, int p_lifeTime, int p_particleAmount, SDL_Rect p_position, eDirection p_direction)
* \brief Fonction d'initialisation de systeme de particule
*
* \param **p_particleSystem system de particule
* \param p_lifeTime temps de vie du système de particule
* \param p_particleAmount nombre de particule du systeme de particule
* \param p_position position du sytème de particule
* \param p_direction direction de propagation des particules
* \return int représentant le déroulement de la fonction
*/
int initParticleSystem(sParticleSystem **p_particleSystem, int p_lifeTime, int p_particleAmount, SDL_Rect p_position, eDirection p_direction) {
	int l_i;
	
	srand((unsigned int)time(NULL));

	(*p_particleSystem) = malloc(sizeof(sParticleSystem));

	(*p_particleSystem)->lifeTime = p_lifeTime;
	(*p_particleSystem)->particleAmount = p_particleAmount;
	(*p_particleSystem)->particleAliveAmount = p_particleAmount;
	(*p_particleSystem)->direction = p_direction;
	(*p_particleSystem)->alive = TRUE;
	(*p_particleSystem)->position = p_position;

	(*p_particleSystem)->particle = malloc(sizeof(sParticle*) * p_particleAmount);

	for (l_i = 0; l_i < (*p_particleSystem)->particleAmount; ++l_i) {
		initParticle(&((*p_particleSystem)->particle[l_i]), p_position, p_direction);
	}

	return 0;
}

/**
* \fn int initParticle(sParticle **p_particle, SDL_Rect p_position, eDirection p_direction)
* \brief Fonction d'initialisation de particule
*
* \param **p_particle particule
* \param p_position position du sytème de particule
* \param p_direction direction de propagation de la particule
* \return int représentant le déroulement de la fonction
*/
int initParticle(sParticle **p_particle, SDL_Rect p_position, eDirection p_direction) {
	(*p_particle) = malloc(sizeof(sParticle));

	(*p_particle)->lifeTime = (rand() % (PARTICLE_LIFETIME_MAX - PARTICLE_LIFETIME_MIN)) + PARTICLE_LIFETIME_MIN;
	(*p_particle)->position = p_position;
	(*p_particle)->position.h = WINDOW_HEIGHT / CASE_LINE_AMOUNT;
	(*p_particle)->position.w = WINDOW_WIDTH / CASE_COLUMN_AMOUNT;

	switch (p_direction) {
		case(DUP):
			(*p_particle)->velocity.x = ((float)((rand() % 100) - 50) / 10);
			(*p_particle)->velocity.y = ((float)((rand() % 50) - 50) / 10);
			break;
		case(DRIGHT):
			(*p_particle)->velocity.x = ((float)((rand() % 50)) / 10);
			(*p_particle)->velocity.y = ((float)((rand() % 100) - 50) / 10);
			break;
		case(DDOWN):
			(*p_particle)->velocity.x = ((float)((rand() % 100) - 50) / 10);
			(*p_particle)->velocity.y = ((float)((rand() % 50)) / 10);
			break;
		case(DLEFT):
			(*p_particle)->velocity.x = ((float)((rand() % 50) - 50) / 10);
			(*p_particle)->velocity.y = ((float)((rand() % 100) - 50) / 10);
			break;
		default:
			(*p_particle)->velocity.x = ((float)((rand() % 100)-50)/10);
			(*p_particle)->velocity.y = ((float)((rand() % 100)-50)/10);
			break;
	}

	return 0;
}

/**
* \fn int updateParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, bool p_followPlayer)
* \brief Fonction de mise à jour du système de particule
*
* \param **p_particleSystem system de particule
* \param *p_interface interface de l'enigme
* \param p_followPlayer vaut 1 si les particules doivent suivre le joueur, 0 sinon
* \return int représentant le déroulement de la fonction
*/
int updateParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, bool p_followPlayer) {
	int l_i;

	if ((*p_particleSystem)) {
		for (l_i = 0; l_i < (*p_particleSystem)->particleAmount; ++l_i) {
			if ((*p_particleSystem)->particle[l_i]) {
				SDL_RenderCopy(p_interface->renderer, p_interface->effect.particleSprite[2], NULL, &((*p_particleSystem)->particle[l_i]->position));
				//on update la particule
				(*p_particleSystem)->particle[l_i]->position.x += (int)(*p_particleSystem)->particle[l_i]->velocity.x;
				(*p_particleSystem)->particle[l_i]->position.y += (int)(*p_particleSystem)->particle[l_i]->velocity.y;
				//On baisse son temps de vie
				(*p_particleSystem)->particle[l_i]->lifeTime--;
				//si il est nul et que le system est en vie on reinit la particule sinon on la tue
				if ((*p_particleSystem)->particle[l_i]->lifeTime == 0) {
					if ((*p_particleSystem)->alive && PARTICLE_LOOP) {
						free((*p_particleSystem)->particle[l_i]);
						if (p_followPlayer) {
							initParticle(&((*p_particleSystem)->particle[l_i]), p_interface->player.realPosition, (*p_particleSystem)->direction);
						}else{
							initParticle(&((*p_particleSystem)->particle[l_i]), (*p_particleSystem)->position, (*p_particleSystem)->direction);
						}
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
		free((*p_particleSystem));
		(*p_particleSystem) = NULL;
		p_particleSystem = NULL;

	}

	return 0;
}

/**
* \fn int renderParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, sMap *p_map, bool p_followPlayer)
* \brief Fonction de rendu des particules
*
* \param **p_particleSystem system de particule
* \param *p_interface interface de l'enigme
* \param *p_map map de l'enigme
* \param p_followPlayer vaut 1 si les particules doivent suivre le joueur, 0 sinon
* \return int représentant le déroulement de la fonction
*/
int renderParticle(sParticleSystem **p_particleSystem, struct s_interface *p_interface, sMap *p_map, bool p_followPlayer) {
	if ((*p_particleSystem)) 
		updateParticle(p_particleSystem, p_interface, p_followPlayer);
	return 0;
}