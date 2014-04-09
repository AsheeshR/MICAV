/* This file implements the linear time invariant control system */

#include "controller.h"

//static int16_t X_dot[12] = {0, };
static int16_t X[12] = {0, };
static int16_t Y[12] = {0, };

/* A and B are too big to be allocated statically */
/* Most likely solution is predefined macros */

static int16_t U[4] = {0, };
/*static int8_t C[4][12] = { 
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
    };*/

static uint16_t channels[7], thrust[4]/*, heading[3]*/; /* WARNING: IMU RETURNS FLOATS! */

void update_input()
{
    update_channels(channels);
    
    /* Calculate Errors */
    U[0] = X[9] - map(channels[1], CHANNEL2_MIN, CHANNEL2_MAX, -10, 10); 
    U[1] = X[10] - map(channels[2], CHANNEL3_MIN, CHANNEL3_MAX, -10, 10);
    U[2] = X[11] - map(channels[3], CHANNEL4_MIN, CHANNEL4_MAX, -10, 10);
    
    U[4] = X[5] - map(channels[0], CHANNEL1_MIN, CHANNEL1_MAX, -1, 1);

    /* Apply PID to errors */
    U[0] = pid_dyaw(U[0]);
    U[1] = pid_dpitch(U[1]);
    U[2] = pid_droll(U[2]);
    U[3] = pid_daltitude(U[3]);
    
#ifdef DEBUG_SERIAL
    Serial.print("U Values : ");
    Serial.print(U[0]);
    Serial.print(U[1]);
    Serial.print(U[2]);
    Serial.print(U[3]);
    Serial.println();
#endif
}

void update_state(float heading[])
{
    /* X */
    //update_IMU();
    //imu_loop(ypr2);
    //X[0] = ; //x
    //X[1] = ; //y
    //X[2] = ; //z

    //X[3] = X[3] + X[0]; //dx
    //X[4] = X[4] + X[1]; //dy
    //X[5] = X[5] + X[2]; //dz

    X[6] = heading[0]; //YAW
    X[7] = heading[1]; //PITCH
    X[8] = heading[2]; //ROLL

    X[9] = heading[0] - X[6]; //dYAW
    X[10] = heading[1] - X[7]; //dPITCH
    X[11] = heading[2] - X[8]; //dROLL

#ifdef DEBUG_SERIAL
    Serial.print("YPR Values : ");
    Serial.print(X[6]);
    Serial.print(X[7]);
    Serial.print(X[8]);
    Serial.println();
#endif


#ifdef DEBUG_SERIAL
    Serial.print("dYdPdR Values : ");
    Serial.print(X[9]);
    Serial.print(X[10]);
    Serial.print(X[11]);
    Serial.println();
#endif

}

void update_control()
{
    /* X_dot = AX + Bu */
    
    

    
    

}


void update_output()
{
    int i;
    /* Y = CX */
    /* Y 12x1 
       C 12x12 = Identity
       X 12x1
    */
    for(i=0; i<12; i++)
	Y[i] = X[i];
    
}

void write_output()
{
    /* Reflect controls on driver */
    /* Map Y to T */
    int8_t C[][4] = 
	{1,1,1,1,
	 1,1,1,1,
	 1,1,1,1,
	 1,1,1,1
	};
    
#ifdef DEBUG_SERIAL
    Serial.print("Motors Values : ");
    Serial.print(thrust[0]);
    Serial.print(thrust[1]);
    Serial.print(thrust[2]);
    Serial.print(thrust[3]);
    Serial.println();
#endif
    
    
    thrust[0] = C[0][0] * U[0] + C[0][1] * U[1] + C[0][2] * U[2] + C[0][3] * U[3];
    thrust[1] = C[1][0] * U[0] + C[1][1] * U[1] + C[1][2] * U[2] + C[1][3] * U[3];
    thrust[2] = C[2][0] * U[0] + C[2][1] * U[1] + C[2][2] * U[2] + C[2][3] * U[3];
    thrust[3] = C[3][0] * U[0] + C[3][1] * U[1] + C[3][2] * U[2] + C[3][3] * U[3];

    update_motors(/*Servo * esc[],*/thrust);

}
