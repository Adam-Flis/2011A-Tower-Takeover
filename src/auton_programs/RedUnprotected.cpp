#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 8 cubes from the field
//Places cubes into the unprotected scoring zone
//Points scored: 8
void RedUnprotected(){

  //Auton start things
  driveMove("both", -15);
  unfold();
  angler.move_voltage(-12000);
  intakeMove(200);
  delay(70);
  driveStop();
  arm.move_velocity(-5);
  angler.move_voltage(-1000);

  //Grab line of cubes: 6 total
  drive("f", 55.5, 90, 4.0);
  delay(100);
  intakeMove(175);
  drive("b", 11.5, 250, 0.9);
  intakeStop();
  angler.move_velocity(0);

  //Turn and drive at 2nd line
  drive("r", 38, 180, 0.33);
  drive("b", 36, 220, 1.7);
  drive("l", 35, 180, 0.33);

  //Grab next 2 cubes
  intakeMove(160);
  drive("f", 20, 95, 1.75, false);

  //Turn and drive at scoring zone
  delay(80);
  intakeStop();
  arm.move_velocity(0);
  drive("r", 98, 135, 1.8);
  angler.move_voltage(8075);
  drive("f", 36.5, 190, 2.45, false);

  //Score cubes
  driveMove("both", 70);
  delay(60);
  anglerStack(1.0);
  driveStop();
  intakeMove(-200);
  delay(150);
  drive("b", 12, 250, 1.0);

}
