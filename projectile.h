/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(46.7), radius(0.077545) {}

   void Reset()
   {
      mass = 46.7;
      radius = 0.077545;
      flightPath.clear();
   }

   void fire(Angle angle, Position &pos, Velocity muzzle)
   {
      const double gravity = -9.80665;
      double time = 1.0;
      double theta = angle.getDegrees() * M_PI / 180.0;
      double speed = muzzle.getSpeed();

      double initialVelocityX = speed * sin(theta);
      double initialVelocityY = speed * cos(theta);
      Velocity initialVelocity(initialVelocityX, initialVelocityY);

      Projectile::PositionVelocityTime pvt;
      pvt.pos = pos;
      pvt.v = initialVelocity;
      pvt.t = time;

      flightPath.push_back(pvt);
   }

   // advance the round forward until the next unit of time
   void advance(double simulationTime) 
   {
      if (flightPath.empty())
         return;

      const PositionVelocityTime& prev = flightPath.back();
      double dt = simulationTime - prev.t;
      if (dt <= 0.0) 
         dt = 1.0; 

      double x = prev.pos.getMetersX();
      double y = prev.pos.getMetersY();
      double velocityX = prev.v.getDX();
      double velocityY = prev.v.getDY();

      double accelerationX = 0.0;
      double accelerationY = 0.0;

      if (velocityX == 0.0 && velocityY == 0.0)
      {
         accelerationX = 0.0;
         accelerationY = -9.8064; 
      }
      else
      {
         double altitude = y;
         double gravity = -gravityFromAltitude(altitude);

         double speed = sqrt(velocityX * velocityX + velocityY * velocityY);
         double density = densityFromAltitude(altitude);
         double speedOfSound = speedSoundFromAltitude(altitude);
         double mach = speed / speedOfSound;
         double dragCoeff = dragFromMach(mach);

         double dragForce = forceFromDrag(density, dragCoeff, radius, speed);
         double dragAccel = accelerationFromForce(dragForce, mass);

         accelerationX = -(dragAccel * (velocityX / speed));
         accelerationY = -(dragAccel * (velocityY / speed)) + gravity;
      }

      double newVX = velocityX + accelerationX * dt;
      double newVY = velocityY + accelerationY * dt;

      double newX = x + velocityX * dt + 0.5 * accelerationX * dt * dt;
      double newY = y + velocityY * dt + 0.5 * accelerationY * dt * dt;

      PositionVelocityTime pvt;
      pvt.pos.setMetersX(newX);
      pvt.pos.setMetersY(newY);
      pvt.v.setDX(newVX);
      pvt.v.setDY(newVY);
      pvt.t = prev.t + dt;

      flightPath.push_back(pvt);

      if (flightPath.size() > 10)
         flightPath.pop_front();
   }

   void draw(ogstream& gout, double flightTime)
   {
      for (PositionVelocityTime& projectile : flightPath)
      {
         gout.drawProjectile(projectile.pos, flightTime - projectile.t);
      }
   }

   Position getPosition()
   {
      if (flightPath.size() == 0)
         return Position(0, 0);

      return flightPath.back().pos;
   }

   void RemoveProjectile()
   {
      int size = flightPath.size();
      for (int i = 0; i < size; i++)
         flightPath.pop_front();
   }

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
};