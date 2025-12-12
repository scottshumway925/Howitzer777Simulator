/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Scott Shumway
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION


 /*********************************************
 * Reset Game
 * Resets the position of the howitzer, ground, and target
 *********************************************/
void Simulator::resetGame()
{
   howitzer.generatePosition(posUpperRight);
   ground.reset(howitzer.getPosition());
}

void Simulator::update(const Interface* pUI, void* p)
{
   Simulator* pSimulator = (Simulator*)p;

   ogstream gout;
   howitzer.draw(gout, flightTime);
   ground.draw(gout);

   if (hasFired)
   {
      flightTime++;
      projectile.advance(1);
      projectile.draw(gout);
   }

   if (pUI->isLeft())
   {
      howitzer.rotate(-.03);
   }

   if (pUI->isRight())
   {
      howitzer.rotate(.03);
   }

   if (pUI->isDown())
   {
      howitzer.raise(-.01);
   }

   if (pUI->isUp())
   {
      howitzer.raise(.01);
   }

   if (pUI->isQ())
   {
      resetGame();
   }

   if (pUI->isSpace())
   {
      hasFired = true;
      flightTime = 0;
      Velocity muzzleVelocity;
      muzzleVelocity.set(howitzer.getElevation(), howitzer.getMuzzleVelocity());
      projectile.fire(howitzer.getElevation(), howitzer.getPosition(), muzzleVelocity);
   }
}