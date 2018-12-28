#include "Arduino.h"
#include "Mux.h"


/**
* Construct - no setup
**/
Mux::Mux() {
	//
}


/**
* Construct + setup
**/
Mux::Mux(int dPin0, int dPin1, int dPin2, int dPin3, int * signalPin, int enablePin) {
	setup(dPin0,dPin0,dPin0,dPin0,signalPin,enablePin);
}


/**
* @public
*/
void Mux::setup(int dPin0, int dPin1, int dPin2, int dPin3, int * signalPin, int enablePin){
	
	this->dPin0 			= dPin0;
	this->dPin1 			= dPin1;
	this->dPin2 			= dPin2;
	this->dPin3 			= dPin3;
	this->signalPin 		= signalPin;
	this->enablePin			= enablePin;
	currentChannel 			= -1;
	lastIO					= NULL;
	
	// using the EN pin?
	if(enablePin>-1) {
		pinMode(enablePin, OUTPUT);	
		digitalWrite(enablePin, LOW); // start enabled
	}
	
	int pins[4] = {dPin0,dPin1,dPin2,dPin3};
	int i 		= 0;
	
	for(i=0;i<4;i++){
		// set pinMode for the digital control pins 
		if (pins[i] >= 0)
		{
			pinMode(pins[i], OUTPUT);
			// set all control pins LOW 
			digitalWrite(pins[i], LOW);
		}
	}
	numPins = *(&signalPin[0]);
	if (numPins > 0)
	  lastIO = (int*)realloc(lastIO, numPins * sizeof(int));
	for(i=0;i<numPins;i++)
 	  *(&lastIO[i]) = -1;
	
}


/**
* @public
*/
void Mux::setEnabled(bool enabled){
	if(enablePin!=-1){
		digitalWrite(enablePin, enabled ? LOW : HIGH);
	}
}

	
/**
* @public
*
**/	
int Mux::readTouch(int channel, int index){
	if(*(&lastIO[index]) != MUX_IO_READ) 
	{
		pinMode(*(&signalPin[index+1]), INPUT);
		*(&lastIO[index]) = MUX_IO_READ;
	}
	setChannel(channel);
	return touchRead(*(&signalPin[index+1]));
}


/**
* @public
*
**/
int Mux::readDigital(int channel, int index){
	if(*(&lastIO[index]) != MUX_IO_READ) 
	{
		pinMode(*(&signalPin[index+1]), INPUT);
		*(&lastIO[index]) = MUX_IO_READ;
	}
	setChannel(channel);
	return analogRead(*(&signalPin[index+1])) < 512 ? LOW : HIGH;
}

int Mux::readAnalog(int channel, int index){
	if(*(&lastIO[index]) != MUX_IO_READ) 
	{
		pinMode(*(&signalPin[index+1]), INPUT);
		*(&lastIO[index]) = MUX_IO_READ;
	}
	setChannel(channel);
	return analogRead(*(&signalPin[index+1]));
}

/**
* @public
* 
**/
void Mux::write(int channel, int index, int value){
	if(*(&lastIO[index]) != MUX_IO_WRITE) 
	{
		pinMode(*(&signalPin[index+1]), OUTPUT);
		*(&lastIO[index]) = MUX_IO_WRITE;
	}
	setChannel(channel);
	digitalWrite(*(&signalPin[index+1]), value);
}


/**
* @private 
* set the current mux channel [0-15] using 4 digtal pins to write the 4 bit integer
*/
void Mux::setChannel(int channel){
	if(currentChannel != channel) {
		if (dPin0 >= 0)
			digitalWrite(dPin0, bitRead(channel,0));
		if (dPin1 >= 0)
			digitalWrite(dPin1, bitRead(channel,1));
		if (dPin2 >= 0)
			digitalWrite(dPin2, bitRead(channel,2));
		if (dPin3 >= 0)
			digitalWrite(dPin3, bitRead(channel,3));
		currentChannel = channel;
		delay(5);
	}
}
