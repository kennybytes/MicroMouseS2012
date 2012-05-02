/*
 *
 * File name:	track.c
 * Author: 	Kenny Luong
 *
 * Description:
 * 	This file contains the function definitions for the tracking
 * 	library that is used for the BK Micromouse
 *
 */
#include "track.h"
int track(int steps)
{
	int sum = 0;
	int i = 0;
	int right = 0;
	int left = 0;
	int front= 0;
	
	int error = 0;


	/* 	step without tracking 	*/

	for(i=0;i<steps;i++)
	{
 	  	right = FetchSensor(RIGHTSENSOR) + OFFSETRIGHT;

	  	if(right<OPTIMAL)
			right=OPTIMAL;

	  	left = FetchSensor(LEFTSENSOR) + OFFSETLEFT;
		
	  	if(left<OPTIMAL) left=OPTIMAL;
		error = (right - left);
	 	sum = sum + error;

	  	forward(1,1,1);
	 
	}

	// Divide our error by 5 (how many steps we took)
	sum = sum/steps;
			
	return sum;

}

int trackright(int steps, int optimal)
{
	int i;
	int right = 0;
	int left = 0;
	int error = 0;
	int sum = 0;
	for(i = 0; i < steps ; i++)
	{
		right = optimal;
		left = FetchSensor(LEFTSENSOR);
		error = (right - left);
		sum += error;
		forward(1,1,1);
	}

	return sum;

}
int trackleft(int steps,	int optimal)
{
	int i;
	int right = 0;
	int left = 0;
	int error = 0;
	int sum = 0;
	for(i = 0; i < steps ; i++)
	{
		left = optimal;
		right = FetchSensor(RIGHTSENSOR);
		error = (right - left);
		sum += error;
		forward(1,1,1);
	}

	return sum;
}


void correct(int *totalerror)
{


	/* 	Actually Correct Here	*/
	// if mouse is tilted towards right
	if( (*totalerror) < -200 ){	
		forward(1,0,1);
		(*totalerror) += 200;
	}
					    
	// if mouse is tilted towards left
	if((*totalerror) > 150 ){
		forward(1,1,0);
		(*totalerror) -= 200;
	}


}

