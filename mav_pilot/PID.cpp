/* This file implements the PID controllers for each state update */

#include "PID.h"

/* Timing Tests indicate 153 milliseconds */
int16_t pid_roll(int16_t roll)
{
    static int16_t integral = KI_ROLL*roll + integral;
//    int16_t derivative = KD_ROLL*roll; 
    static int16_t old_derivative = 0;
    int16_t result = KP_ROLL*roll + integral + KD_ROLL*roll - old_derivative;
    old_derivative = KD_ROLL*roll;

    result = constrain(result, PID_MIN_ROLL, PID_MAX_ROLL);
    return -result;
}

int16_t pid_pitch(int16_t pitch)
{
    static int16_t integral = KI_PITCH*pitch + integral;
//    int16_t derivative = KD_ROLL*roll; 
    static int16_t old_derivative = 0;
    int16_t result = KP_PITCH*pitch + integral + KD_PITCH*pitch - old_derivative;
    old_derivative = KD_PITCH*pitch;

    result = constrain(result, PID_MIN_PITCH, PID_MAX_PITCH);
    return -result;
}
