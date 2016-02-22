/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"


void main(){
	initTimer1();

	// delay until half a second 
	delay(500);
	//get 00:00:50
	printf("%s\n", getTimeString());


	// delay until 1s 75ms 
	delay(1250);
	//get 00:01:75
	printf("%s\n", getTimeString());


	// delay until 1min 
	delay(58750);
	//get 01:00:00
	printf("%s\n", getTimeString());

	initTimer1();
	//get 00:00:00
	printf("%s\n", getTimeString());
}