#include "Adafruit_VL53L0X.h"

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// SENSOR
Adafruit_VL53L0X lox = Adafruit_VL53L0X();


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

    // wait until serial port opens for native USB devices
    while (! DEBUG_STREAM) {
        delay(1);
    }
  
    DEBUG_STREAM.println("Adafruit VL53L0X test");
    if (!lox.begin()) {
        DEBUG_STREAM.println(F("Failed to boot VL53L0X"));
        while(1);
    }
    // power 
    DEBUG_STREAM.println(F("VL53L0X API Simple Ranging example\n\n")); 

  
  
}

void loop()
{
  VL53L0X_RangingMeasurementData_t measure;
    
  DEBUG_STREAM.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    DEBUG_STREAM.print("Distance (mm): "); DEBUG_STREAM.println(measure.RangeMilliMeter);
  } else {
    DEBUG_STREAM.println(" out of range ");
  }
    
  delay(100);
}
