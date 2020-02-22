#include "main.h"

#ifndef ROBOT_HPP
#define ROBOT_HPP

/* ********** Other ********** */

int secondsToMillis(float input);
int timeOut(int input);
void unfold();

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
void driveVoltLimit(string side, int limit);
void driveStop();
void drive(string direction, float target, int maxVelocity, float endTime);

#endif
