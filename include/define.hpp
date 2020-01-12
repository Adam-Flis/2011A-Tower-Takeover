#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD;
extern Motor LBD;
extern Motor RFD;
extern Motor RBD;
extern Motor Arm;
extern Motor CI1;
extern Motor CI2;
extern Motor Angler;
extern MotorGroup LeftSide;
extern MotorGroup RightSide;
extern MotorGroup Intake;


/* ********** Declare Sensors ********** */

extern ADIEncoder LeftEnc;
extern ADIEncoder RightEnc;
extern ADIEncoder MiddleEnc;
extern Potentiometer ArmPot;
extern Potentiometer AnglerPot;


/* ********** Declare Controller ********** */

extern Controller Main;


/* ********** Declare Angler Variables ********** */

extern int AnglerPotMin;
extern int AnglerPotMax;
extern float Angler_kP;


/* ********** Declare Arm Variables ********** */

extern int LowChalice;
extern int MediumChalice;
extern int ArmHold;
extern int ArmStart;

#endif
