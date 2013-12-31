int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;
int ch4;
int ch5;

void setup() {

  pinMode(5, INPUT); // Set our input pins as such
  pinMode(6, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(3, INPUT);

  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  ch1 = pulseIn(5, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(6, HIGH, 25000); // each channel
  ch3 = pulseIn(9, HIGH, 25000);
  ch4 = pulseIn(10, HIGH, 25000);
  ch5 = pulseIn(3, HIGH, 25000);

  Serial.print("Channel 1:"); // Print the value of 
  Serial.print(ch1);        // each channel

  Serial.print(" Channel 2:");
  Serial.print(ch2);

  Serial.print(" Channel 3:");
  Serial.print(ch3);
  
  Serial.print(" Channel 4:");
  Serial.print(ch4);

  Serial.print(" Channel 5:");
  Serial.println(ch5);

  delay(50); // I put this here just to make the terminal 
              // window happier
}
