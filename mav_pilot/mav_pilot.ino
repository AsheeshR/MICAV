/* Global Header Files */
#include <Wire.h>
#include <Servo.h>
//#include <Serial.h>
#include <Arduino.h>

#define DEBUG_SERIAL 1

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
    Serial.begin(57600);

};

void loop()
{
    int t = millis();
    update_pilot();
    Serial.print("Loop time: ");
    Serial.println(millis()-t);
};
