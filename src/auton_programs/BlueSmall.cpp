#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 8 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 8
void BlueSmall(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(75);
  Chassis->driveToPoint({3_ft, 0_ft});
  Intake.moveVelocity(100);

  //Drive to 2nd line of cubes
  Chassis->driveToPoint({0_ft, 2_ft});
  Intake.moveVelocity(200);

  //Intake 2nd line of cubes
  Chassis->setMaxVelocity(75);
  Chassis->driveToPoint({3_ft, 2_ft});
  Intake.moveVelocity(100);

  //Turn at scoring zone
  Angler.moveVoltage(5000);
  Chassis->turnToAngle(-135_deg);
  Angler.moveVelocity(0);
  Angler.setBrakeMode(AbstractMotor::brakeMode::hold);

  //Drive to scoring zone
  Chassis->driveToPoint({0.5_ft, 0_ft});
  Intake.moveVelocity(-30);
  Chassis->setMaxVelocity(100);
  Chassis->moveDistanceAsync(2_ft);
  pros::delay(1200);
  Chassis->stop();

  //Score cubes
  AnglerStack(2000);
  Chassis->moveDistance(-1_ft);

}
