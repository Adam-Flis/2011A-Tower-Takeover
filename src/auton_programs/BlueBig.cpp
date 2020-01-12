#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 5 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 5
void BlueBigClose(){

  //Unfolds tray and sets starting point
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);

  //Drive at cube tower and sucks up cubes
  Chassis->moveDistanceAsync(3.8_ft);
  pros::delay(2300);
  Chassis->stop();
  pros::delay(800);

  //Turn and drive at the scoring zone
  Intake.moveVelocity(0);
  Chassis->moveDistance(-4_in);
  Chassis->turnAngle(120_deg);
  Chassis->moveDistanceAsync(3.0_ft);
  pros::delay(200);
  Intake.moveVelocity(200); //Suck up cube
  pros::delay(1350);

  //Set down stack
  Intake.moveVelocity(-200);
  pros::delay(100);
  Intake.moveVelocity(-20);
  AnglerStack(3200);
  pros::delay(800);
  Chassis->stop();
  Intake.moveVelocity(-80);
  pros::delay(1000);

  //Drive out of scoring zone
  Chassis->moveDistance(-1_ft);

}

//Collects 5 cubes from the field
//Places cubes into the corner of the big scoring zone
//Points scored: 5
void BlueBigCorner(){

  //Unfolds tray and sets starting point
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);

  //Drive at cube tower and sucks up cubes
  Chassis->moveDistance(3.8_ft);
  pros::delay(800);

  //Turn and drive at the scoring zone
  Intake.moveVelocity(0);
  Chassis->moveDistance(-4_in);
  Chassis->turnAngle(120_deg);
  Chassis->moveDistanceAsync(3.25_ft);
  pros::delay(250);
  Intake.moveVelocity(200); //Suck up cube
  pros::delay(1250);

  //Set down stack
  Intake.moveVelocity(-40);
  AnglerStack(3200);
  pros::delay(200);
  Chassis->waitUntilSettled();
  Intake.moveVelocity(-100);
  pros::delay(1000);

  //Drive out of scoring zone
  Chassis->moveDistance(-1_ft);

}
