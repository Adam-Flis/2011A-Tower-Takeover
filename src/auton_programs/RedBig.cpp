#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 4 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 4
void RedBig(){

  //Auton start things
  int Stack = timeOut(secondsToMillis(12.0));
  driveMove("both", -15);
  unfold();
  delay(1000);
  driveStop();
  intakeMove(200);

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
  //Makes sure we have the time to stack
  if (Stack > millis()){
    anglerStack(2.3);
    driveMove("both", -250);
    delay(500);
    driveStop();
    intakeMove(0);
    anglerHome(2.0);
  }
  //Does not stack if stack int is smaller than millis
  intakeMove(0);

}
