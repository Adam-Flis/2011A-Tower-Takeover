#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  Chassis->driveToPoint({0.05_ft, 0_ft});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->driveToPoint({2.4_ft, 0_ft});

  //Turn at challice cube
  Chassis->turnAngle(-23_deg);

  //Grab 6th cube
  Chassis->moveDistance(4.45_in);
  Chassis->waitUntilSettled();
  pros::delay(300);
  Intake.moveVelocity(35);

  //Drive away from chalice
  Chassis->moveDistance(-8_in);
  pros::delay(300);
  Chassis->turnAngle({140_deg});

  //Drive to score
  Chassis->moveDistance(1.5_ft);
  RightSide.moveVelocity(100);
  Intake.moveVelocity(-40);
  pros::delay(550);
  RightSide.moveVelocity(0);
  AnglerStack(3000);

  //Drive away from zone
  Chassis->moveDistance(-1_ft);


}
