#include "main.h"
#include "robot.hpp"
#include "auton_programs.hpp"

 void autonomous(){

   pros::lcd::shutdown();

   /* ********** Blue Side ********** */

   //BlueBigClose();
   //BlueBigCorner();
   BlueSmall();

   /* ********** Red Side ********** */

   //RedBigClose();
   //RedBigCorner();
   //RedSmall();

   /* ********** Universal ********** */

   //Universal();

   /* ********** Skills ********** */

   //Skills();

   /* ********** Other ********** */

   //Nothing();
   //Test();

 }
