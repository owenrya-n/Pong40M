// contains basic functions used to construct the visual elements of the display
#include "gmplexer.h"

const byte ANODE_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13}; // declaration of anode and cathode pins so methods will work independently and can be called in other files
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void display(int pos[2], int delay)
// general display function for a single LED with position array and delay int input
{
    digitalWrite(CATHODE_PINS[pos[0]], LOW); // turn LED at array position on
    digitalWrite(ANODE_PINS[pos[1]], LOW);
    delayMicroseconds(delay);                 // wait a bit
    digitalWrite(CATHODE_PINS[pos[0]], HIGH); // turn LED off
    digitalWrite(ANODE_PINS[pos[1]], HIGH);
}

int iteratex(int x, int y, int xp, int yp, int t)
// should return x and ypos with time inc
{
    x = x + t * xp; // xf=x0+vxt+.5axt^2
    return x;
}

int iteratey(int x, int y, int xp, int yp, int t)
// should return x and ypos with time inc
{
    y = y + t * yp; // yf=y0+vyt+ayt^2
    return y;
}