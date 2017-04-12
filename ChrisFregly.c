/*

Created by 
Jack Duryea, Shashank Mahesh, Andrew Giorgio

Project name: Chris Fregly


*/

//4-Digit Display library
#include "TM1637.h"
#include "DHT.h"


// Display
#define CLK                 39   /* 4-Digit Display clock pin */
#define DIO                 38   /* 4-Digit Display data pin */

// Moisture
#define MOISTURE_PIN        24   /* pin of Moisture Sensor */

// Temp/Hum
#define TEMP_HUMI_PIN       25   /* pin of temperature&humidity sensor */

// Light
#define LIGHT_SENSOR        27   /* pin connected to the Light Sensor */

// Buzzer
#define BUZZER_PIN          40   /* pin connected to the buzzer */


// Threshholds
#define THRESHOLD_VALUE     300   /* threshold for watering the plant */

/* Global Variables */
TM1637 tm1637(CLK, DIO);          /* 4-Digit Display object */
DHT dht(TEMP_HUMI_PIN, DHT22);    /* temperature&humidity sensor object */

// Values from sensors, default to 0
int moisture = 0;                 
int temperature = 0;
int humidity = 0;
int light = 0;

// Definitions of notes and their respective tone frequencies
char names[] = { 'c', 'd',   'e', 'f',  'g',   'a',  'b', 'C', 'D', 'E', 'F','G','A' };
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 853, 805, 718, 683, 613.5 };


/* Variables for buzzer music */
int glob_len = 24;         // the number of notes
char glob_notes[] = "gebbbbgebbbbagaaaaabbAG"; //notes in the song
int glob_beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2,1,1,1,1,1,1,1,1, 2,1 }; //length of each note
int glob_tempo = 200;

/* the setup() method runs once, when the sketch starts */
void setup() 
{
  // Set baud rate
  Serial.begin(9600);
  /* Initialize 4-Digit Display */
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);

  /* Initialize 4-Digit Display */
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin(); // initialize temperature humidity sensor

}

/* the loop() method runs over and over again */
void loop() 
{
    // Read sensor values
    moisture = analogRead(MOISTURE_PIN);      /* read the value from the sensor */
    temperature = dht.readTemperature();             /* read the temperature value from the sensor */
    humidity = dht.readHumidity();                   /* read the humidity value from the sensor */    
    light = analogRead(LIGHT_SENSOR);        /* read the value from the sensor */

    // Print sensor values to the console
    Serial.println("Moisture");
    Serial.println(moisture);
    Serial.println("Temp");
    Serial.println(temperature);
    Serial.println("Humidity" );
    Serial.println(humidity);
    Serial.println("light" );
    Serial.println(light);
    Serial.println("--------------");

    // IF moisture is less than 100 this is bad
    int mBit = 0;
    if ((moisture < 100)){
      mBit = 1;
      playMusic(glob_len, glob_notes, glob_beats, glob_tempo); // Play alert song

    }
    
    
    // If temperature is less than 16 or more than 27 C, this is bad
    int tBit = 0;
    if ((temperature < 16) || (temperature > 27)){
      tBit = 1;
    }

     // If humidity is less than 50 or more than 100, this is bad
    int hBit = 0;
    if ((humidity < 50) || (humidity > 100)){
      hBit = 1;
    }

     // If light is less than 1000, this is bad
    int lBit = 0;
    if (light < 500){
      lBit = 1;
    }

    // Set display values
    tm1637.display(0, mBit);
    tm1637.display(1, tBit);
    tm1637.display(2, hBit);
    tm1637.display(3, lBit);
    
    delay(500);  //small delay so that the number doesn't change too quickly to read
}


/* Play the alert song */
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
  // Play a tone for a certain amount of time
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
  {
    // Write the buzzer pin to high and then delay and then back down to low
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
}

/* Play a particular note */
void playNote(char note, int duration) 
{ 
  // play the tone corresponding to the note name
  for (int i = 0; i < 13; i++) 
  {
    if (names[i] == note) 
    {
      playTone(tones[i], duration);
    }
  }
}
