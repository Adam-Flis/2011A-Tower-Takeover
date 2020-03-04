#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 10 cubes from the field and sets 3 cubes in challices
//Points scored: 30
void Skills(){

  //Auton start things
  driveMove("both", -15);
  unfold();
  driveStop();
  intakeMove(200);
  arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  delay(100);

  //Intake first line of cube
  drive("f", 135, 80, 12.0);
  drive("b", 12, 100, 1.0);
  intakeMove(100);
  delay(200);
  arm.set_brake_mode(MOTOR_BRAKE_BRAKE);

  //Go to scoring zone
  drive("r", 45, 100, 2.0);
  delay(200);
  intakeMove(-10);
  drive("f", 19, 100, 2.2);
  anglerStack(2.7);
  intakeMove(-200);
  delay(100);

  //Drive out of scoring zone a align on wall
  driveMove("both", -100);
  delay(700);
  intakeStop();
  driveStop();
  anglerHome(2.2);
  drive("l", 45, 120, 1.5);
  armUp(lowChalice, 200, 2.0);
  drive("f", 24, 120, 3.0);

  //Drive away from wall
  driveMove("both", -100);
  delay(500);
  driveStop();
  delay(100);
  armDown(armHome, 200, 1.5);

  //Turn and get medium chalice cube
  drive("l", 90, 120, 2.0);
  delay(50);
  intakeMove(200);
  drive("f", 26.5, 160, 2.5);
  intakeMove(-200);
  delay(200);
  intakeStop();

  //Score cube in medium chalice
  driveMove("both", -100);
  delay(230);
  driveStop();
  delay(100);
  armUp(mediumChalice, 200, 2.5);
  drive("f", 5, 100, 1.0);
  intakeMove(-200);
  delay(800);
  intakeStop();

  //Drive away from medium chalice pt2
  drive("b", 18, 130, 2.0);
  armDown(armHome, 200, 2.0);
  delay(100);
  intakeStop();

}
