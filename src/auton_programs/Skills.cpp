#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 10 cubes from the field and sets 2 cubes in challices
//Points scored: 30
void Skills(){

  //Auton start things
  driveMove("both", -15);
  unfold();
  angler.move_voltage(-12000);
  intakeMove(200);
  delay(70);
  driveStop();
  arm.move_velocity(-5);
  angler.move_voltage(-1000);

  //Intake first line of cube
  drive("f", 135, 80, 12.0);
  angler.move_velocity(0);
  drive("b", 12, 100, 1.0);
  intakeMove(100);
  delay(200);
  arm.move_velocity(0);

  //Go to scoring zone
  drive("r", 43, 100, 2.0);
  delay(200);
  intakeMove(-10);
  drive("f", 18, 100, 1.7);
  anglerStack(2.7);
  intakeMove(-200);
  delay(150);

  //Drive out of scoring zone a align on wall
  drive("b", 13, 200, 1.5);
  intakeStop();
  anglerHome(2.2);
  drive("l", 43, 120, 1.5);
  armUp(smallChalice, 200, 2.0);
  drive("f", 24, 120, 2.5);

  //Drive away from wall
  drive("b", 12, 200, 0.8);
  delay(50);
  armDown(armHome, 200, 1.5);

  //Turn and get medium chalice cube
  drive("l", 90, 120, 2.0);
  delay(50);
  intakeMove(200);
  drive("f", 28, 160, 2.8);

  //Score cube in medium chalice
  drive("b", 7, 100, 1.3);
  intakeMove(-200);
  delay(450);
  intakeStop();
  armUp(mediumChalice, 200, 2.5);
  drive("f", 9, 100, 1.5);
  intakeMove(-200);
  delay(800);
  intakeStop();

  //Drive away from medium chalice pt2
  drive("b", 17, 120, 2.2);
  delay(100);
  intakeStop();

  //Turn and get small chalice cube
  drive("l", 90, 130, 1.5);
  delay(50);
  armDown(armHome, 200, 2.0);
  intakeMove(200);
  drive("f", 30, 180, 2.2);
  delay(50);

  //Score cube in small chalice
  drive("b", 9, 100, 1.4);
  intakeMove(-200);
  delay(450);
  intakeStop();
  armUp(smallChalice, 200, 2.5);
  drive("f", 2, 100, 0.5);
  intakeMove(-200);
  delay(800);
  intakeStop();
  
}
