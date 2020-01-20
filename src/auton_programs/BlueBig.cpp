#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 6
void BlueBig(){

  //Unfolds tray
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Drive at cube tower
  Chassis->driveToPoint({3_ft, 0_ft});
  pros::delay(800);

  //Turn and drive at chalice cube
  Intake.moveVelocity(100);
  Chassis->turnToAngle(20_deg);
  Intake.moveVelocity(200);
  Chassis->setMaxVelocity(100);
  Chassis->moveDistanceAsync(1.5_ft);
  pros::delay(800);
  Chassis->stop();

  //Drive away from challice cube
  Chassis->setMaxVelocity(200);
  Chassis->driveToPoint({3_ft, 0_ft});
  Intake.moveVelocity(100);

  //Turn and drive at scoring zone
  pros::delay(500);
  Chassis->turnToAngle(135_deg);
  Chassis->moveDistanceAsync(4_ft);
  pros::delay(500);
  Intake.moveVelocity(200);
  pros::delay(1000);
  Chassis->setMaxVelocity(100);
  pros::delay(500);
  Chassis->stop();
  Intake.moveVelocity(100);

  //Align on scoring zone
  LeftSide.moveVelocity(200);
  Intake.moveVelocity(-30);
  pros::delay(1000);
  LeftSide.moveVelocity(0);

  //Score cubes
  AnglerStack(3000);
  Chassis->moveDistance(-1_ft);

}
