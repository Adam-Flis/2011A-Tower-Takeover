#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void BlueSmall(){

  //Auton start things
  int Stack = timeOut(secondsToMillis(13.0));
  driveMove("both", -15);
  unfold();
  driveStop();
  intakeMove(200);
  arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  delay(100);

  //Grab line of cubes: 5 total
  drive("f", 39, 90, 3.5);
  delay(200);
  intakeMove(100);

  //Drive away from line and turn at 6th cube
  drive("r", 25, 180, 1.0);
  intakeMove(200);
  drive("f", 9.5, 200, 1.2);
  delay(100);

  //Drive away 6th cube
  driveMove("both", -100);
  delay(250);
  intakeStop();
  delay(250);
  driveStop();
  delay(100);

  //Turn and drive at scoing zone
  drive("r", 180, 180, 2.7);
  intakeMove(-15);
  drive("f", 19.8, 135, 2.3);
  driveMove("right", 140);
  delay(600);
  driveStop();

  //Stack cubes and drive away
  //Makes sure we have the time to stack
  if (Stack > millis()){
    anglerStack(2.0);
    driveMove("both", 150);
    delay(200);
    driveStop();
    intakeMove(-200);
    delay(70);
    driveMove("both", -250);
    delay(500);
    driveStop();
    intakeStop();
  }

  //Does not stack if stack int is smaller than millis
  intakeMove(0);

}
