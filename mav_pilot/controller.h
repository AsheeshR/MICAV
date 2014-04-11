/* This file defines the control system */
/* Dependencies - Serial */


#include "config.h"
#include "drivers.h"
#include "PID.h"
#include <stdint.h>

#define MAX_DYAW 50
#define MIN_DYAW -50
#define MAX_DPITCH 50
#define MIN_DPITCH -50
#define MAX_DROLL 50
#define MIN_DROLL -50

void update_input();
void update_state(float []);
void update_control();
void update_output();

void write_output();


