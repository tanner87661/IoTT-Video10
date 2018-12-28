#include <Mux.h>

//Mux mux(2,3,4,5,A0); // initialise on construct... 
Mux mux; // ...or construct now, and call setup later

int counter=0;

void setup(){

  Serial.begin(115200);
  mux.setup(17,8,15,2,4,16); // initialise on setup
  
}


void loop(){
  
  int val = mux.read(counter);
  if(counter==15){
    Serial.println(val); 
  }else{
    Serial.print(val);
    Serial.print(", "); 
  }
  
  counter = ++counter & 15;
  
  delay(50);
}
