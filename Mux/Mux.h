#ifndef Mux_h
#define Mux_h

#include "Arduino.h"

#define MUX_IO_READ 0
#define MUX_IO_WRITE 1

/**
* Mux control lib for CD74HC4067
* 
* Made for / tested with Analog/Digital MUX Breakout from sparkfun: https://www.sparkfun.com/products/9056
*/
class Mux {

   public:
    
	/**
	* Constructor - you'll need to call Mux::setup later if not passing parameters here.
	*/
    Mux();
	
	/**
	* @see Mux::setup
	*/
	Mux(int dPin0, int dPin1, int dPin2, int dPin3, int * signalPin, int enablePin=-1);
   
	/**
     *  set Pin # to -1 for not using the pin, i.e. for using only channels 0..3, set dPin2 and dPin3 to -1 and wire the MUX inputs to Vcc
	* setup 
	* @param dPin0		- digital control pin0
	* @param dPin1		- digital control pin1
	* @param dPin2		- digital control pin2
	* @param dPin3		- digital control pin3
	* @param signalPin 	- array of analog io pins to read/write data on. First byte is # of pins to follow
	* @param enablePin 	- optional, use if you have connected the EN (enable) pin to a digtal pin.
	*					 defaults to -1 (unused) if not set here.
	*/
    void setup(int dPin0, int dPin1, int dPin2, int dPin3, int * signalPin, int enablePin=-1);
	
	/**
	* setEnabled
	* If the EN (enable) pin is connected to a digital output on the arduino, 
	* and not just connected to ground, use this to enable/disable all IO pins on the board.
	*/
	void setEnabled(bool enabled);
	
	
	/**
	* Read from the chosen channel - the returned value will be in the range of 0 to 1023
	* For reading digital signals, assume a value >= 512 is HIGH and < 512 is LOW - or just use Mux::dRead, which does that mapping for you. Unused pins are ignored, resulting in reading the same input for several addresses.
	* @param channel
	*/
	int readTouch(int channel, int index); //touch read
	
	
	/**
	* @param channel - channel to read from
	* @return HIGH or LOW
	*/
	int readDigital(int channel, int index); //digital read

	int readAnalog(int channel, int index); //analog read
	
	/**
	* @param channel
	* @param value - HIGH or LOW
	**/
    void write(int channel, int index, int value);
	
	
  protected:
	int enablePin; // EN - HIGH==all outputs disabled, LOW==everything is enabled
	int * signalPin;
    int dPin0;
    int dPin1;
    int dPin2;
    int dPin3;
	
	int * lastIO = NULL; //array with value for each pin whether last operation was read or write. Allocated in setup
	int numPins = 0; //number of analog pins used
	int currentChannel;
	
	void setChannel(int channel);
};

#endif
