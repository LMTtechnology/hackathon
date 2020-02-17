#include <Wire.h>
#include "Seeed_QTouch.h"


#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// SENSOR



//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

     Wire.begin();      //Intel Edison need this procedure
}

void loop()
{
  int tn = QTouch.touchNum();
    
  if (tn >= 0) {
        DEBUG_STREAM.print("KEY");
        DEBUG_STREAM.print(tn);
        DEBUG_STREAM.println(" touched");
    }
    
  delay(10);
}
