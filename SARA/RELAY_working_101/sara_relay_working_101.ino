#include <Sodaq_N2X.h>
#include <Sodaq_wdt.h>
#include <Sodaq_LSM303AGR.h>

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

// NL LMT NB
const char* apn = "nb-iot.lmt.lv";
const char* forceOperator = "24701"; // optional - depends on SIM / network (network Local) Country 
uint8_t urat = 20;

float h = 0.0;
float t = 0.0;

Sodaq_N2X n2x;
Sodaq_LSM303AGR AccMeter;

static Sodaq_SARA_N211_OnOff saraR4xxOnOff;

//void sendMessageThroughUDP()
//{   
//    dht.begin();
//    DEBUG_STREAM.println();
//    DEBUG_STREAM.println("Sending message through UDP");
//
//    int localPort = 16666;
//    int socketID = n2x.socketCreate(localPort);
//    float h = dht.readHumidity();
//    float t = dht.readTemperature();
//    DEBUG_STREAM.print("Temp: ");
//    DEBUG_STREAM.print(t);
//    DEBUG_STREAM.print(" Celsius ");
//    DEBUG_STREAM.print("Hum: ");
//    DEBUG_STREAM.print(h);
//    DEBUG_STREAM.println(" %RH");
//    if (socketID >= 7 || socketID < 0) {
//        DEBUG_STREAM.println("Socket:" + socketID);
//        DEBUG_STREAM.println("Failed to create socket");
//        return;
//    }
//
//    DEBUG_STREAM.println("Created socket!");
//
//    String deviceId = "L33ycVs8J9qH9gCFCesTcUmu";
//    String token = "maker:4Tzjh6k3RxY8G0lqFxfosTbyakzFyv5pcTYZb411";
//    String value = "{\"t\":{\"value\":" + String(getBoardTemperature()) +"}}";
//
//    String reading = deviceId + '\n' + token + '\n' + value;
//
//    uint8_t size = reading.length();
//    int lengthSent = n2x.socketSend(socketID, "40.68.172.187", 8891, (uint8_t*)reading.c_str(), size);
//    DEBUG_STREAM.print("Temreture is:" );
//    DEBUG_STREAM.print("Length buffer vs sent:");
//    DEBUG_STREAM.print(size);
//    DEBUG_STREAM.print(",");
//    DEBUG_STREAM.println(lengthSent);
//    DEBUG_STREAM.println();
//    
//    DEBUG_STREAM.print("DTH Sensor: \n" );
//    
//    
//    int tempr = dht.readTemperature();
//    int hum = dht.readHumidity();
//        DEBUG_STREAM.print("0Temperature: "); 
//        DEBUG_STREAM.print(tempr);
//        DEBUG_STREAM.print("  AND  ");
//        DEBUG_STREAM.print("0HM: "); 
//        DEBUG_STREAM.print(hum);
//        DEBUG_STREAM.print("\n"); 
//        
//    if (isnan(t) || isnan(h)) 
//    {
//        DEBUG_STREAM.println("Failed to read from DHT");
//    } 
//    else 
//    {
//        DEBUG_STREAM.print("Humidity: "); 
//        DEBUG_STREAM.print(h);
//        DEBUG_STREAM.print(" %\t");
//        DEBUG_STREAM.print("Temperature: "); 
//        DEBUG_STREAM.print(t);
//        DEBUG_STREAM.println(" *C");
//    }
//
//    n2x.socketClose(socketID);
//    DEBUG_STREAM.println();
//}

void setup()
{
    sodaq_wdt_safe_delay(STARTUP_DELAY);

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

    // Setup relay
    pinMode(15, OUTPUT);  
    digitalWrite(15, HIGH);   //Switch relay ON
    
    Wire.begin();
    AccMeter.rebootAccelerometer();
    delay(1000);

    // Enable the Accelerometer
    AccMeter.enableAccelerometer();

    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    //MODEM_STREAM.begin(n2x.getDefaultBaudrate());

    DEBUG_STREAM.println("Initializing and connecting... ");

    //n2x.setDiag(DEBUG_STREAM);
   // n2x.init(&saraR4xxOnOff, MODEM_STREAM);
 //   bool onn(true);
//    n2x.init(onn, MODEM_STREAM);
//    if (n2x.on()) {
//       DEBUG_STREAM.println("turning modem on");
//    }
    //if (!n2x.connect(apn, urat)) {
//    if (!n2x.connect("nb-iot.lmt.lv","0","24701", urat)) {
//       DEBUG_STREAM.println("FAILED TO CONNECT TO MODEM");
//    }
//    DEBUG_STREAM.println("On UDP Sending!");
//    sendMessageThroughUDP();
    
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
    
    digitalWrite(15, HIGH);   //Switch relay ON
    DEBUG_STREAM.println("Relay ON");

    delay(1000);
    
    digitalWrite(15, LOW);   //Switch relay OFF
    DEBUG_STREAM.println("Relay OFF");

    //sendMessageThroughUDP();
}
