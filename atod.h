/*
 *
 *
 * atod.h
 *
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
