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
			
			/* 	If there is a hole on the right */
			if( (front > 170) && (right < 150) && (left > 120) )
			{	
				int i;
				Delay10KTCYx(100);
				left = FetchSensor(LEFTSENSOR);
				totalerror = 0 ;

				while(front < 500)
				{
					front = FetchSensor(FRONTSENSOR);
					forward(1,1,1);
				}

				turnright(82);
				track(3);
				correct(&totalerror);
				break;
			}

			/* Just keep tracking forward */
			totalerror+=track(1);
			correct(&totalerror);
			break;
		}
			

		/*	If at a dead end */
		if( (front > 500) && (right > 150) && (left > 150) )
		{
			Delay10KTCYx(100);
			/* Turn Around */
			forward(15,1,1);
			turnright(163);
			totalerror+=track(2);
			correct(&totalerror);
			break;

		}


		/*	If there is an opening on the left */
		if( (front < 700) && (right > 160) && (left < 80) )
		{	
			int i;
			Delay10KTCYx(100);
			right = FetchSensor(RIGHTSENSOR);
			
			/* if the front is far away */
			if( front < 80 )
			{
				/* NO Tracking */
				forward(220,1,1);
			}

			/* If the front is closer */
			else
			{
				Delay10KTCYx(100);

				/* wait for the front wall to turn */
				while(front < 500)
				{
					front = FetchSensor(FRONTSENSOR);

					/* If the right wall is there track off it*/
					if(right > 150)
					{
						right = FetchSensor(RIGHTSENSOR);
						totalerror+=track(1);
						correct(&totalerror);
					}
					else
					{
						forward(1,1,1);
					}
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
			while(left < 180)
			{
				forward(1,1,1);
				left = FetchSensor(RIGHTSENSOR);
			}
			//forward(200,1,1);
			turnleft(78);
			break;
		}


	}
}

}
