/*
 *
 *
 * atod.h
 *
 *
 */


#define RIGHTSENSOR 1
#define MIDDLESENSOR 2
#define LEFTSENSOR 3

#include <p18f4620.h>
#include <delays.h>

void InitAD(int sensor);
int ConvertAD(void);
