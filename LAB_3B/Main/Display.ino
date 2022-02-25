#include "init.h"
#include "rmplexer.h"
#include "gmplexer.h"
#include "gamefunctions.h"
#define echoPin1 A5
#define echoPin2 1
#define trigPin1 A4
#define trigPin2 0
const byte ANODE_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};
const byte settings[8] = {5, 9, 13, 17, 21, 25, 29, 33}; //reference values for histogram
//const byte settings[8] = {7, 10, 13, 16, 19, 22, 25, 28};
int d1;          //distance read from sensor 1
int d2;          //distance read from sensor 2
int clock = 300; //refresh rate for sensor
int sclock = 300;
int prev[2] = {4, 1};            //initial pos
unsigned long timescale = 100UL; //fps
unsigned long freq;              //fps multiplier
int dx = 1;                      //velocity wrt x
int dy = 1;                      //velocity wrt y
int timef = 0;                   //animation speed multiplier
int contactstate;                //paddle collision detector
int scorep1 = 3;                 // score player 1
int scorep2 = 4;                 //score player 2
void setup()
{
    setPins();
    startupanimation();
}

void loop()
{

    if (millis() - freq >= timescale)
    {
        freq = millis();
        contactstate = contact(prev[0], prev[1], d1, d2, settings);
        prev[0] = iteratex(prev[0], prev[1], dx, dy, 1);
        prev[1] = iteratey(prev[0], prev[1], dx, dy, 1);
        if (contactstate == 3)
        {
            goalanimation(3, scorep1, scorep2);
            delay(1000);
            prev[1] = rand() % 2 + 3;
            prev[0] = rand() % 7;
            dx = -dx;
            dy = -dy;
            timef++;
            scorep2++;
        }
        if (contactstate == 4)
        {
            goalanimation(4, scorep1, scorep2);
            delay(1000);
            prev[1] = rand() % 2 + 3;
            prev[0] = rand() % 7;
            dx = -dx;
            dy = -dy;
            timef++;
            scorep1++;
        }
        if ((prev[0] >= 7 || prev[0] <= 0) && !(contactstate == 3 || contactstate == 4))
        {
            dx = -dx;
        }
        if (prev[1] >= 7 || prev[1] <= 0)
        {
            dy = -dy;
        }
        d1 = ping(echoPin2, trigPin2, 2);
        d2 = ping(echoPin1, trigPin1, 2);
    }

    ramp(d1, 0, sclock, settings);
    ramp(d2, 7, sclock, settings);
    display(prev, clock);
}