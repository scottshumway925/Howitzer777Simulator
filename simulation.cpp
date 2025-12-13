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
   //gout << "Projectile Altitude: " << projectile.getPosition().getMetersY();
   //gout << "Projectile Position: " << projectile.getPosition().getMetersY();

   projectile.advance(1);

   if (hasFired)
   {
      flightTime++;
      projectile.draw(gout, flightTime);

      Position projectileLocation = projectile.getPosition();
      double x = projectileLocation.getMetersX();
      double y = projectileLocation.getMetersY();

      if (y <= ground.getElevationMeters(projectileLocation))
      {
         hasFired = false;

         double targetLocation = ground.getTarget().getMetersX();
         if (x > (targetLocation - 1000) && (x < targetLocation + 1000))
         {
            resetGame();
         }
      }
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
      if (!hasFired)
      {
         hasFired = true;
         flightTime = 0;
         Velocity muzzleVelocity;
         muzzleVelocity.set(howitzer.getElevation(), howitzer.getMuzzleVelocity());
         projectile.fire(howitzer.getElevation(), howitzer.getPosition(), muzzleVelocity);
      }
   }
}