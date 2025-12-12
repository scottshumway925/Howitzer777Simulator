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
   howitzer.draw(gout, 1);
   ground.draw(gout);


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
}