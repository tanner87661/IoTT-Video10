
int ledThreshold = 11; //threshold level to trigger touch button
int numRead = 4;//set the number of read commands in read burst

#define numPins 10
int analogPins[numPins] = {0,2,4,12,13,14,15,27,32,33}; //byte 0 is number of defined pins to follow

uint32_t startTime;
uint32_t finishTime;

void setup(){
  touch_pad_init();
  Serial.begin(115200);
}

void loop(){
  int val = 0;
  for (int j = 0; j < numPins; j++)
  {
    startTime = micros();
    val = touchRead(analogPins[j]);
    finishTime = micros();
    Serial.printf("Pin #: %d Value: %d Time: %l", analogPins[j], val, finishTime-startTime);
    Serial.println(); 
  }
}
