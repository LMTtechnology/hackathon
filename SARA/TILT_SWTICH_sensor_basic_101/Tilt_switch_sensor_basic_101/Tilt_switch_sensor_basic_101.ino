#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// TILT SWITCH SENSOR

int inPin = 15;
bool val = 0;

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

    pinMode(inPin, INPUT);  
}

void loop()
{
    val = digitalRead(inPin);   //Read digital value from TILT SWITCH sensor 
    DEBUG_STREAM.print("Tilt: ");
    DEBUG_STREAM.println(val);
    delay(100);
}
