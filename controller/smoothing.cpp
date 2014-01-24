//This file will contain implementations of the smoothing algorithms

#include <smoothing.h>
#define SMA_LENGTH 5

int history[SMA_LENGTH] = {0,};

int simple_mov_avg(int current_value)
{  
  int average=0,sum=0;
  for(int i=1;i<SMA_LENGTH;i++)
  { 
    history[i-1]=history[i];
  }
  
  history[SMA_LENGTH-1]=current_value;
  for(int j=0;j<SMA_LENGTH;j++)
  {
    sum+=history[j];
  }
  
  average=sum/SMA_LENGTH;
  
  return average;
}

int cumulative_mov_avg(int current_value)

{ static int cumulative_average=0;
  static int k=0;
  k++;
  
  cumulative_average=(current_value+k*cumulative_average)/(k+1);
  return cumulative_average;
}

int exponential_mov_avg(int current_value)

{ float alpha=0.8;
  static int exponential_average=current_value;
  
  exponential_average=alpha*current_value + (1-alpha)*exponential_average;
  return exponential_average; 
  
}
  

