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
void track( void )
{	
	int sum = 0;
	int i = 0;
	int right = 0;
	int left = 0;
	int front= 0;
	
	int error = 0;

	// Move Forward and Track
	for(i=0;i<5;i++)
	{
  		Delay1KTCYx(10);
	  	InitAD(RIGHTSENSOR);
 	  	right = ConvertAD() + OFFSETRIGHT;
	  	if(right<OPTIMAL)
			right=200;

	  	InitAD(LEFTSENSOR);
	  	left = ConvertAD() + OFFSETLEFT;
	  	if(left<OPTIMAL) left=200;


		error = (right - left);
	 	sum = sum + error;

	  	forward(1,1,1);
	 
	}

	// Divide our error by 5 (how many steps we took)
	sum = sum/5;
			

	// if mouse is tilted towards right
	if( sum < -25 ){	
		forward(1,0,1);
		sum = sum + 25;
	}

	// if mouse is tilted towards left
	if(sum > 25 ){
		forward(1,1,0);
		sum = sum - 25;
	}


}

