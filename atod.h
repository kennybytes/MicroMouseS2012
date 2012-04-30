/*
 *
 *
 * File Name:	atod.h
 * Author:	Kenny Luong
 *
 * Description:
 * 	The AtoD library contains the functions responsible for converting
 * 	analog voltage input from our sensors to discrete digital output 
 * 	that we can use.
 *
 */


#define RIGHTSENSOR 1
#define FRONTSENSOR 2
#define LEFTSENSOR 3

#include <p18f4620.h>
#include <delays.h>

void InitAD(int sensor);
int ConvertAD(void);
void FetchAllSensors( int *left, int *front, int *right );
int FetchSensor(int whichsensor);
