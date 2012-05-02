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
		if( (front <= 600)  && (right > 100) && (left > 100) ){
			
			/* Just keep tracking forward */
			totalerror+=track(20);
			correct(&totalerror);
		}
			
		/*	If at a dead end */
		if( (front > 400) && (right > 100) && (left > 100) )
		{
			/* Turn Around */
			track(40);
			turnright(150);
		}
		


		/*	If there is an opening on the left */
		if( (front < 700) && (right > 90) && (left < 90) )
		{	
			int i;
			Delay10KTCYx(100);
			right = FetchSensor(RIGHTSENSOR);
			/* Track off right wall for a bit */
			for(i = 0; i < 100 ; i ++){
				totalerror=trackleft(1, right-25);
				correct(&totalerror);
			}

			/* NO Tracking */
			while(front < 700)
			{
				front = FetchSensor(FRONTSENSOR);
				forward(1,1,1);
			}

			turnleft(80);
		}
		
		/* 	If there is an opening on the right */	
		if( (front < 700) && (right < 150) && (left > 150) )
		{	
			int i;
			left = FetchSensor(LEFTSENSOR);

			for(i = 0; i< 50 ; i++){
				totalerror=trackleft(1, left);
				correct(&totalerror);
			}

			while(front < 700)
			{
				front = FetchSensor(FRONTSENSOR);
				forward(1,1,1);
			}

			turnright(80);
		}

		FetchAllSensors(&left, &front, &right);


	}


}
