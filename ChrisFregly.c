/*


Created by 
Jack Duryea
Shashank Mahesh
Andrew Giorgio

Project Chris Fregly


 The following sketch demonstrates a simple application of sensing 
 the moisture of the soil. You can determine whether a plant needs water 
 or not by observing the results that the sensor outputs.
 
 The circuit:
 * 4-Digit Display attached to Pin 38 and 39 (J14 plug on Grove Base BoosterPack)
 * Moisture Sensor attached to Pin 24 (J6 plug on Grove Base BoosterPack)
 
 * Note:  
 
 This example code is in the public domain.
 
 http://www.seeedstudio.com/depot/Grove-Moisture-Sensor-p-955.html

*/
//4-Digit Display library
#include "TM1637.h"
#include "DHT.h"

/* Macro Define */
#define CLK                 39          /* 4-Digit Display clock pin */
#define DIO                 38          /* 4-Digit Display data pin */

#define MOISTURE_PIN        24          /* pin of Moisture Sensor */
#define TEMP_HUMI_PIN       25                 /* pin of temperature&humidity sensor */

#define THRESHOLD_VALUE     300         /* threshold for watering the plant */
#define LED       RED_LED

/* Global Variables */
TM1637 tm1637(CLK, DIO);                  /* 4-Digit Display object */
DHT dht(TEMP_HUMI_PIN, DHT22);            /* temperature&humidity sensor object */

int m_analog_value = 0;                     /* variable to store the value coming from Moisture Sensor */
int8_t m_bits[4] = {0};                     /* array to store the single digits of the value */

int8_t t_bits[2] = {0};                   /* array to store the single bits of the temperature */
int8_t h_bits[2] = {0};                   /* array to store the single bits of the humidity */  


/* the setup() method runs once, when the sketch starts */
void setup() 
{
  Serial.begin(9600);
  /* Initialize 4-Digit Display */
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  dht.begin();                         /* initialize temperature humidity sensor */

  /* declare the LED pin as an OUTPUT */
  pinMode(LED, OUTPUT);  
}

/* the loop() method runs over and over again */
void loop() 
{
    m_analog_value = analogRead(MOISTURE_PIN);      /* read the value from the sensor */
    int _temperature = dht.readTemperature();             /* read the temperature value from the sensor */
//    int _humidity = dht.readHumidity();                   /* read the humidity value from the sensor */    
    Serial.println("Moisture");
    Serial.println(m_analog_value);
    Serial.println("Temp");
    Serial.println(_temperature);
//    Serial.println("Humidity" + _humidity);
    Serial.println("--------------");
    // /* if the value is smaller than threshold, turn on LED */
    // if(analog_value < THRESHOLD_VALUE) 
    // {
    //     digitalWrite(LED, HIGH);
    // } 
    // else 
    // {
    //     digitalWrite(LED, LOW);
    // }
    
    // memset(bits, 0, 4);                             /* reset array before we use it */
    // for(int i = 3; i >= 0; i--) 
    // {
    //     /* Convert the value to individual decimal digits for display */
    //     bits[i] = analog_value % 10;
    //     analog_value = analog_value / 10;  
    //     tm1637.display(i, bits[i]);                 /* display on 4-Digit Display */
    // }
    delay(500);  //small delay so that the number doesn't change too quickly to read
}