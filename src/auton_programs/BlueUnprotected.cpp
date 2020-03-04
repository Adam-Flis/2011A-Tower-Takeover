#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 8 cubes from the field
//Places cubes into the unprotected scoring
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
  delay(475);
  intakeStop();
  drive("b", 10.7, 250, 0.86);
  delay(20);

  //Turn and drive at 2nd line
  drive("l", 50, 200, 0.45);
  delay(20);
  drive("b", 36.5, 250, 1.48);
  delay(20);
  drive("r", 39, 200, 0.33);
  delay(20);

  //Grab next 2 cubes
  intakeMove(200);
  drive("f", 24, 107, 2.1, false);

  //Turn and drive at scoring zone
  intakeStop();
  arm.move_velocity(0);
  delay(70);
  drive("l", 100, 135, 1.75);
  angler.move_voltage(8100);
  drive("f", 34.85, 180, 2.427, false);

  //Score cubes
  driveMove("right", 40);
  anglerStack(1.0);
  driveStop();
  intakeMove(-200);
  delay(150);
  drive("b", 12, 250, 1.0);
}
