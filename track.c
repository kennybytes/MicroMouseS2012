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
  		//Delay1KTCYx(10);
	  	InitAD(RIGHTSENSOR);
 	  	right = ConvertAD() + OFFSETRIGHT;

		/*
	  	if(right<OPTIMAL)
			right=200;
		*/

	  	InitAD(LEFTSENSOR);
	  	left = ConvertAD() + OFFSETLEFT;
		
		/*
	  	if(left<OPTIMAL) left=200;
		*/
		error = (right - left);
	 	sum = sum + error;

	  	forward(1,1,1);
	 
	}

	// Divide our error by 5 (how many steps we took)
	sum = sum/steps;
			
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

