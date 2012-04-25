#include <p18f4620.h>
#include <delays.h>

#define RIGHTSENSOR 1
#define MIDDLESENSOR 2
#define LEFTSENSOR 3
#define OFFSETRIGHT 30
#define OFFSETLEFT 0
#define REPEAT 5
#define DELAY 50
#define DELAYTURN 25
#define TURNRIGHT 83
#define TURNLEFT 83
#define OPTIMAL 481


#define YELLOW 0x01
#define GREEN 0x02
#define BLUE 0x04
#define RED 0x08


void InitAD(int sensor);
int ConvertAD(void);
void forward(int times, int pulse_right, int pulse_left);
void adjust_forward(int times);
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

	TRISA = 0x00;	// left motor
	TRISB = 0b11111111;
	TRISC = 0x00;	// right motor
	TRISD = 0x00;
	//TRISE = 0x00;
	PORTD = 0b00000001;



while(1)
{
	while(1)
	{

		InitAD(MIDDLESENSOR);
 		front = ConvertAD();

		InitAD(RIGHTSENSOR);
 		right = ConvertAD();

		InitAD(LEFTSENSOR);
 		left = ConvertAD();


		if(right<300) // check if front is greater than one square but less than two away from wall
		{
			//Delay10KTCYx(10);
			forward(20,1,1);
		}
		else
		{	
		
		}


	}




}


}

void track( void )
{	
	int sum = 0;

	int right = 0;
	int left = 0;
	int front= 0;

	while(1)
	{

		InitAD(RIGHTSENSOR);
 		right = ConvertAD() + OFFSETRIGHT;
		InitAD(LEFTSENSOR);
		left = ConvertAD() + OFFSETLEFT;
		sum = sum + (right - left);
		
		
		
		//	if motor is tilted towards right

		if( sum < 0 )
		{	
			
			forward(1,0,1) ;

		}
		//if motor is tilted towards left
		if(sum > 0 )
		{
			forward(1,1,0);

		}

	}
}



void InitAD( int sensor )
{
	// Set Config Bits	
/*
	ADCON1 = 0b00000000;
	ADCON0 = 0b00000101;
	ADCON2 = 0b00110001;
*/

	switch(sensor)
	{	

		// AN11
		case RIGHTSENSOR:

			ADCON1 = 0b00000011;//VSS,VDD ref. AN0 analog only
			ADCON2 = 0b00001000;//ADCON2 setup: Left justified, Tacq=2Tad, Tad=2*Tosc (or Fosc/2)
			ADCON0 = 0b00101101;//clear ADCON0 to select channel 0 (AN0)

			ADCON0bits.ADON = 0x01;//Enable A/D module
			break;

		// AN 9
		case MIDDLESENSOR:
			ADCON1 = 0b00000011;//VSS,VDD ref. AN0 analog only
			ADCON2 = 0b00001000; //ADCON2 setup: Left justified, Tacq=2Tad, Tad=2*Tosc (or Fosc/2)
			ADCON0 = 0b00100101;//clear ADCON0 to select channel 0 (AN0)
			ADCON0bits.ADON = 0x01;//Enable A/D module
			break;

		// AN 8 
		case LEFTSENSOR:
			ADCON1 = 0b00000011;//VSS,VDD ref. AN0 analog only
			ADCON2 = 0b00001000;//ADCON2 setup: Left justified, Tacq=2Tad, Tad=2*Tosc (or Fosc/2)
			ADCON0 = 0b00100001;//clear ADCON0 to select channel 0 (AN0)
			ADCON0bits.ADON = 0x01;//Enable A/D module
			break;
		default:
			break;
	}

}

int ConvertAD(void)
{
	int output = 0;
	int temp1 = 0;
	int temp2 = 0;

	ADCON0bits.GO_DONE = 1;
	while(ADCON0bits.GO_DONE != 0);
	output = ADRESH;
	temp1 = output << 2;
		temp2 = ADRESL >> 6;
	output = temp1 + temp2;		
	return output;
}



void adjust_forward(int times)
{
		int i, left, right;

		for(i=0;i<times;i++)
		{
			InitAD(LEFTSENSOR);
			left = ConvertAD();
			InitAD(RIGHTSENSOR);
			right = ConvertAD();
//		  if(left>OPTIMAL && right>OPTIMAL)
		  {
			if(left<right)
			{
				current_pulse_left = next_pulse(current_pulse_left);
				PORTA = current_pulse_left;
				Delay100TCYx(DELAY);
//				current_pulse_right = next_pulse(current_pulse_right);
//				PORTC = current_pulse_right;
//				Delay100TCYx(DELAY);
				current_pulse_left = next_pulse(current_pulse_left);
				PORTA = current_pulse_left;
				Delay100TCYx(DELAY);
			}
			if(right<left)
			{
				current_pulse_right = next_pulse(current_pulse_right);
				PORTC = current_pulse_right;
				Delay100TCYx(DELAY);
//				current_pulse_left = next_pulse(current_pulse_left);
//				PORTA = current_pulse_left;
//				Delay100TCYx(DELAY);
				current_pulse_right = next_pulse(current_pulse_right);
				PORTC = current_pulse_right;
				Delay100TCYx(DELAY);
			}
			else
			{
			current_pulse_right = next_pulse(current_pulse_right);
			PORTC = current_pulse_right;
			Delay100TCYx(DELAY);
			current_pulse_left = next_pulse(current_pulse_left);
			PORTA = current_pulse_left;
			Delay100TCYx(DELAY);
			}
		  }
//		  else
//		  {
//			current_pulse_right = next_pulse(current_pulse_right);
//			PORTC = current_pulse_right;
//			Delay100TCYx(DELAY);
//			current_pulse_left = next_pulse(current_pulse_left);
//			PORTA = current_pulse_left;
//			Delay100TCYx(DELAY);
//		  }
		}
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

void reverse(void) // moves the mouse approx 1/8 of a square forward
{
//	int i;

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
