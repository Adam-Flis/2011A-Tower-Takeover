#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 4 cubes from the field
//Places cubes into the protected scoring zone
//Points scored: 4
void RedProtected(){

  //Auton start things
  driveMove("both", -15);
  unfold();
  angler.move_voltage(12000);
  delay(150);
  angler.move_voltage(-12000);
  delay(250);
  angler.move_velocity(0);
  driveStop();
  intakeMove(200);
  arm.move_velocity(-5);

  //Drive at 1st & 2nd cube
  drive("f", 22, 170, 1.2);
  intakeStop();
  delay(20);

  //Turn and get 3rd and 4th cube
  drive("r", 92, 160, 1.1);
  delay(20);
  intakeMove(150);
  drive("f", 24.5, 110, 1.8);
  delay(300);

  //Turn and get 5th cube
  intakeStop();
  drive("r", 22, 100, 0.5);
  delay(20);
  intakeMove(200);
  drive("f", 13, 100, 1.0);
  delay(350);

  //Drive away from cube turn at scoring zone
  intakeStop();
  drive("b", 20, 220, 1.0);
  delay(20);
  drive("r", 135, 200, 1.5);

  //Drive at scoring zone and score cubes
  drive("f", 18, 150, 0.9);
  anglerStack(2.0);
  intakeMove(-200);
  delay(150);
  drive("b", 12, 250, 1.0);
  intakeStop();

}
