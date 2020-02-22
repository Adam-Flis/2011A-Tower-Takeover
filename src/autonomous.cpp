#include "main.h"
#include "auton_programs.hpp"
#include "define.hpp"
#include "voids.hpp"

 void autonomous(){

   while(IMU.is_calibrating()){}

   /* ********** Blue Side ********** */

   //BlueBig();
   //BlueSmall();

   /* ********** Red Side ********** */

   //RedBig();
   //RedSmall();

   /* ********** Universal ********** */

  //Universal();

   /* ********** Skills ********** */

   Skills();

 }
