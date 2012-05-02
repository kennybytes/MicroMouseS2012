/*
 *
 * File Name:	Motors.c
 * Author: 	Kenny Luong
 *
 * Description:
 * 	Contains the function definitions for the 
 * 	motors library.
 *
 *
 */


#ifndef MOTORS
#define MOTORS

#include "motors.h"

int current_pulse_right = RED;
int current_pulse_left = RED;
/*
 *
 *
 * Linear Movement
 *
 *
 */

void forward(int times, int pulse_right, int pulse_left)
{		
		
		int i;
		int old_pulse =0;

		for(i=0;i<times;i++)
		{	
			if(pulse_right)
			{
			current_pulse_right = next_pulse(current_pulse_right);
			PORTA = current_pulse_right;
			}

			if(pulse_left)
			{
			current_pulse_left = next_pulse(current_pulse_left);
			PORTC = current_pulse_left;
			}

			Delay100TCYx(STEPDELAY);
		}

}

/*
 *
 *
 * Step Trackers
 *
 *
 */

// This function returns the NEXT step in the sequence where
// 	the motor should pulse.
//
//
int next_pulse(int current)
{

	switch(current)
	{
		case RED:
			return YELLOW;
		case YELLOW:
			return GREEN;
		case GREEN:
			return BLUE;
		case BLUE:
			return RED;
		default: 	
			break;
	}

}

// This function return the previous step value where the
// 	motor pulsed before.
//
//
int last_pulse(int current)
{
	switch(current)
	{
		case RED:
			return BLUE;
		case YELLOW:
			return RED;
		case GREEN:
			return YELLOW;
		case BLUE:
			return GREEN;
		default:
			break;
	}
}




/*
 *
 *
 *	Turning Functions
 *
 */



void turnright(int steps)
{	
	int i;
	for( i = 0 ; i < steps; i++)
	{

		current_pulse_right = last_pulse(current_pulse_right);
		PORTA = current_pulse_right;
		
		current_pulse_left = next_pulse(current_pulse_left);
		PORTC = current_pulse_left;

		Delay100TCYx(STEPDELAY);
	}
}


void turnleft(int steps)
{	
	int i;
	for( i = 0 ; i < steps; i++)
	{
		current_pulse_left = last_pulse(current_pulse_left);
		PORTC = current_pulse_left;

		current_pulse_right = next_pulse(current_pulse_right);
		PORTA = current_pulse_right;

		Delay100TCYx(STEPDELAY);

	}
}

#endif
