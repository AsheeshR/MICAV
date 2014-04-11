/* This file defines the motor and channel control functions */
/* Dependencies - Serial & Servo */

#include "config.h"
#include <stdint.h>
#include <Arduino.h>
#include <Servo.h>

/* Motor Functions
 * The thrust array is in order of 1,2,3,4 clockwise direction 
 * however array indexes are from 0 to 3
 */
void arm_motors();
void update_motors(/*Servo * esc[],*/ int16_t thrust[]);
void cutoff_motors();

/* Channel Functions
 * The channel array is a 7 member array stroring all 7 channel readings.
 * The channels are in order:
 * 0 = CHANNEL1 : Thrust
 * 1 = CHANNEL2 : Yaw
 * 2 = CHANNEL3 : Pitch
 * 3 = CHANNEL4 : Roll
 */

void setup_channels();
void update_channels(uint16_t channels[]);

