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
	// Set inputs and outputs
	
	TRISA = 0x00;		// left motor
	TRISB = 0b11111111;	// Analog inputs (set all as input)
	TRISC = 0x00;		// right motor
	TRISD = 0x00;

	//TRISE = 0x00;
	PORTD = 0b00000001;

	InitAD(MIDDLESENSOR);
	front = ConvertAD();
		
	while(1)
	{
		forward(1,1,1);
	}

	while(1) 
	{	

		if( front < 250 ) 
			track();
			
		else
		{
			forward(150,1,1);
			turnright(TURNRIGHT);
		}


		InitAD(MIDDLESENSOR);
		front = ConvertAD();
	}


}
