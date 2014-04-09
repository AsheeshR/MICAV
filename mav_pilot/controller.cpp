/* This file implements the linear time invariant control system */

static int16_t X_dot[12] = {0, };
static int16_t X[12] = {0, };

/* A and B are too big to be allocated statically */
/* Most likely solution is predefined macros */

static int16_t U[4][0] = {0, };
static int8_t C[4][12] = { 
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

static uint16_t channels[7], thrust[4], heading[3]; /* WARNING: IMU RETURNS FLOATS! */

void update_input()
{
    update_channels(uint16_t channels[]);
    
    /* Calculate Errors */
    U[0] = X[9] - map(channel[1],); 
    U[1] = X[10] - map(channel[2],);
    U[2] = X[11] - map(channel[3],);
    
    U[4] = X[5] - map(channel[0],);

    /* Apply PID to errors */
    U[0] = pid_dyaw(U[0]);
    U[1] = pid_dpitch(U[1]);
    U[2] = pid_droll(U[2]);
    U[3] = pid_daltitude(U[3]);
    
}

void update_state()
{
    /* X */
    //update_IMU();
    
    //X[0] = ; //x
    //X[1] = ; //y
    //X[2] = ; //z

    //X[3] = X[3] + X[0]; //dx
    //X[4] = X[4] + X[1]; //dy
    //X[5] = X[5] + X[2]; //dz

    X[6] = heading[0]; //YAW
    X[7] = heading[1]; //PITCH
    X[8] = heading[2]; //ROLL

    X[9] = heading[0] - X[9]; //dYAW
    X[10] = heading[1] - X[10]; //dPITCH
    X[11] = heading[2] - X[11]; //dROLL
}

void update_control()
{
    /* X_dot = AX + Bu */
    


    
    

}


void update_output()
{
    /* Y = CX */
    /* Y 4x1 
       C 4x12
       X 12x1
    */
    
    Y[0] = C[0][0] * 
    
    
    
}

void write_output()
{
    /* Reflect controls on driver */
    /* Map Y to T */
    thrust[0] = C[0][0] * Y[0] + C[0][1] * Y[1] + C[0][2] * Y[2] + C[0][3] * Y[3];
    thrust[1] = C[1][0] * Y[0] + C[1][1] * Y[1] + C[1][2] * Y[2] + C[1][3] * Y[3];
    thrust[2] = C[2][0] * Y[0] + C[2][1] * Y[1] + C[2][2] * Y[2] + C[2][3] * Y[3];
    thrust[3] = C[3][0] * Y[0] + C[3][1] * Y[1] + C[3][2] * Y[2] + C[3][3] * Y[3];

    update_motors(/*Servo * esc[],*/ uint16_t thrust[]);

}
