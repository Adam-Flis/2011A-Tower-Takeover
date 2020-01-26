#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  Chassis->setMaxVelocity(40);
  Chassis->moveDistance(6_in);
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->driveToPoint({3.4_ft, 0_ft});
  Intake.moveVelocity(100);

  //Turn at scoring zone
  Chassis->turnAngle(150_deg);

  //Drive at scoring zone
  Chassis->setMaxVelocity(90);
  Chassis->moveDistanceAsync(3.0_ft);
  pros::delay(400);
  Intake.moveVelocity(-35);
  pros::delay(600);
  Chassis->setMaxVelocity(40);
  pros::delay(400);
  Chassis->stop();

  //Score cubes
  AnglerStack(3000);
  pros::delay(200);

  //Drive out of zone
  Chassis->moveDistance(-1_ft);


}
