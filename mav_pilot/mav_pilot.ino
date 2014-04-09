/* Global Header Files */
#include <Wire.h>
#include <Servo.h>
//#include <Serial.h>
#include <Arduino.h>

/* Project Header Files */
#include "config.h"
#include "drivers.h"
#include "PID.h"
#include "controller.h"
#include "Razor_AHRS.h"
#include "pilot.h"


void setup()
{
    start_pilot();
};

void loop()
{
    update_pilot();
};
