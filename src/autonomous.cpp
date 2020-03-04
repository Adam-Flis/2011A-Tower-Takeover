#include "main.h"
#include "auton_programs.hpp"
#include "define.hpp"
#include "voids.hpp"

 void autonomous(){

   while(IMU.is_calibrating()){}

   /* ********** Blue Side ********** */

   //BlueProtected();
   //BlueUnprotected();

   /* ********** Red Side ********** */

   //RedProtected();
   RedUnprotected();

   /* ********** Universal ********** */

  //Universal();

   /* ********** Skills ********** */

   //Skills();

 }
