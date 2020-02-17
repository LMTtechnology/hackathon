#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// FIRE sensor SENSOR
#define inPin A4 
//int inPin = A0;
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
    val = digitalRead(inPin);   //Read digital value from HALL sensor 
    DEBUG_STREAM.print("FIREt: ");
    DEBUG_STREAM.println(val);
    delay(100);
}
