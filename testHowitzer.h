/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/


#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "howitzer.h"
#include "unitTest.h"

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the Howitzer unit tests
 ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();

      report("Howitzer");
   }

private:
   double metersFromPixels = -1.0;

   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    DEFAULT CONSTRUCTOR
     * input:   nothing
     * output:  zeros (except angle is at 45 degrees, 
     *                 and the muzzle velocity is correct)
     *********************************************/
   void defaultConstructor()
   {
      // setup

      // excersize
      Howitzer howitzer = Howitzer();

      // Verify
      assertEquals(howitzer.position.x, 0);
      assertEquals(howitzer.position.y, 0);
      assertEquals(howitzer.elevation.getDegrees(), 45);
      assertEquals(howitzer.muzzleVelocity, 827.0);

      // Teardown
   }

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
   void getPosition_zero()
   {
      // setup
      Howitzer howitzer;
      Position testPos = Position(0, 0);
      howitzer.position.x = 0;
      howitzer.position.y = 0;

      // excersize
      Position howPos = howitzer.getPosition();

      // Verify
      assertEquals(howPos.x, testPos.x);
      assertEquals(howPos.y, howPos.x);

      // Teardown
   }

   /*********************************************
    * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {
      // setup
      Howitzer howitzer;
      Position testPos = Position(123.4, 567.8);
      howitzer.position.x = 123.4;
      howitzer.position.y = 567.8;

      // excersize
      Position howPos = howitzer.getPosition();

      // Verify
      assertEquals(howPos.x, testPos.x);
      assertEquals(howPos.y, howPos.y);

      // Teardown
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {
      // setup
      Howitzer howitzer;
      howitzer.muzzleVelocity = 24.68;

      // excersize
      double muzVel = howitzer.getMuzzleVelocity();

      // Verify
      assertEquals(muzVel, 24.68);

      // Teardown
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {
      // setup
      Howitzer howitzer;
      howitzer.muzzleVelocity = 827.00;

      // excersize
      double muzVel = howitzer.getMuzzleVelocity();

      // Verify
      assertEquals(muzVel, 827);

      // Teardown
   }

   /*********************************************
    * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
    *********************************************/
   void getElevation_up()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.setDegrees(0);

      // excersize
      Angle el = howitzer.getElevation();
      double degrees = el.getDegrees();

      // Verify
      assertEquals(degrees, 0);

      // Teardown
   }

   /*********************************************
    * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.setDegrees(0.4);

      // excersize
      Angle el = howitzer.getElevation();
      double degrees = el.getDegrees();

      // Verify
      assertEquals(degrees, 0.4);

      // Teardown
   }

   /*********************************************
    * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.setDegrees(5.8);

      // excersize
      Angle el = howitzer.getElevation();
      double degrees = el.getDegrees();

      // Verify
      assertEquals(degrees, 5.8);

      // Teardown
   }

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  1px <= x <= 9px
     *********************************************/
   void generatePosition_small()
   {
      // setup
      Howitzer howitzer;
      Position pos = Position(0, 0);

      // excersize
      howitzer.generatePosition(pos);

      // Verify
      bool isGood = (1 <= howitzer.position.x <= 9);
      assertEquals(isGood, true);

      // Teardown
   }

    /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  100px <= x <= 900px
    *********************************************/
   void generatePosition_large()
   {
      // setup
      Howitzer howitzer;
      Position pos = Position(1000, 1000);

      // excersize
      howitzer.generatePosition(pos);

      // Verify
      bool isGood = (100 <= howitzer.position.x <= 900);
      assertEquals(isGood, true);

      // Teardown
   }

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = 0.5;

      // excersize
      howitzer.raise(-0.1);

      // Verify
      assertEquals(howitzer.elevation.radians, 0.6);

      // Teardown
   }

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = 0.5;

      // excersize
      howitzer.raise(0.1);

      // Verify
      assertEquals(howitzer.elevation.radians, 0.4);

      // Teardown
   }

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
   void raise_leftDown()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = -0.5;

      // excersize
      howitzer.raise(-0.1);

      // Verify
      assertEquals(howitzer.elevation.radians, (M_PI * 2) - 0.6);

      // Teardown
   }

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_leftUp()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = -0.5;

      // excersize
      howitzer.raise(0.1);

      // Verify
      assertEquals(howitzer.elevation.radians, (M_PI * 2) - 0.4);

      // Teardown
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = 1.23;

      // excersize
      howitzer.rotate(.3);

      // Verify
      assertEquals(howitzer.elevation.radians, 1.53);

      // Teardown
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = 1.23;

      // excersize
      howitzer.rotate(-.3);

      // Verify
      assertEquals(howitzer.elevation.radians, .93);

      // Teardown
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
    * output:  h.elevation=.1
    *********************************************/
   void rotate_wrapClock()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = (M_PI * 2) -0.1;

      // excersize
      howitzer.rotate(.2);

      // Verify
      assertEquals(howitzer.elevation.radians, .1);

      // Teardown
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI
    * output:  h.elevation=6.1 (2pi + -0.1)
    *********************************************/
   void rotate_wrapCounterClock()
   {
      // setup
      Howitzer howitzer;
      howitzer.elevation.radians = 0.1;

      // excersize
      howitzer.rotate(-.2 - (M_PI * 4));

      // Verify
      assertEquals(howitzer.elevation.radians, (M_PI * 2) + -0.1);

      // Teardown
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};