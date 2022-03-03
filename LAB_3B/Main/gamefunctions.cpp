// contains functions related to game mechanics and state detection
#include "gamefunctions.h"
const byte ANODE_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void goalanimation(int player, int player1score, int player2score)
// lights goal with player score
// dependent upon contactstate
{
    if (player == 4) // checking for player 2 using the output conditions of contact()
    {

        if (player1score <= 8) // if under max score
        {
            for (int i = 0; i < player1score; i++) // for each point scored
            {
                digitalWrite(ANODE_PINS[7], LOW); // turn LEDS on with some delay
                digitalWrite(CATHODE_PINS[i], LOW);
                delay(50); // delay between each LED to create building effect
            }
            delay(1000);                // wait a bit so LEDS stay on
            for (int i = 0; i < 8; i++) // sequentially turn off every LED
            {
                digitalWrite(ANODE_PINS[7], HIGH);
                digitalWrite(CATHODE_PINS[i], HIGH);
                delay(50); // delay to create slow removal effect
            }
        }
        else // if the player has already reached the max score play a single moving pixle animation to represent a win
        {
            for (int i = 0; i < 8; i++) // beginning of nested for loop to create movement effect
            {
                digitalWrite(ANODE_PINS[7], LOW); // turning all anodes low so only one pin has to be modified in nested loop
                for (int J = 0; J < 8; J++)
                {
                    digitalWrite(CATHODE_PINS[J], LOW);  // turn on led i
                    delay(100);                          // leave on for .1s
                    digitalWrite(CATHODE_PINS[J], HIGH); // turn off LED
                }
                digitalWrite(ANODE_PINS[7], HIGH); // set anode high to ensure other LEDS dont accidentally turn on
            }
        }
    }
    if (player == 3) // checking for player 1 using the output conditions of contact()
    {
        if (player2score <= 8) // if under max score
        {

            for (int i = 0; i < player2score; i++) // for each point scored
            {
                digitalWrite(ANODE_PINS[0], LOW); // turn LEDS on with some delay
                digitalWrite(CATHODE_PINS[i], LOW);
                delay(50); // delay between each LED to create building effect
            }
            delay(1000);                // wait a bit so LEDS stay on
            for (int i = 0; i < 8; i++) // sequentially turn off every LED
            {
                digitalWrite(ANODE_PINS[0], HIGH);
                digitalWrite(CATHODE_PINS[i], HIGH);
                delay(50); // delay to create slow removal effect
            }
        }
        else // if the player has already reached the max score play a single moving pixle animation to represent a win
        {
            for (int i = 0; i < 8; i++) // beginning of nested for loop to create movement effect
            {
                digitalWrite(ANODE_PINS[7], LOW); // turning all anodes low so only one pin has to be modified in nested loop
                for (int J = 0; J < 8; J++)
                {
                    digitalWrite(CATHODE_PINS[J], LOW);  // turn on led j
                    delay(100);                          // leave on for .1s
                    digitalWrite(CATHODE_PINS[J], HIGH); // turn off LED
                }
                digitalWrite(ANODE_PINS[7], HIGH); // set anode high to ensure other LEDS dont accidentally turn on
            }
        }
    }
}

int contact(int x, int y, int dstp1, int dstp2, const byte stsp[7]) // method to detect the collision of ball with paddle using distance from physical paddle and ball xy coordinates
// return 1 if player 1 collides return 2 if player 2 collides return 3 for p1 goal return 4 for p2 goal
{
    int p1pos; // declare the position of player 1 as an internal variable to be used later
    int p2pos; // declare the position of player 2 as an internal variable to be used later
    for (int i = 0; i < 7; i++)
    {
        if (dstp1 == stsp[i] || dstp1 + 1 == stsp[i] || dstp1 - 1 == stsp[i]) // uses the integer (refined) distance value from the paddle to decide which LED to set the paddle position to solely for comparison with ball position (uses +-1 to allow for corner shots/side paddle interactions)
        {
            p1pos = i; // set the position of paddle 1 to the appropriate index of the LED column
        }
    }
    for (int j = 0; j < 7; j++) // does the same as previous loop but for player 2
    {
        if (dstp2 == stsp[j] || dstp2 + 1 == stsp[j] || dstp2 - 1 == stsp[j])
        {
            p2pos = j; // set the position of paddle 2 to the appropriate index of the LED column
        }
    }
    if (p1pos == x && (y <= 0)) // if a goal has not been scored on player 1
    {
        return 1; // unused value of function for current game mechanics due to presense of display class logic but allows for further developement
    }
    if (p2pos == x && (y >= 7)) // if a goal has not been scored on player 2
    {
        return 2; // unused value of function for current game mechanics due to presense of display class logic but allows for further developement
    }
    if (!(p1pos == x || p1pos == x + 1 || p1pos == x - 1) && (y <= 0)) // if a goal has been scored on player 1
    {
        return 3; // goal 1 value
    }
    if (!(p2pos == x || p2pos == x + 1 || p2pos == x - 1) && (y >= 7)) // if a goal has been scored on player 2
    {
        return 4; // goal 2 value
    }

    else          // the ball has not reached the end of the screen
        return 0; // no goal/ contac value
}
