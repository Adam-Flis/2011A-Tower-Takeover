#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//USed for testing commands and tuning PIDs
void Test(){

  Chassis->moveDistance(36_in);
  Chassis->waitUntilSettled();

  /*Chassis->turnAngle(90_deg);
  Chassis->waitUntilSettled();*/

  /*Chassis->setState({0_in, 0_in, 0_deg});
  pros::delay(200);
  Chassis->driveToPoint({2_ft, 0_ft});
  Chassis->turnAngle(90_deg);*/

  /*ProfileController->loadPath("/usd/A.csv", "A");
  ProfileController->setTarget("A", true, true);
  ProfileController->waitUntilSettled();*/

  Intake.moveVelocity(200);

}

//Waits 15 seconds and does nothing
void Nothing(){
  pros::delay(15000);
}
