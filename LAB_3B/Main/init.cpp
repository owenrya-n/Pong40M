// contains functions that simplify initialization in void setup for display
#include "init.h" //declaration of all pins so methods will work independently and can be called in other files
#define echoPin1 A5
#define echoPin2 1
#define trigPin1 A4
#define trigPin2 0
const byte ANODE_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void setPins()
// sets pinmodes of LEDS and Sensors
{
  pinMode(trigPin1, OUTPUT); // ultrasound sensor pin declarations-- these cannot immedediately be set to anything in setup as it will interfere with the measurement process
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  for (byte i = 0; i < 8; i++) // runs through all LED pins in a for loop, setting each LED to an output and the off state
  {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
}

void setBaud()
// begins serial communications
// usually unused but available for debugging
{
  Serial.begin(115200);
  Serial.setTimeout(100);
}

void startupanimation()
// cool startup animation that checks if leds are on
{
  for (int i = 0; i < 8; i++) // cycle through LEDS horizontally, turning all on with some delay between
  {
    digitalWrite(ANODE_PINS[i], LOW);
    digitalWrite(CATHODE_PINS[0], LOW);
    delay(50);
  }
  for (int i = 0; i < 8; i++) // cycle through LEDS vertically, turning all on with some delay between
  {
    digitalWrite(ANODE_PINS[0], LOW);
    digitalWrite(CATHODE_PINS[i], LOW);
    delay(50);
  }
  delay(100);                 // wait a bit to leave full display on
  for (int i = 0; i < 8; i++) // cycle through LEDS horizontally, turning all off with some delay between
  {
    {
      digitalWrite(ANODE_PINS[0], HIGH);
      digitalWrite(CATHODE_PINS[i], HIGH);
      delay(50);
    }
    for (int i = 0; i < 8; i++) // cycle through LEDS vertically, turning all off with some delay between
    {
      digitalWrite(ANODE_PINS[i], HIGH);
      digitalWrite(CATHODE_PINS[0], HIGH);
      delay(50);
    }
  }
