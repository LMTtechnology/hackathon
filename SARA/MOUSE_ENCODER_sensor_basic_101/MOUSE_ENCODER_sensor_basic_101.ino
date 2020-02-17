#include "EncoderStepCounter.h"
#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// MOUSE ENCODER SENSOR

#define ENCODER_PIN1 14
#define ENCODER_PIN2 15

EncoderStepCounter encoder(ENCODER_PIN1, ENCODER_PIN2);

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

    // Initialize encoder
    encoder.begin();
  
}

void interrupt() {
  encoder.tick();
}

signed char lastpos = 0;

void loop()
{
  // Call tick on every loop
  encoder.tick();
  // Print out current encoder value
  // Have a look at the InterruptExample on how
  // to have a bigger variable for the counter
  signed char pos = encoder.getPosition();
  if (pos != lastpos) {
    lastpos = pos;
    DEBUG_STREAM.println(pos);
  }


}
