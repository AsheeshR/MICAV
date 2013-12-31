#ifndef CONSTANTS
#define CONSTANTS

//Pin Configuration

#define PIN_M1 A0
#define PIN_M2 A1
#define PIN_M3 A2
#define PIN_M4 A3

#define PIN_THROTTLE 5
#define PIN_ROLL  6
#define PIN_PITCH  9
#define PIN_YAW  10

//ON HOLD #define PIN_TOGGLEM 2 //This should be connected to an interrupt handler

#define MULTIPLIER_YAW 3

#define THRESHOLD_CHANNEL_THROTTLE_MIN 1050
#define THRESHOLD_CHANNEL_THROTTLE_HOVER 1200
#define THRESHOLD_CHANNEL_THROTTLE_MAX 1645


#define THRESHOLD_MOTOR_MIN 1350
#define THRESHOLD_MOTOR_HOVER 1400
#define THRESHOLD_MOTOR_MAX 2400

#endif
