#include "main.h"

/* ********** Define Motor Ports ********** */

#define LFD_Port 15
#define LBD_Port 16
#define RFD_Port 17
#define RBD_Port 18
#define Angler_Port 13
#define Arm_Port 5
#define Cube_Intake_Left_Port 1
#define Cube_Intake_Right_Port 3

/* ********** Define Sensor Ports ********** */

#define Left_Encoder_Top_Port 'e'
#define Left_Encoder_Bottom_Port 'f'
#define Right_Encoder_Top_Port 'c'
#define Right_Encoder_Bottom_Port 'd'
#define Middle_Encoder_Top_Port 'g'
#define Middle_Encoder_Bottomm_Port 'h'
#define Angler_Potentiomenter_Port 'b'
#define Arm_Potentiometer_Port 'a'

/* ********** Creates Motors ********** */

Motor LFD(LFD_Port, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor LBD(LBD_Port, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor RFD(RFD_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor RBD(RBD_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor Arm(Arm_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor CIL(Cube_Intake_Left_Port, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor CIR(Cube_Intake_Right_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor Angler(Angler_Port, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

/* ********** Creates Motor Groups ********** */

MotorGroup LeftSide{LFD, LBD};
MotorGroup RightSide{RFD, RBD};
MotorGroup Intake{CIL, CIR};

/* ********** Creates Sensors ********** */

ADIEncoder LeftEnc(Left_Encoder_Top_Port, Left_Encoder_Bottom_Port, false);
ADIEncoder RightEnc(Right_Encoder_Top_Port, Right_Encoder_Bottom_Port, true);
ADIEncoder MiddleEnc(Middle_Encoder_Top_Port, Middle_Encoder_Bottomm_Port, false);
Potentiometer ArmPot(Arm_Potentiometer_Port);
Potentiometer AnglerPot(Angler_Potentiomenter_Port);

/* ********** Creates Controller ********** */

Controller Main(ControllerId::master);

/* ********** Angler Variables ********** */

int AnglerPotMin = 1195;
int AnglerPotMax = 3195;
float Angler_kP = 9.2;

/* ********** Arm Variables ********** */

int ArmHold = 1085;
int LowChalice = 1695;
int MediumChalice = 2300;
int ArmStart = 665;
