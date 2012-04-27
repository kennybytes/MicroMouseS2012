#include <p18f4620.h>



void InitAD(int sensor)
{
	
	/* Some Example Config Bits */
	/*
	ADCON1 = 0b00000000;
	ADCON0 = 0b00000101;
	ADCON2 = 0b00110001;
	*/

	switch(sensor)
	{	
		// AN11
		// Right Sensor
		case RIGHTSENSOR:

			ADCON1 = 0b00000011;//VSS,VDD ref. AN0 analog only
			ADCON2 = 0b00001000;//ADCON2 setup: Left justified, Tacq=2Tad, Tad=2*Tosc (or Fosc/2)
			ADCON0 = 0b00101101;//clear ADCON0 to select channel 0 (AN0)
			ADCON0bits.ADON = 0x01;//Enable A/D module
			break;

		// AN 9
		// Middle Sensor
		case MIDDLESENSOR:
			ADCON1 = 0b00000011;//VSS,VDD ref. AN0 analog only
			ADCON2 = 0b00001000; //ADCON2 setup: Left justified, Tacq=2Tad, Tad=2*Tosc (or Fosc/2)
			ADCON0 = 0b00100101;//clear ADCON0 to select channel 0 (AN0)
			ADCON0bits.ADON = 0x01;//Enable A/D module
			break;

		// AN 8 
		// Left Sensor
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

	// GO 
	ADCON0bits.GO_DONE = 1;

	// Wait until A/D is done
	while(ADCON0bits.GO_DONE != 0);


	// Shift our output into a 10 bit int
	temp1 = ADRESH << 2;
	temp2 = ADRESL >> 6;
	output = temp1 + temp2;		


	return output;


}
