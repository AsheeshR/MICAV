void setup()
{
  Serial.begin(9600);
  
}

int i=0;

void loop()
{
  Serial.println(millis());
  recurse();
  i=0;
  Serial.println("I'm done!");
  Serial.println(millis());
}


void recurse()
{
  i++;
  int j = 10000000/567890;
  int k = 10000000/590;
  int l = 10000/567890;
  int m = 10000000/890;
//  Serial.println(i);
  if(i>100)
  {
    return;
  }
  recurse();
}
