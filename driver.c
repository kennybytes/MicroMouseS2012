#include <p18f4620.h>

#define OFFSETRIGHT 0
#define OFFSETLEFT 0
#define REPEAT 5
#define DELAY 1
#define DELAYTURN 25
#define TURNRIGHT 95
#define TURNLEFT 95
#define OPTIMAL 200

#include <delays.h>

#include "atod.h"

void main(void)
{
	int front, left, right;
	// Set inputs and outputs
	
	TRISA = 0x00;		// left motor
	TRISB = 0b11111111;	// Analog inputs (set all as input)
	TRISC = 0x00;		// right motor
	TRISD = 0x00;

	//TRISE = 0x00;
	//PORTD = 0b00000001;
	

		InitAD(MIDDLESENSOR);
		front = ConvertAD();
		

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

