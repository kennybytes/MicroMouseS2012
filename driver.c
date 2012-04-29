#include <p18f4620.h>
#include <delays.h>

#include "atod.h"

#define OFFSETRIGHT 0
#define OFFSETLEFT 0

#define REPEAT 5
#define DELAY 1
#define DELAYTURN 25

#define TURNRIGHT 95
#define TURNLEFT 95

#define OPTIMAL 200

#define YELLOW 0x08
#define GREEN 0x04
#define BLUE 0x02
#define RED 0x01

void forward(int times, int pulse_right, int pulse_left);
void reverse(void);

void turnright(int steps);
void turnleft(int steps);
void track(void);

int next_pulse(int current);
int last_pulse(int current);
int current_pulse_right = RED;
int current_pulse_left = RED;


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


/*
 *
 *
 * Linear Movement
 *
 *
 */


void reverse(void) 
{
		PORTA = BLUE;
		PORTC = BLUE;
		Delay100TCYx(DELAY);
		PORTA = GREEN;
		PORTC = GREEN;
		Delay100TCYx(DELAY);
		PORTA = YELLOW;
		PORTC = YELLOW;
		Delay100TCYx(DELAY);
		PORTA = RED;
		PORTC = RED;
		Delay100TCYx(DELAY);
}






void forward(int times, int pulse_right, int pulse_left)
{		
		
		int i;
		int old_pulse =0;

		for(i=0;i<times;i++)
		{	
			if(pulse_right)
			{
			current_pulse_right = next_pulse(current_pulse_right);
			PORTC = current_pulse_right;
			Delay100TCYx(DELAY);
			}

			if(pulse_left)
			{
			current_pulse_left = next_pulse(current_pulse_left);
			PORTA = current_pulse_left;
			Delay100TCYx(DELAY);

			}
		}

		/*
		for ( i = 0 ; i < times ; i ++)
		{

		PORTA = BLUE;
		Delay100TCYx(delayleft);

		PORTC = BLUE;
		Delay100TCYx(delayright);

		PORTA = GREEN;
		Delay100TCYx(delayleft);

		PORTC = GREEN;
		Delay100TCYx(delayright);

		PORTA = YELLOW;
		Delay100TCYx(delayleft);

		PORTC = YELLOW;
		Delay100TCYx(delayright);

		PORTA = RED;
		Delay100TCYx(delayleft);

		PORTC = RED;
		Delay100TCYx(delayright);
		}
		*/

}


/*
 *
 *
 * Step Trackers
 *
 *
 */
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
		PORTC = current_pulse_right;
		
		current_pulse_left = next_pulse(current_pulse_left);
		PORTA = current_pulse_left;

		Delay1KTCYx(DELAYTURN);

		/*
		 * OUTDATED Turn
		PORTA = BLUE;
		PORTC = RED;
		Delay1KTCYx(DELAY);
		
		PORTA = GREEN;
		PORTC = YELLOW;
		Delay1KTCYx(DELAY);
		
		PORTA = YELLOW;
		PORTC = GREEN;
		Delay1KTCYx(DELAY);

		PORTA = RED;	
		PORTC = BLUE;
		Delay1KTCYx(DELAY);
		*
		*/

	}
}


void turnleft(int steps)
{	
	int i;
	for( i = 0 ; i < steps; i++)
	{

		current_pulse_left = last_pulse(current_pulse_left);
		PORTA = current_pulse_left;

		current_pulse_right = next_pulse(current_pulse_right);
		PORTC = current_pulse_right;

		Delay1KTCYx(DELAYTURN);

		/*
		PORTC = BLUE;
		PORTA = RED;
		Delay1KTCYx(DELAY);
		
		PORTC = GREEN;
		PORTA = YELLOW;
		Delay1KTCYx(DELAY);
		
		PORTC = YELLOW;
		PORTA = GREEN;
		Delay1KTCYx(DELAY);

		PORTC = RED;	
		PORTA = BLUE;
		Delay1KTCYx(DELAY);
		*/
	
	}
}
