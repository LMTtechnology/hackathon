#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// FIRE SENSOR

int inPin1 = 15;
int inPin2 = 14;
bool val1 = 0;
bool val2 = 0;


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

    pinMode(inPin1, INPUT); 
    pinMode(inPin2, INPUT); 
  
}

void loop()
{
    val1 = digitalRead(inPin1);   //Read digital value from COLLISION sensor 
    val2 = digitalRead(inPin2);   //Read digital value from COLLISION sensor 

    DEBUG_STREAM.print("COLLISION: ");
    DEBUG_STREAM.print(val1);
    DEBUG_STREAM.print(" ");
    DEBUG_STREAM.println(val2);

    delay(100);
}
