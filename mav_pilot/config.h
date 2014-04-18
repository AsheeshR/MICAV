/* This defines all the configuration variables for the entire system and the pin-map */


/* PIN Map */

//#define PIN_RX 0
//#define PIN_TX 1
//#define PIN_ 2
#define PIN_THROTTLE 3
//#define PIN_ 4
#define PIN_ROLL 5
#define PIN_PITCH 6
//#define PIN_ 7
//#define PIN_ 8
#define PIN_YAW 9 
#define PIN_AUX1 10
#define PIN_AUX2 11
//#define PIN_ 12
//#define PIN_ 13
#define PIN_MOTOR3 A0
#define PIN_MOTOR2 A1
#define PIN_MOTOR0 A2
#define PIN_MOTOR1 A3
//#define PIN_ 18 IMU Pins
//#define PIN_ 19



/* Configuration Values for Motor */
#define THRESHOLD_MOTOR0_MIN 1225
//#define THRESHOLD_MOTOR0_HOVER
#define THRESHOLD_MOTOR0_MAX 2400

#define THRESHOLD_MOTOR1_MIN 1325
//#define THRESHOLD_MOTOR0_HOVER
#define THRESHOLD_MOTOR1_MAX 2400

#define THRESHOLD_MOTOR2_MIN 1225
//#define THRESHOLD_MOTOR0_HOVER
#define THRESHOLD_MOTOR2_MAX 2025

#define THRESHOLD_MOTOR3_MIN 1375
//#define THRESHOLD_MOTOR0_HOVER
#define THRESHOLD_MOTOR3_MAX 1850


/* Configuration Values for Channels */
/* Morning Range */
/*
#define CHANNEL1_MIN 1100 
#define CHANNEL1_MAX 1875

#define CHANNEL2_MIN 1100
#define CHANNEL2_MAX 1875

#define CHANNEL3_MIN 1100
#define CHANNEL3_MAX 1875

#define CHANNEL4_MIN 1100
#define CHANNEL4_MAX 1875
*/
/* Evening Range */

#define CHANNEL1_MIN 950 
#define CHANNEL1_MAX 1650

#define CHANNEL2_MIN 950
#define CHANNEL2_MAX 1650

#define CHANNEL3_MIN 950
#define CHANNEL3_MAX 1650

#define CHANNEL4_MIN 950
#define CHANNEL4_MAX 1650
