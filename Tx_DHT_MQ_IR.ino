#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7);
 #define DHTPIN 2

// Uncomment the type of sensor in use:
 #define DHTTYPE DHT11
int ir_val;
DHT_Unified dht(DHTPIN, DHTTYPE);

float mqVoltage; 
float mqValue;

void setup()
{
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
//    pinMode(13, OUTPUT);
//    pinMode(A0, INPUT);
//    digitalWrite(13, HIGH);
    int ir_val=digitalRead(4);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    Serial.begin(9600);
    mySerial.begin(9600);
  
//    dht.begin();
}

void loop()
{
    // Get Sensor data
    sensors_event_t tempEvent;
    sensors_event_t humEvent;
    
    dht.temperature().getEvent(&tempEvent);
    dht.humidity().getEvent(&humEvent);

    for(int i = 0; i < 100; i++){ 
      mqValue = mqValue + analogRead(0); // read analog input pin 0 
    }
    mqValue = mqValue / 100; // get average reading 
    mqVoltage = mqValue/1024*5.0; //convert to voltage 

        mySerial.print(ir_val);
        mySerial.print(":");
        mySerial.println(mqVoltage);
        Serial.println(mqVoltage);
        Serial.print(":");
        Serial.print(ir_val);


    // mySerial.println(mqVoltage);
//    Serial.println(digitalRead(3));
//    mySerial.println(digitalRead(3));
    delay(2000);
}
