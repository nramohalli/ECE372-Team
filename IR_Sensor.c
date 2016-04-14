#include "IR_Sensor.h"
#include <xc.h>
#include "PWM.h"

#define SPEED 1023

// function to make car move forward
void forward(){
    setRightWheelSpeed(SPEED);
    setLeftWheelSpeed(SPEED);
    setRightForward(1);
    setLeftForward(1);
} // function to make car move forward
void right_turn(){
    setRightWheelSpeed(SPEED-60);
    setLeftWheelSpeed(SPEED+60);
    setRightForward(0);
    setLeftForward(0);
}// function to make car turn left
void left_turn(){
    setRightWheelSpeed(SPEED+60);
    setLeftWheelSpeed(SPEED-60);
    setRightForward(0);
    setLeftForward(0);
}//function to make car turn right

