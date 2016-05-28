/**
* \file metric.h
* \brief Header qui contient les structures metrics
* \date 27 mai 2016
*
* Header qui contient les definitions des structures metrics
*
*/
#ifndef METRIC_H
#define METRIC_H

#include <stdlib.h>
#include <stdio.h>

/**
* \struct sPosition
* \brief Structure qui représente une position 
*/
typedef struct s_position {
	int x;
	int y;
}sPosition;

/**
* \struct sDimension
* \brief Structure qui représente une dimension
*/
typedef struct s_dimension{
	int height;
	int width;
}sDimension;

/**
* \struct sVelocity
* \brief Structure qui représente une velocité
*/
typedef struct s_velocity {
	float x;
	float y;
}sVelocity;

#endif