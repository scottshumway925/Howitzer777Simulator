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
#include "uiInteract.h"


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) : posUpperRight(posUpperRight) { ground = Ground(posUpperRight); }
   Position posUpperRight;
   Howitzer getHowitzer() { return howitzer; }
   Ground getGround() { return ground; }
   void resetGame();
   void update(const Interface* pUI, void* p);

private:
   Howitzer howitzer;
   Ground ground;
};
