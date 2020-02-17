//#include <Sodaq_R4X.h>
#include <Sodaq_N2X.h>
#include <Sodaq_wdt.h>
#include <Sodaq_LSM303AGR.h>
#include "DHT.h"

#if defined(ARDUINO_SODAQ_AUTONOMO)
/* SODAQ AUTONOMO + SODAQ NB-IoT R41XM Bee */
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define powerPin BEE_VCC
#define enablePin BEEDTR

#elif defined(ARDUINO_SODAQ_SARA)
/* SODAQ SARA AFF*/
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE
#define MODEM_ON_OFF_PIN SARA_ENABLE

#elif defined(ARDUINO_SODAQ_SFF)
/* SODAQ SARA SFF*/
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial
#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE

#else
#error "Please use one of the listed boards or add your board."
#endif

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

#define STARTUP_DELAY 5000

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

// LIGHT SENSOR
int analogPin_light = A0;
int ADC_light_value = 0;
//int light_intensity_value  = 0;

// POT SENSOR
int analogPin_pot = A7;
int ADC_pot_value = 0;
//int light_intensity_value  = 0;

// DHT22
#define DHTPIN A4 
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

float h = 0.0;
float t = 0.0;


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------


// NL VODAFONE NB-IoT
// const char* apn = "nb.inetd.gdsp";
// const char* forceOperator = "20404"; // optional - depends on SIM / network
// const char* urat = "8";

// NL VODAFONE LTE-M
//const char* apn = "live.vodafone.com";
//const char* forceOperator = "20404"; // optional - depends on SIM / network 
//const char* urat = "7";

// NL LMT NB
const char* apn = "nb-iot.lmt.lv";
const char* forceOperator = "24701"; // optional - depends on SIM / network (network Local) Country 
uint8_t urat = 20;

int temp_data = 23;
int hum_data = 45;
int pot_data = 502;
int light_data = 365;


// NL KPN
// const char* apn = "internet.m2m";
// const char* forceOperator = "20408"; // optional - depends on SIM / network


Sodaq_N2X n2x;
Sodaq_LSM303AGR AccMeter;

static Sodaq_SARA_N211_OnOff saraR4xxOnOff;

void sendMessageThroughUDP()
{
    DEBUG_STREAM.println();
    DEBUG_STREAM.println("Sending message through UDP");

    int localPort = 16666;
    int socketID = n2x.socketCreate(localPort);

    if (socketID >= 7 || socketID < 0) {
        DEBUG_STREAM.println("Socket:" + socketID);
        DEBUG_STREAM.println("Failed to create socket");
        return;
    }

    DEBUG_STREAM.println("Created socket!");

    String deviceId = "5oseDujrwhnFOb030EDDoWcK";
    String token = "maker:4KAR5LmHBiadW1VeVxRzM2co0SZWD6ufS2mwzyh1";
    String value = "{\"Humidity\":{\"value\":" + String(h) + 
                    "},\"Temperature\":{\"value\":" + String(t) +
                    "},\"Pot\":{\"value\":" + String(ADC_pot_value) +
                    "},\"Light\":{\"value\":" + String(ADC_light_value) +"}}";

    String reading = deviceId + '\n' + token + '\n' + value;

    uint8_t size = reading.length();
    int lengthSent = n2x.socketSend(socketID, "40.68.172.187", 8891, (uint8_t*)reading.c_str(), size);
    DEBUG_STREAM.print("Temreture is:" );
    DEBUG_STREAM.print("Length buffer vs sent:");
    DEBUG_STREAM.print(size);
    DEBUG_STREAM.print(",");
    DEBUG_STREAM.println(lengthSent);

    n2x.socketClose(socketID);
    DEBUG_STREAM.println();
}

void setup()
{
    sodaq_wdt_safe_delay(STARTUP_DELAY);

    dht.begin();
    
    #ifdef powerPin
    // Turn the nb-iot module on
    pinMode(powerPin, OUTPUT); 
    digitalWrite(powerPin, HIGH);
    DEBUG_STREAM.println("powerPin!");
  #endif
  
  #ifdef enablePin
    // Set state to active
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, HIGH);
    DEBUG_STREAM.println("enablePin!");
  #endif // enablePin

  
    Wire.begin();

    AccMeter.rebootAccelerometer();
    delay(1000);

    // Enable the Accelerometer
    AccMeter.enableAccelerometer();

    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    MODEM_STREAM.begin(n2x.getDefaultBaudrate());

    DEBUG_STREAM.println("Initializing and connecting... ");

    n2x.setDiag(DEBUG_STREAM);
    n2x.init(&saraR4xxOnOff, MODEM_STREAM);
 //   bool onn(true);
//    n2x.init(onn, MODEM_STREAM);
    if (n2x.on()) {
       DEBUG_STREAM.println("turning modem on");
    }
    //if (!n2x.connect(apn, urat)) {
    if (!n2x.connect("nb-iot.lmt.lv","0","24701", urat)) {
       DEBUG_STREAM.println("FAILED TO CONNECT TO MODEM");
    }
    DEBUG_STREAM.println("On UDP Sending!");
    sendMessageThroughUDP();
}

/**
* Returns the board temperature.
*/
int8_t getBoardTemperature()
{
    int8_t temp = AccMeter.getTemperature();

    return temp;
}

void loop()
{
    sodaq_wdt_safe_delay(5000);

    ADC_light_value = analogRead(analogPin_light);   //Read ADC value from light sensor 
    ADC_pot_value = analogRead(analogPin_pot);   //Read ADC value from light sensor 
    h = dht.readHumidity();
    t = dht.readTemperature();
    
    sendMessageThroughUDP();
}
