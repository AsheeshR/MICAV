//This file will contain prototypes for the smoothing algorithms
#ifndef SMOOTH
#define SMOOTH

#define SMA_LENGTH 5
extern int history_SMA[SMA_LENGTH];
int simple_mov_avg(int current_value);


#endif
