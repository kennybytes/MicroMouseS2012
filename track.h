/*
 *
 *
 * File Name:	track.h
 * Author:	Kenny Luong
 *
 * Description:
 *	The track function library contains all of the necessary
 *	functions that are related to tracking the mouse. Tracking
 *	is necessary to keep the mouse from hitting the walls.
 *
 */



#define OFFSETRIGHT 0
#define OFFSETLEFT 0
#define OPTIMAL 180

#include "motors.h"
#include "atod.h"
int track(int steps);
void correct(int *totalerror);


