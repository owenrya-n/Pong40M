// contains functions that generate sensor data and display its
#include "rmplexer.H"
const byte ANODE_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};
long duration1;
long duration2;
int distance1;
int distance2;
int echopin;
int trigpin;
int duration;
int distance;
void blink(int row, int column, int delay) // turns on 3 LEDS centered at the row value in the same column (used for displaying paddle locations)
// paddle interface display
{
    digitalWrite(CATHODE_PINS[row], LOW);
    digitalWrite(ANODE_PINS[column], LOW); // if there is still space to display the top LED
    if (row + 1 <= 7)
        digitalWrite(CATHODE_PINS[row + 1], LOW); // display an LED 1 unit above the paddle's true pos
    if (row - 1 >= 0)
        digitalWrite(CATHODE_PINS[row - 1], LOW); // if there is still space to display the bottom  LED
    delayMicroseconds(delay);                     // leave on for some small ammount of time
    digitalWrite(CATHODE_PINS[row], HIGH);        // turning all possible LEDS off
    digitalWrite(ANODE_PINS[column], HIGH);
    digitalWrite(CATHODE_PINS[row + 1], HIGH);
    digitalWrite(CATHODE_PINS[row - 1], HIGH);
}

void ramp(int dst, int row, int delay, const byte stsp[8])
// Parses data from sensors using array and displays paddle
{
    for (int i = 0; i < 7; i++) // for every LED in a collumn
    {
        if (dst < stsp[i + 1] && dst >= stsp[i]) // if the distance to the sensor is in between the value of the prior and next ints in the settings array
        {
            blink(i, row, delay); // display a paddle at the derived row in the appropriate collumn
        }
        if (dst < stsp[0]) // if the paddle is too close
        {
            blink(0, row, delay); // display the paddle as at the first position
        }
        if (dst > stsp[7]) // if the paddle is too far
        {
            blink(7, row, delay); // display the paddle at the last position
        }
    }
}

int ping(int echopin, int trigpin, int time)
// calculates distance to the nearest object
{
    digitalWrite(trigpin, HIGH);       // turn on the ultrasound coil
    delayMicroseconds(time);           // send out a pulse time microseconds long
    digitalWrite(trigpin, LOW);        // stop the pulse
    duration = pulseIn(echopin, HIGH); // count seconds until reciever coil sends back a high signal
    distance = duration * 0.034 / 2;   // calculate the distance using the speed of sound, accounting for the fact that the sound must travel twice the paddle dist
    return distance;
}
