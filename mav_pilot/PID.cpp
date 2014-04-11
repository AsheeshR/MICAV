/* This file implements the PID controllers for each state update */

#include "PID.h"

int16_t pid_dyaw(int16_t dyaw)
{
    static int16_t dyaw_old = 0;
    return 
	(
	dyaw_old = 
	KP_DYAW * dyaw + 
	dyaw_old + KI_DYAW * dyaw +
	KD_DYAW * (dyaw - dyaw_old)
	);
}

int16_t pid_dpitch(int16_t dpitch)
{
    static uint16_t dpitch_old = 0;
    return 
	(
	dpitch_old = 
	KP_DPITCH * dpitch + 
	dpitch_old + KI_DPITCH * dpitch +
	KD_DPITCH * (dpitch - dpitch_old)
	);
}

int16_t pid_droll(int16_t droll)
{
    static uint16_t droll_old = 0;
    return 
	(
	droll_old = 
	KP_DROLL * droll + 
	droll_old + KI_DROLL * droll +
	KD_DROLL * (droll - droll_old)
	);
}

int16_t pid_daltitude(int16_t daltitude)
{
    static uint16_t daltitude_old = 0;
    return 
	(
	daltitude_old = 
	KP_DALTITUDE * daltitude + 
	daltitude_old + KI_DALTITUDE * daltitude +
	KD_DALTITUDE * (daltitude - daltitude_old)
	);
}
