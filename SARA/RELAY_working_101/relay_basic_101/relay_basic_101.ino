#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

#define PinOut A4
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    // Setup relay
    pinMode(PinOut, OUTPUT);  
    digitalWrite(PinOut, LOW);   //Switch relay OFF
    
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");
}

void loop()
{
    digitalWrite(PinOut, HIGH);   //Switch relay ON
    DEBUG_STREAM.println("BUZZER ON");

    delay(1000);
    
    digitalWrite(PinOut, LOW);   //Switch relay OFF
    DEBUG_STREAM.println("BUZZER OFF");

    delay(1000);
}
