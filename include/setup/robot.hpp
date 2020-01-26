#include "main.h"

#ifndef ROBOT_HPP
#define ROBOT_HPP

/* ********** Drivetrain ********** */

extern std::shared_ptr<OdomChassisController> Chassis;
extern std::shared_ptr<AsyncMotionProfileController> ProfileController;

/* ********** Other ********** */

int Time(int TimeIn);
void Unfold();

/* ********** Arm Voids ********** */

void ArmHome(int TimeOut);
void ArmLowChalice(int TimeOut);
void ArmMediumChalice(int TimeOut);

/* ********** Angler Voids ********** */

void AnglerHome(int TimeOut);
void AnglerStack(int TimeOut);

#endif
