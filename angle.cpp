/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Scott Shumway & Kaitlin Heusner
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#define TWO_PI 6.28318530718

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 * This method normalizes the radians of an angle to ensure it is within 0 and 2Pi.
 ************************************/
double Angle::normalize(double radians) const
{
	double normalizedRadians = std::fmod(radians, TWO_PI);

	if (normalizedRadians < 0)
		normalizedRadians += TWO_PI;

	return normalizedRadians;
}

/************************************
 * ANGLE : Convert To Degrees
 * This method converts the radians attribute to degrees and returns it.
 ************************************/
double Angle::convertToDegrees(double radians) const {
	double normalizedRadians = normalize(radians);

	double degrees;
	degrees = (normalizedRadians / TWO_PI) * 360.0;

	return degrees;
}

/************************************
 * ANGLE : Convert to Radians
 * This method takes in degrees as a parameter and converts those degrees to normalized radians.
 ************************************/
double Angle::convertToRadians(double degrees) const {
	double radians;
	radians = (degrees / 360.0) * (TWO_PI);
	radians = normalize(radians);

	return radians;
}

void Angle::reverse()
{
	radians += M_PI;
	radians = normalize(radians);
}

Angle& Angle::add(double delta)
{
	radians += delta;
	radians = normalize(radians);
	return *this;
}