/* This file defines the motor and channel control functions */
/* Dependencies - Serial & Servo */

#include "config.h"
#include <stdint.h>
#include <Arduino.h>
#include <Servo.h>

void arm_motors();
void update_motors(/*Servo * esc[],*/ uint16_t thrust[]);
void cutoff_motors();


void setup_channels();
void update_channels(uint16_t channels[]);
