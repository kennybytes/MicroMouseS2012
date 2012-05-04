#include <p18f4620.h>

#define REPEAT 5
#define DELAY 20
#define DELAYTURN 25
#define TURNRIGHT 95
#define TURNLEFT 95

#include <delays.h>
#include "atod.h"
#include "motors.h"
#include "track.h"
void main(void)
{
	int front, left, right;
	int totalerror = 0;

	// Set inputs and outputs
	
	TRISA = 0x00;		// left motor
	TRISB = 0b11111111;	// Analog inputs (set all as input)
	TRISC = 0x00;		// right motor
	TRISD = 0x00;

	//TRISE = 0x00;
	PORTD = 0b00000001;
	

	front = FetchSensor(FRONTSENSOR);
	
	FetchAllSensors(&left, &front, &right);

	/* Wait for sign to start */
	while(1)
	{
		if(front > 300)
		{
			Delay10KTCYx(1000);
			break;
		}
		front = FetchSensor(FRONTSENSOR);

	}


	/* Main Program loop */
	while(1) 
	{	

		FetchAllSensors(&left, &front, &right);
	
		/*	if the front is clear and sides are blocked */
		if( (front <= 600)  && (right > 130) && (left > 130) ){
			
			/* Just keep tracking forward */
			totalerror+=track(1);
			correct(&totalerror);
		}
			
		/*	If at a dead end */
		if( (front > 400) && (right > 100) && (left > 100) )
		{
			/* Turn Around */
			track(40);
			turnright(160);
		}


		/*	If there is an opening on the left */
		if( (front < 700) && (right > 90) && (left < 90) )
		{	
			int i;
			Delay10KTCYx(100);
			right = FetchSensor(RIGHTSENSOR);
			/* Track off right wall for a bit */
			totalerror = 0;

			/*
			for(i = 0; i < 200 ; i ++){
				left = FetchSensor(LEFTSENSOR);
				if(left > 200) break;
				totalerror=trackleft(1, right-25);
				correct(&totalerror);
			}
			*/

			/* NO Tracking */
			forward(220,1,1);
			turnleft(75);
			forward(5,1,1);
		}
		
		FetchAllSensors(&left, &front, &right);

		/* Opening on the right */
		if( (front < 700) && (right < 160) && (left > 160) )
		{	
			int i;
			Delay10KTCYx(100);
			left = FetchSensor(LEFTSENSOR);
			totalerror = 0 ;

			for(i = 0; i < 200 ; i ++){
				right = FetchSensor(RIGHTSENSOR);
				if(right > 200) break;
				totalerror=trackright(1, left-25);
				correct(&totalerror);
			}
				
			forward(30,1,1);
			turnright(75);
			forward(10,1,1);
		}

		
		FetchAllSensors(&left, &front, &right);

		/* 	If there are no walls on both sides */
		if( (front < 600) && (right < 150) && (left < 150) ) 
		{
			
			Delay10KTCYx(50);
			Delay10KTCYx(50);
			while(front <400)
			{	front =FetchSensor(FRONTSENSOR);
				forward(1,1,1);
			}

			turnleft(75);
		}


			

	}


}
