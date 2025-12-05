/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Scott Shumway & Kaitlin Heusner
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   // Constructors
   Angle() : radians(9.9) { radians = 0; }
   Angle(const Angle& rhs) : radians(9.9) { this->radians = rhs.getRadians(); }
   Angle(double degrees) : radians(9.9) { this->radians = convertToRadians(degrees); }

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dy = cos a
   // dx = sin a
   double getDx() const { return sin(radians); }
   double getDy() const { return cos(radians); }
   bool   isRight()          const { if (convertToDegrees(radians) <= 180) return true; else return false; }
   bool   isLeft()           const { if (convertToDegrees(radians) > 180) return true; else return false; }


   // Setters
   void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp() { radians = convertToRadians(0); }
   void setDown() { radians = convertToRadians(180); }
   void setRight() { radians = convertToRadians(90); }
   void setLeft() { radians = convertToRadians(270); }
   void reverse();
   Angle& add(double delta);

   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   void setDxDy(double dx, double dy) { radians = normalize(atan2(dx, dy)); }
   Angle operator+(double degrees) const { return Angle(); }

private:
   double convertToRadians(double degrees) const;
   double convertToDegrees(double radians) const;
   double normalize(double radians) const;
   double radians;   // 360 degrees equals 2 PI radians
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}