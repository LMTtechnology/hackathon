#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// FIRE SENSOR

int inPin1 = 15;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");

    pinMode(inPin1, INPUT); 
    starttime = millis();//get the current time;
  
}

void loop()
{
    duration = pulseIn(inPin1, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
    {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        DEBUG_STREAM.print(lowpulseoccupancy);
        DEBUG_STREAM.print(",");
        DEBUG_STREAM.print(ratio);
        DEBUG_STREAM.print(",");
        DEBUG_STREAM.println(concentration);
        lowpulseoccupancy = 0;
        starttime = millis();
    }

}
