#include "TM1637.h"
#include "DHT.h"


#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// 4 digit 7 SEGMENT DISPLAY I2C

#define CLK 15  //pins definitions for TM1637 and can be changed to other ports
#define DIO 14
TM1637 tm1637(CLK,DIO);
int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
int8_t ListDisp[4];
unsigned char i = 0;
unsigned char count = 0;
int Thousands = 0;
int Hundreds = 0;
int Tens = 0;
int Ones = 0;

// LIGHT SENSOR
int analogPin = A0;
int ADC_value = 0;
int light_intensity_value  = 0;

// DHT22
#define DHTPIN A4 
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

float h = 0.0;
float t = 0.0;

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup()
{
    tm1637.init();
    tm1637.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    pinMode(19, OUTPUT);
    dht.begin();

    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    //MODEM_STREAM.begin(n2x.getDefaultBaudrate());
    DEBUG_STREAM.println("Initializing and connecting... ");



}

void loop()
{
    ADC_value = analogRead(analogPin);   //Read ADC value from light sensor 

    SegmentDisplayNumber(ADC_value);
    DEBUG_STREAM.print("ADC value: ");
    DEBUG_STREAM.println(ADC_value);
    delay(1000);

    h = dht.readHumidity();
    t = dht.readTemperature();
    DEBUG_STREAM.print("Temp: ");
    DEBUG_STREAM.print(t);
    DEBUG_STREAM.print(" Celsius ");
    DEBUG_STREAM.print("Hum: ");
    DEBUG_STREAM.print(h);
    DEBUG_STREAM.println(" %RH");

    SegmentDisplayNumber(t);
    delay(1000);

    SegmentDisplayNumber(h);
    delay(1000);
}

void SegmentDisplayNumber(int number)
{
    Thousands = number/1000;
    Hundreds = (number - Thousands*1000)/100;
    Tens = (number-Thousands*1000-Hundreds*100)/10;
    Ones = (number-Thousands*1000-Hundreds*100-Tens*10);

    ListDisp[0] = Thousands;
    ListDisp[1] = Hundreds;
    ListDisp[2] = Tens;
    ListDisp[3] = Ones;
    
    tm1637.display(0,ListDisp[0]);
    tm1637.display(1,ListDisp[1]);
    tm1637.display(2,ListDisp[2]);
    tm1637.display(3,ListDisp[3]);
}
