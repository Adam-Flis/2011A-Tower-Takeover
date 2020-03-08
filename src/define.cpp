#include "main.h"

/* ********** Define Motor Ports ********** */

#define LFD_Port 4
#define LBD_Port 5
#define RFD_Port 10
#define RBD_Port 9
#define Angler_Port 3
#define Arm_Port 13
#define Cube_Intake_Left_Port 14
#define Cube_Intake_Right_Port 12

/* ********** Define Sensor Ports ********** */

#define IMU_Port 2
#define Left_Encoder_Top_Port 'e'
#define Left_Encoder_Bottom_Port 'f'
#define Right_Encoder_Top_Port 'a'
#define Right_Encoder_Bottom_Port 'b'
#define Angler_Potentiomenter_Port 'c'
#define Arm_Potentiometer_Port 'd'


/* ********** Creates Motors ********** */

Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor angler (Angler_Port,MOTOR_GEARSET_36,false,MOTOR_ENCODER_DEGREES);
Motor arm (Arm_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor LI (Cube_Intake_Left_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor RI (Cube_Intake_Right_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);

/* ********** Creates Sensors ********** */

Imu IMU (IMU_Port);
ADIAnalogIn anglerPot (Angler_Potentiomenter_Port);
ADIAnalogIn armPot (Arm_Potentiometer_Port);
ADIEncoder lEnc (Left_Encoder_Top_Port,Left_Encoder_Bottom_Port,true);
ADIEncoder rEnc (Right_Encoder_Top_Port,Right_Encoder_Bottom_Port,false);

/* ********** Creates Controller ********** */

Controller Main (CONTROLLER_MASTER);

/* ********** Arm Variables ********** */

int armHold = 1100;
int smallChalice = 1600;
int mediumChalice = 2000;
int armHome = 740;

/* ********** Angler Variables ********** */

int anglerHomeVar = 1260;
int anglerStackVar = 3480;
int anglerAdd = 650;
float angler_Kp = 9.8;
