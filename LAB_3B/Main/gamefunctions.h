// header file containing prototype methods which are identical of those in gamefunctions.cpp
#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
#include <Arduino.h>

void showscore(int scorep1, int scorep2);
int contact(int x, int y, int dstp1, int dstp2, const byte stsp[7]);
void goalanimation(int player, int player1score, int player2score);
#endif