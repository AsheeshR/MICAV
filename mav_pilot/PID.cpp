/* This file implements the PID controllers for each state update */

#include "PID.h"


int16_t pid_roll(int16_t roll)
{
    static int16_t integral = KI_ROLL*roll + integral;
    int16_t derivative = KD_ROLL*roll; 
    static int16_t old_derivative = 0;
    int16_t result = KP_ROLL*roll + integral + derivative - old_derivative;
    old_derivative = derivative;

    result = constrain(result, PID_MIN_ROLL, PID_MAX_ROLL);
    return -result;
}


/* 
int16_t pid_roll(int16_t roll)
{
    static int16_t roll_old = 0;
    int16_t result = 
	(KP_ROLL * roll) + 
	(KI_ROLL * (roll_old + roll)) +
	(KD_ROLL * (roll - roll_old))
	;
    roll_old += roll;
    result = constrain(result, PID_MIN_ROLL, PID_MAX_ROLL);
    return -result;
}
*/
