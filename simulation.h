/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "ground.h"


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) { ground = Ground(posUpperRight); }
   Howitzer getHowitzer() { return howitzer; }
   Ground getGround() { return ground; }
private:
   Howitzer howitzer;
   Ground ground;
};
