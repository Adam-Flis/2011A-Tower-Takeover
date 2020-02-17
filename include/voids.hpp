#include "main.h"

#ifndef ROBOT_HPP
#define ROBOT_HPP

extern int secondsToMillis(float input);
extern int timeOut(int input);

/* ********** Cube Intake ********** */

void intakeBrake();
void intakeMove(int velocity);
void intakeStop();

/* ********** Arm ********** */

void armBrakeMode();
void armUp(int position, int velocity, float endTime);
void armDown(int position, int velocity, float endTime);

/* ********** Angler ********** */

void anglerBrakeMode();
void anglerStack(float endTime);
void anglerHome(float endTime);

/* ********** Drivetrain ********** */

void driveReset();
void driveMode(string mode);
void driveMove(string side, int velocity);
void driveStop();
void drive(string direction, float target, int maxVelocity, float endTime);

#endif
