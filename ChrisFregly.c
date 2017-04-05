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

// Display
#define CLK                 39          /* 4-Digit Display clock pin */
#define DIO                 38          /* 4-Digit Display data pin */

// Moisture
#define MOISTURE_PIN        24          /* pin of Moisture Sensor */

// Temp/Hum
#define TEMP_HUMI_PIN       25                 /* pin of temperature&humidity sensor */

// Light
#define LIGHT_SENSOR      27                 /* pin connected to the Light Sensor */

// Buzzer
#define BUZZER_PIN 40


// Threshholds
#define THRESHOLD_VALUE     300         /* threshold for watering the plant */

/* Global Variables */
TM1637 tm1637(CLK, DIO);                  /* 4-Digit Display object */
DHT dht(TEMP_HUMI_PIN, DHT22);            /* temperature&humidity sensor object */

// Values from sensors
int moisture = 0;                     /* variable to store the value coming from Moisture Sensor */
int temperature = 0;
int humidity = 0;
int light = 0;

// Values for display
int8_t m_bits[4] = {0};                     /* array to store the single digits of the value */


/* Variables for buzzer music */
int glob_len = 15;         /* the number of notes */
char glob_notes[] = "ccggaagffeeddc "; //notes in the song
int glob_beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }; //length of each note
int glob_tempo = 200;

/* the setup() method runs once, when the sketch starts */
void setup() 
{
  Serial.begin(9600);
  /* Initialize 4-Digit Display */
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  dht.begin();                         /* initialize temperature humidity sensor */

}

/* the loop() method runs over and over again */
void loop() 
{
    moisture = analogRead(MOISTURE_PIN);      /* read the value from the sensor */
    temperature = dht.readTemperature();             /* read the temperature value from the sensor */
    humidity = dht.readHumidity();                   /* read the humidity value from the sensor */    
    light = analogRead(LIGHT_SENSOR);        /* read the value from the sensor */

    Serial.println("Moisture");
    Serial.println(moisture);
    Serial.println("Temp");
    Serial.println(temperature);
    Serial.println("Humidity" );
    Serial.println(humidity);
    Serial.println("light" );
    Serial.println(light);
    Serial.println("--------------");

    // IF moisture is less than 300 or more than 700, this is bad
    if ((moisture <= 300) || (moisture >= 700)){
      //playMusic(glob_len, glob_notes, glob_beats, glob_tempo);
    }
    
     memset(m_bits, 0, 4);                             /* reset array before we use it */
     for(int i = 3; i >= 0; i--) 
     {
         /* Convert the value to individual decimal digits for display */
         m_bits[i] = moisture % 10;
         moisture = moisture / 10;  
         tm1637.display(i, m_bits[i]);                 /* display on 4-Digit Display */
     }
     
    delay(500);  //small delay so that the number doesn't change too quickly to read
}

void playMusic(int len, char notes[], int beats[], int tempo){

for(int i = 0; i < len; i++) 
  {
    //space indicates a pause
    if(notes[i] == ' ') 
    {
      delay(beats[i] * tempo);
    } 
    else 
    {
      playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2);    /* delay between notes */
  }

}
  
/* play tone */
void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
}

char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

void playNote(char note, int duration) 
{
  
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) 
  {
    if (names[i] == note) 
    {
      playTone(tones[i], duration);
    }
  }
}
