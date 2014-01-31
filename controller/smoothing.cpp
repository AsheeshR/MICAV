//This file will contain implementations of the smoothing algorithms

#include <smoothing.h>
#define SMA_LENGTH 5
#define SG_LENGTH 5


int history_SMA[SMA_LENGTH] = {0,};

int simple_mov_avg(int current_value)
{  
  int average=0,sum=0;
  for(int i=1;i<SMA_LENGTH;i++)
  { 
    history_SMA[i-1]=history_SMA[i];
  }
  
  history_SMA[SMA_LENGTH-1]=current_value;
  for(int j=0;j<SMA_LENGTH;j++)
  {
    sum+=history_SMA[j];
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

int history_SG[SG_LENGTH] = {0,};
const int coefficients[]={-3,12,17,12,-3};
const int normalization_value=35;

int savitzky_golay(int current_value)
{ 
  int sum=0;
  
  for(int i=1;i<SG_LENGTH;i++)
  {
         history_SG[i-1]=history_SG[i];
  }
    history_SG[SG_LENGTH-1]=current_value;
    
  for(int i=-(SG_LENGTH-1)/2;i<(SG_LENGTH/2);i++)
  {  
    sum+=history_SG[i]*coefficients[i];
  }
  
  history_SG[SG_LENGTH/2]=sum/normalization_value;
  
  return history_SG[SG_LENGTH/2];
  
}
    
  
  


