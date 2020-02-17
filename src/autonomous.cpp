#include "main.h"
#include "auton_programs.hpp"
#include "define.hpp"
#include "voids.hpp"

 void autonomous(){

   delay(2000);
   drive("f", 24, 250, 10.0);
   intakeMove(200);

   /* ********** Blue Side ********** */

   //BlueBig();
   //BlueSmall();

   /* ********** Red Side ********** */

   //RedBig();
   //RedSmall();

   /* ********** Universal ********** */

  //Universal();

   /* ********** Skills ********** */

   //Skills();

 }
