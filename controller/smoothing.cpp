//This file will contain implementations of the smoothing algorithms

#include <smoothing.h>
#include <math.h>
#define SMA_LENGTH 5
#define SG_LENGTH 5
#define RDP_LENGTH 5
#define epsilon 30


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
    
int history_RDP[RDP_LENGTH] = {0,}; 
int index_RDP[]={0,};

  
void RDP(int start_index, int end_index)
{
  int a = history_RDP[end_index]-history_RDP[start_index];
  int b = -(end_index-start_index);
  int c = -start_index*a + end_index*b;
  
  float max_distance = 0;
  int max_index=0;
  float distance = 0;
  
  for( int i=start_index+1;i<end_index;i++)
  {
    distance=(i*a-history_RDP[i]*b+c)/sqrt(a^2+b^2);
    if (distance>max_distance)
    { 
      max_distance=distance;
      max_index=i;
    }
  }
  
  if(max_distance>epsilon)
  { 
        RDP(start_index,max_index);
        RDP(max_index,end_index);
   } 
   else 
    
   {
    for( int i=start_index+1;i<end_index;i++) 
    {
      history_RDP[i]=(-c-a*i)/b;
    }
   }
}
   
  int RDP_caller(int current_value)
{ 
  int update_value=history_RDP[0];
  for(int i=1;i<RDP_LENGTH;i++)
  { 
    history_RDP[i-1]=history_RDP[i];  
  }
  
  history_RDP[RDP_LENGTH-1]=current_value;
  
  RDP(0,RDP_LENGTH-1);
  return update_value;
}


    
  
  


