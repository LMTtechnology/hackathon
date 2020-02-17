#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// POTENTIOMETER SENSOR

int analogPin = A7;
int ADC_value = 0;
int potentiometer_value  = 0;

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");
}

void loop()
{
    ADC_value = analogRead(analogPin);   //Read ADC value from potentiometer 
    DEBUG_STREAM.print("ADC value: ");
    DEBUG_STREAM.println(ADC_value);
    delay(100);
}
