
#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// SENSOR
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

    if (tcs.begin()) {
        DEBUG_STREAM.println("Found sensor");
    } else {
        DEBUG_STREAM.println("No TCS34725 found ... check your connections");
        while (1);
    }

  
  
}

void loop()
{
    uint16_t r, g, b, c, colorTemp, lux;
    
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);

    DEBUG_STREAM.print("Color Temp: "); DEBUG_STREAM.print(colorTemp, DEC); DEBUG_STREAM.print(" K - ");
    DEBUG_STREAM.print("Lux: "); DEBUG_STREAM.print(lux, DEC); DEBUG_STREAM.print(" - ");
    DEBUG_STREAM.print("R: "); DEBUG_STREAM.print(r, DEC); DEBUG_STREAM.print(" ");
    DEBUG_STREAM.print("G: "); DEBUG_STREAM.print(g, DEC); DEBUG_STREAM.print(" ");
    DEBUG_STREAM.print("B: "); DEBUG_STREAM.print(b, DEC); DEBUG_STREAM.print(" ");
    DEBUG_STREAM.print("C: "); DEBUG_STREAM.print(c, DEC); DEBUG_STREAM.print(" ");
    DEBUG_STREAM.println(" ");

}
