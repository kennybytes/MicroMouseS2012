/*
 *
 * File Name:	motors.h
 * Author:	Kenny Luong
 *
 * Description: 
 * 	This file contains the motor definitions for the different
 * 	motor functions that we need for our mouse. These are all
 * 	and any functions that have access to the motor.
 *
 */

#define YELLOW 0x08
#define GREEN 0x04
#define BLUE 0x02
#define RED 0x01

void forward(int times, int pulse_right, int pulse_left);
int next_pulse(int current);
int last_pulse(int current);
void turnright(int steps);
void turnleft(int steps);




