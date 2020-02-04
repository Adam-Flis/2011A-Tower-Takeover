#include "main.h"
#include "setup/robot.hpp"

//Code that runs when you start the program
void initialize(){
  /*ProfileController->generatePath({{0_ft, 0_ft, 0_deg}, {1.4_ft, 1.8_ft, 0_deg}}, "A");
  ProfileController->storePath("/usd/A.csv", "A");*/
  /*Logger::setDefaultLogger(
    std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::warn // Show errors and warnings
  ));*/
}

//Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled(){

}

//Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize(){

}
