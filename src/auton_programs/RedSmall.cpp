#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  //Auton start things
  int Stack = timeOut(secondsToMillis(13.0));
  driveMove("both", -15);
  unfold();
  driveStop();
  intakeMove(200);
  arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  delay(100);

  //Grab line of cubes: 5 total
  drive("f", 38, 90, 3.5);
  intakeMove(100);

  //Drive away from line and turn at 6th cube
  drive("l", 25, 180, 1.0);
  intakeMove(170);
  drive("f", 8.5, 200, 1.7);

  //Drive away 6th cube
  intakeStop();
  driveMove("both", -100);
  delay(500);
  driveStop();
  delay(100);

  //Turn and drive at scoing zone
  drive("l", 185, 180, 2.7);
  intakeMove(-30);
  drive("f", 17, 130, 1.7);

  //Stack cubes and drive away
  //Makes sure we have the time to stack
  if (Stack > millis()){
    anglerStack(2.0);
    intakeMove(-200);
    delay(50);
    driveMove("both", -250);
    delay(500);
    driveStop();
    intakeStop();
  }

  //Does not stack if stack int is smaller than millis
  intakeMove(0);

}
