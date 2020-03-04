#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 4 cubes from the field
//Places cubes into the protected scoring zone
//Points scored: 4
void RedProtected(){

  //Auton start things
  driveMove("both", -15);
  //unfold();
  angler.move_voltage(12000);
  delay(150);
  angler.move_voltage(-12000);
  delay(250);
  angler.move_velocity(0);
  driveStop();
  intakeMove(200);
  arm.move_velocity(-5);

  //Drive at 1st & 2nd cube
  drive("f", 18, 220, 1.3);
  delay(200);
  intakeMove(100);

  //Turn and get 3rd and 4th cube
  drive("r", 85, 160, 1.3);
  delay(100);
  intakeMove(200);
  drive("f", 29, 130, 2.3);
  delay(300);

  //Drive away from cube and go to scoring zone
  intakeMove(100);
  drive("b", 20, 220, 2.0);
  intakeMove(0);
  delay(250);
  drive("r", 160, 170, 2.0);

  //Go to stack cubes
  LFD.set_voltage_limit(5000);
  LBD.set_voltage_limit(5000);
  delay(100);
  intakeMove(-35);
  drive("f", 11.5, 120, 1.2);
  LFD.set_voltage_limit(12000);
  LBD.set_voltage_limit(12000);

  //Stack cubes and drive away
  anglerStack(2.3);
  driveMove("both", -250);
  delay(500);
  driveStop();
  intakeMove(0);
  anglerHome(2.0);

}
