#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 6 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 6
void BlueBig(){

  //Auton start things
  int Stack = timeOut(secondsToMillis(13.3));
  driveMove("both", -10);
  //unfold();
  driveStop();
  intakeMove(200);

  //Drive at 1st & 2nd cube
  drive("f", 18, 220, 1.3);
  intakeMove(100);
  delay(200);

  //Turn and get 3rd and 4th cube
  drive("l", 85, 170, 2.5);
  delay(200);
  intakeMove(200);
  drive("f", 28, 180, 2.5);
  delay(200);

  //Drive away from cube and go to scoring zone
  intakeMove(100);
  drive("b", 20, 220, 3.4);
  intakeMove(0);
  delay(200);
  drive("l", 160, 170, 3.0);

  //Go to stack cubes
  RFD.set_current_limit(800);
  RBD.set_current_limit(800);
  intakeMove(-35);
  drive("f", 12, 150, 1.2);

  //Stack cubes and drive away
  //Makes sure we have the time to stack
  if (Stack > millis()){
    anglerStack(2.3);
    RFD.set_current_limit(12000);
    RBD.set_current_limit(12000);
    drive("b", 12, 250, 1.0);
  }
  //Does not stack if stack int is smaller than millis
  else {
    intakeMove(0);
    angler.move_velocity(0);
    driveStop();
  }
}
