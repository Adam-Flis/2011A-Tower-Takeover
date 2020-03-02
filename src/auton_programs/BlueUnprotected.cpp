#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 6 cubes from the field
//Places cubes into the unprotected scoring
//Points scored: 6
void BlueUnprotected(){

  //Auton start things
  int Stack = timeOut(secondsToMillis(13.0));
  //driveMove("both", -15);
  //unfold();
  //driveStop();
  intakeMove(200);
  arm.move_velocity(-5);

  //Grab line of cubes: 6 total
  drive("f", 54.5, 85, 4.1);
  delay(450);
  intakeStop();
  drive("b", 10, 250, 0.8);
  delay(20);

  //Turn and drive at 2nd line
  drive("l", 45, 250, 0.4);
  delay(50);
  drive("b", 36.5, 250, 3.0);
  delay(50);
  drive("r", 43, 250, 0.4);
  delay(20);

  //Grab next 2 cubes
  intakeMove(200);
  drive("f", 15, 85, 1.7, false);
  delay(200);

/*
  //Turn and drive at scoring zone
  intakeMove(50);
  drive("l", 115, 250, 1.0);
  intakeStop();
  angler.move_voltage(7000);
  drive("f", 29, 180, 2.2);
  angler.move_voltage(0);

  //Stack cubes and drive away
  //Makes sure we have the time to stack
  if (Stack > millis()){
    driveMove("right", 30);
    anglerStack(2.3);
    driveStop();
    intakeMove(-200);
    delay(300);
    drive("b", 12, 250, 1.0);
  }
  //Does not stack if stack int is smaller than millis
  intakeMove(0);
*/
}

/*
  //Auton start things
  int Stack = timeOut(secondsToMillis(13.0));
  driveMove("both", -15);
  //unfold();
  driveStop();
  intakeMove(200);
  arm.move_velocity(-5);

  //Grab line of cubes: 5 total
  drive("f", 39, 90, 3.0);
  intakeMove(50);

  //Trun and grab 6th pryamid cube
  drive("l", 35, 250, 0.8);
  intakeMove(200);
  drive("f", 15, 250, 1.2);
  intakeMove(100);

  //Drive away 6th cube
  drive("b", 48, 250, 2.2);
  intakeMove(50);
  delay(100);
  drive("r", 42, 200, 1.2);

  //Drive at 7th and 8th cube
  intakeMove(200);
  drive("f", 23, 140, 2.1);
  intakeMove(50);

  //Turn and drive at scoring zone
  drive("l", 130, 225, 1.5);
  angler.move_voltage(9200);
  drive("f", 31.5, 250, 1.8);

  //Stack cubes
  intakeMove(-10);
  anglerStack(1.0);
  driveStop();
  delay(200);
  intakeMove(-200);
  drive("b", 12, 250, 1.0);
*/
