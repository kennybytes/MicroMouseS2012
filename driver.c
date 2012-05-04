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

while(1)
{

	/* Main Program loop */
	while(1) 
	{	

		FetchAllSensors(&left, &front, &right);

		/*	if the front is clear and sides are blocked */
		if( (front <= 400)  && (left > 130) ){
			
			if( (front > 100) && (right < 170) && (left > 100) )
			{	
				int i;
				Delay10KTCYx(100);
				left = FetchSensor(LEFTSENSOR);
				totalerror = 0 ;
					
				forward(210,1,1);
				turnright(75);
				forward(5,1,1);

				break;
			}
			/* Just keep tracking forward */
			totalerror+=track(1);
			correct(&totalerror);
			break;
		}
			

		/* Opening on the right */


		/*	If at a dead end */
		if( (front > 300) && (right > 150) && (left > 150) )
		{
			
			Delay10KTCYx(100);
			/* Turn Around */
			forward(15,1,1);
			turnright(155);
			totalerror+=track(2);
			break;
		}


		/*	If there is an opening on the left */
		if( (front < 700) && (right > 90) && (left < 90) )
		{	
			int i;
			Delay10KTCYx(100);
			right = FetchSensor(RIGHTSENSOR);
			if( front < 80 )
			{
				/* NO Tracking */
				forward(200,1,1);
			}
			else
			{
				Delay10KTCYx(100);
				while(front < 500)
				{
				front = FetchSensor(FRONTSENSOR);
				forward(1,1,1);
				}
			}
				
			turnleft(78);
			forward(5,1,1);
			
			break;
		}


		/* 	If there are no walls on both sides */
		if( (front < 600) && (right < 150) && (left < 150) ) 
		{
			
			Delay10KTCYx(50);
			forward(200,1,1);
			turnleft(78);
			break;
		}


	}
}

}
