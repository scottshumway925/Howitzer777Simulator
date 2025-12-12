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
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSimulator = (Simulator*)p;

   ogstream gout;

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