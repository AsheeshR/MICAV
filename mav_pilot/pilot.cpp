#include "pilot.h"

void start_pilot()
{
    //Initialize IMU
#ifdef DEBUG_SERIAL    
    Serial.println("IMU Setup");
#endif
    imu_setup();
#ifdef DEBUG_SERIAL    
    Serial.println("Arm Motors");
#endif
    arm_motors();
#ifdef DEBUG_SERIAL    
    Serial.println("Controller Setup");
#endif
    setup_channels();
    //Initialize states
    //Initialize control system
}

float ypr2[3];

void update_pilot()
{
    //Update IMU
#ifdef DEBUG_SERIAL    
    Serial.println("Update IMU");
#endif
    imu_loop(ypr2);
//    update_channels();
#ifdef DEBUG_SERIAL    
    Serial.println("Update X");
#endif
    update_state(ypr2);
    //Run PID
#ifdef DEBUG_SERIAL    
    Serial.println("Update U");
#endif
    update_input();

    //Update control system
#ifdef DEBUG_SERIAL    
    Serial.println("Update motors");
#endif
    write_output();
    //Update thrust values
    

}
