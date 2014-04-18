#ifndef CONSTANTS
#define CONSTANTS

//TBT -- To be tuned

//Pin Configuration

#define PIN_M1 A0
#define PIN_M2 A1
#define PIN_M3 A2
#define PIN_M4 A3

#define PIN_THROTTLE 3
#define PIN_ROLL  6
#define PIN_PITCH  9
#define PIN_YAW  10

//TBT
#define MULTIPLIER_PITCH 2
#define MULTIPLIER_ROLL 2

//Input Based Limits
#define THRESHOLD_CHANNEL_THROTTLE_MIN 1050
#define THRESHOLD_CHANNEL_THROTTLE_HOVER 1200 //TBT
#define THRESHOLD_CHANNEL_THROTTLE_MAX 1645

//Output Limits
#define THRESHOLD_MOTOR_MIN 1300
#define THRESHOLD_MOTOR_HOVER 1400 //TBT
#define THRESHOLD_MOTOR_MAX 2400

#endif
