#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 8 cubes from the field
//Places cubes into the unprotected scoring zone
//Points scored: 8
void BlueUnprotected(){

  //Auton start things
  driveMove("both", -15);
  unfold();
  delay(50);
  driveStop();
  intakeMove(200);
  arm.move_velocity(-5);

  //Grab line of cubes: 6 total
  drive("f", 54.7, 85, 4.09);
  delay(100);
  intakeMove(100);
  drive("b", 10, 250, 0.8);
  intakeStop();
  delay(20);

  //Turn and drive at 2nd line
  drive("l", 42, 210, 0.35);
  delay(20);
  drive("b", 37.5, 250, 1.5);
  delay(20);
  drive("r", 40, 210, 0.35);
  delay(20);

  //Grab next 2 cubes
  intakeMove(200);
  drive("f", 23.5, 105, 2.13, false);

  //Turn and drive at scoring zone
  delay(80);
  intakeStop();
  arm.move_velocity(0);
  drive("l", 97, 125, 1.8);
  angler.move_voltage(8075);
  drive("f", 36, 185, 2.44, false);

  //Score cubes
  driveMove("both", 50);
  anglerStack(1.0);
  driveStop();
  intakeMove(-200);
  delay(150);
  drive("b", 12, 250, 1.0);
}
