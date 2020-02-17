
#include "Ultrasonic.h"

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// FIRE sensor SENSOR
#define inPin A4 
//int inPin = A0;
bool val = 0;

Ultrasonic ultrasonic(inPin);
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... "); 
}

void loop()
{
    long RangeInInches;
    long RangeInCentimeters;


    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    DEBUG_STREAM.print(RangeInCentimeters);//0~400cm
    DEBUG_STREAM.println(" cm");
    delay(250);
}
