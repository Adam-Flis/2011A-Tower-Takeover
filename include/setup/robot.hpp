#include "main.h"

#ifndef ROBOT_HPP
#define ROBOT_HPP

/* ********** Drivetrain ********** */

extern std::shared_ptr<OdomChassisController> Chassis;
extern std::shared_ptr<AsyncMotionProfileController> ProfileController;

/* ********** Other ********** */

int Time(int TimeIn);
void Unfold();
void DriveVel(int Velocity);

/* ********** Arm Voids ********** */

void ArmMove(int Position, int TimeOut);

/* ********** Angler Voids ********** */

void AnglerHome(int TimeOut);
void AnglerStack(int TimeOut);

#endif
