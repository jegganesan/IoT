/*
* Read ultrasonic sensor code and write to 7 segment display
*
*/


int num_array[10][7] = {  { 1,1,1,1,1,1,0 },    // 0
                          { 1,0,1,0,0,0,0 },    // 1
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,0,0,1 },    // 3
                          { 1,0,1,0,0,1,1 },    // 4
                          { 0,1,1,1,0,1,1 },    // 5
                          { 0,1,1,1,1,1,1 },    // 6
                          { 1,1,1,0,0,0,0 },    // 7
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,1,1,1,0,1,1 }};   // 9
                                       
//function header
void Num_Write(int);

// defines pins numbers
const int trigPin = 2;
const int echoPin = 3;
int trail = 0;
int pinArray[] = {4,5,6,7,8,9,10};

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  for (int j=0; j < 7; j++) {
    pinMode(pinArray[j], OUTPUT);
  }   
}


void loop() {
  // defines variables
  long duration;
  int distance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2 * 0.0328084;

  if(distance > 9) {
    distance = 9;
  }
  Num_Write(distance);//trail);
  trail++;
  if(trail == 10) {
    trail = 0; 
  }
  delay(3000);
  if(distance < 1) {
    Serial.print("Tank full");
    Serial.println(distance);
  }
  else {
    Serial.print("Tank distance: ");
    Serial.println(distance);
  }
  delay(2000);
}

// this functions writes values to the sev seg pins  
void Num_Write(int number) 
{
  for (int j=0; j < 7; j++) {
   digitalWrite(pinArray[j], num_array[number][j]);
  }
}
