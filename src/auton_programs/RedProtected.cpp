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
  angler.move_voltage(-12000);
  intakeMove(200);
  delay(70);
  driveStop();
  arm.move_velocity(-5);
  angler.move_voltage(-1000);

  //Drive at 1st cube
  drive("f", 22, 170, 1.2);
  intakeStop();
  angler.move_velocity(0);
  delay(20);

  //Turn and get 2nd and 3rd cube
  drive("r", 92, 160, 1.1);
  delay(20);
  intakeMove(150);
  drive("f", 24.5, 110, 1.8);
  delay(300);

  //Drive away from cube turn at scoring zone
  intakeStop();
  drive("b", 20, 220, 1.0);
  delay(20);
  drive("r", 200, 200, 2.0);

  //Drive at scoring zone and score cubes
  drive("f", 18, 150, 0.9);
  anglerStack(2.0);
  intakeMove(-200);
  delay(150);
  drive("b", 12, 250, 1.0);
  intakeStop();

}
