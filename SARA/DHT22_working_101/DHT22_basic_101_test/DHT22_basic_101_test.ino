#include "DHT.h"

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// DHT22

#define DHTPIN A4 
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

float h = 0.0;
float t = 0.0;

//int digPin = A0;
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    dht.begin();

    //pinMode(digPin, OUTPUT);

    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    DEBUG_STREAM.println("Initializing and connecting... ");
}

void loop()
{
    h = dht.readHumidity();
    t = dht.readTemperature();
    DEBUG_STREAM.print("Temp: ");
    DEBUG_STREAM.print(t);
    DEBUG_STREAM.print(" Celsius ");
    DEBUG_STREAM.print("Hum: ");
    DEBUG_STREAM.print(h);
    DEBUG_STREAM.println(" %RH");
    //digitalWrite(digPin, HIGH);
    delay(1000);
    //digitalWrite(digPin, LOW);
    //delay(1000);
}
