// this is the main file, which is deployed to the arduino
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
const byte settings[8] = {5, 9, 13, 17, 21, 25, 29, 33}; // reference values for histogram
// const byte settings[8] = {7, 10, 13, 16, 19, 22, 25, 28};
int d1;                          // distance read from sensor 1
int d2;                          // distance read from sensor 2
int clock = 300;                 // refresh rate for display
int sclock = 300;                // refresh rate for sensor
int prev[2] = {4, 1};            // initial pos
unsigned long timescale = 130UL; // fps
unsigned long freq;              // fps multiplier
int dx = 1;                      // velocity wrt x
int dy = 1;                      // velocity wrt y
int timef = 0;                   // animation speed multiplier
int contactstate;                // paddle collision detector
int scorep1 = 1;                 // score player 1
int scorep2 = 1;                 // score player 2
void setup()
{
    setPins();          // sets pins
    startupanimation(); // cycles through every LED
}

void loop()
{

    if (millis() - freq >= timescale) // animation time controller
    {
        freq = millis();
        contactstate = contact(prev[0], prev[1], d1, d2, settings); // checks if contact with wall or paddles
        prev[0] = iteratex(prev[0], prev[1], dx, dy, 1);            // update pos of ball
        prev[1] = iteratey(prev[0], prev[1], dx, dy, 1);
        if (contactstate == 3) // if goal p1
        {
            goalanimation(3, scorep1, scorep2); // display score
            delay(1000);                        // leave animation playing for 1s
            prev[1] = rand() % 2 + 3;           // put ball somewhere random
            prev[0] = rand() % 7;
            dx = -dx;
            dy = -dy;
            timef++;   // for diagnostic stuff
            scorep2++; // increase player 2 score
        }
        if (contactstate == 4)
        {                                       // if goal p2
            goalanimation(4, scorep1, scorep2); //
            delay(1000);
            prev[1] = rand() % 2 + 3; // put ball somewhere random
            prev[0] = rand() % 7;
            dx = -dx;
            dy = -dy;
            timef++;
            scorep1++; // increase player 2 score
        }
        if ((prev[0] >= 7 || prev[0] <= 0) && !(contactstate == 3 || contactstate == 4)) // if ball reaches end of board and no goal has been scored
        {
            dx = -dx; // wall bounce
        }
        if (prev[1] >= 7 || prev[1] <= 0)
        {
            dy = -dy; // wall bounce
        }
        d1 = ping(echoPin2, trigPin2, 2); // sensor readout
        d2 = ping(echoPin1, trigPin1, 2);
    }

    ramp(d1, 0, sclock, settings); // paddle multiplexing
    ramp(d2, 7, sclock, settings);
    display(prev, clock); // ball multiplexing
}