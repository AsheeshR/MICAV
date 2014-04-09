/* This file defines the control system */
/* Dependencies - Serial */


#include "config.h"
#include "drivers.h"
#include "PID.h"
#include <stdint.h>

void update_input();
void update_state(float []);
void update_control();
void update_output();

void write_output();


