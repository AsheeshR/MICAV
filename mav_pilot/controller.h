/* This file defines the control system */
/* Dependencies - Serial */

#ifndef MICAV_CONTROLLER
#define MICAV_CONTROLLER

#include "config.h"
#include "drivers.h"
#include "PID.h"
#include <stdint.h>

#define MAX_DYAW 100
#define MIN_DYAW -100
#define MAX_DPITCH 100
#define MIN_DPITCH -100
#define MAX_DROLL 100
#define MIN_DROLL -100

#define MAX_DYAW 100
#define MIN_DYAW -100
#define MAX_DPITCH 100
#define MIN_DPITCH -100
#define MAX_ROLL 150
#define MIN_ROLL -150 /*Degrees*10*/




void update_input();
void update_state(float []);
//void update_control();
//void update_output();

void write_output();

#endif /* MICAV_CONTROLLER */
