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

   gout.setPosition(Position(23000, 19000));
   gout << "Altitude: " << round(projectile.getPosition().getMetersY()) << "m";
   gout.setPosition(Position(23000, 18000));
   gout << "Position: " << round(projectile.getPosition().getMetersX()) << "m";
   gout.setPosition(Position(23000, 17000));
   gout << "Target: " << round(ground.getTarget().getMetersX()) << "m";
   gout.setPosition(Position(23000, 16000));
   gout << "Flight Time: " << (hasFired? round(flightTime) : 0) << "s";
   gout.setPosition(Position(23000, 15000));
   gout << "Angle: " << round(howitzer.getElevation().getDegrees()) << " degrees";

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
         projectile.RemoveProjectile();

         double targetLocation = ground.getTarget().getMetersX();
         if (x > (targetLocation - 500) && (x < targetLocation + 500))
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