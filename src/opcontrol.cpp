#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"
#include "odomDebug/odomDebug.hpp"

void setState(OdomDebug::state_t state){
  Chassis->setState({Chassis->getState().x, Chassis->getState().y, Chassis->getState().theta});
}

void resetSensors(){
  Chassis->setState({0_in, 0_in, 0_deg});
  LeftEnc.reset();
  RightEnc.reset();
  MiddleEnc.reset();
}

void opcontrol(){

  /* ********** Declares Controller Buttons ********** */

  ControllerButton ButtonUp = Main[ControllerDigital::up];
  ControllerButton ButtonDown = Main[ControllerDigital::down];
  ControllerButton ButtonLeft = Main[ControllerDigital::left];
  ControllerButton ButtonRight = Main[ControllerDigital::right];
  ControllerButton ButtonL1 = Main[ControllerDigital::L1];
  ControllerButton ButtonL2 = Main[ControllerDigital::L2];
  ControllerButton ButtonR1 = Main[ControllerDigital::R1];
  ControllerButton ButtonR2 = Main[ControllerDigital::R2];
  ControllerButton ButtonX = Main[ControllerDigital::X];
  ControllerButton ButtonY = Main[ControllerDigital::Y];
  ControllerButton ButtonA = Main[ControllerDigital::A];
  ControllerButton ButtonB = Main[ControllerDigital::B];

  ProfileController->flipDisable(true); //Disables the profile controller, prevents it from trying to run during operator control
  Chassis->stop(); //Stops the drivetrain motors from running in the background
  Chassis->setMaxVelocity(200); //Makes sure to reset the velocity to the maximum on the drivetrain
  Chassis->getModel()->setMaxVoltage(12000); //Makes sure to reset the voltage to the maximum on the drivetrain
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake); //Sets brake mode brake on drivetrain
  Chassis->setState({0_in, 0_in, 0_deg});
  bool TrayDown = true;

  OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
  display.setStateCallback(setState);
  display.setResetCallback(resetSensors);

  while(1){

    //Displays the robot position on the cortex screen
    display.setData({Chassis->getState().x, Chassis->getState().y, Chassis->getState().theta}, {LeftEnc.get(), RightEnc.get(), MiddleEnc.get()});

    /*if (ButtonDown.isPressed()){
      Unfold();
    }*/

    /* ********** Drivetrain Control ********** */

    Chassis->getModel()->tank(Main.getAnalog(ControllerAnalog::leftY), //Left joystick moved, power left side of drivetrain
                              Main.getAnalog(ControllerAnalog::rightY)); //Right joystickt moved, power right side of drivetrain

    /* ********** Cube Intake Control ********** */

    if (ButtonL1.isPressed()){ //Button left 1 pressed, intake cubes
      Intake.moveVoltage(12000);
    }
    else if (ButtonL2.isPressed()){ //Button left 2 pressed, outtake cubes
      Intake.moveVoltage(-12000);
    }
    else { //Sets brake mode and stops cube intake when buttons L1 & L2 are not pressed
      Intake.setBrakeMode(AbstractMotor::brakeMode::brake); //Set brake mode brake
      Intake.moveVelocity(0); //Stops intake
    }

    /* ********** Arm Control ********** */

    if (ButtonR1.isPressed()){ //Button right 1 pressed, raise arm
      Arm.moveVelocity(200);
    }
    else if (ButtonR2.isPressed()){ //Button right 2 pressed, lower arm
      Arm.moveVelocity(-200);
    }
    else { //Sets brake mode and stops arm when buttons R1 & R2 are not pressed
 			if (ArmPot.get() > ArmHold) { //Set brake mode hold if over certain value
 				Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
 			}
 			else { //Set brake mode brake if anything else
 				Arm.setBrakeMode(AbstractMotor::brakeMode::brake);
 			}
 			Arm.moveVelocity(0); //Stops arm
 		}

    /* ********** Angler Control ********** */

    if (ButtonY.changedToPressed()){ //Button Y changed state, start or stop macro for lowering tray
      TrayDown = !TrayDown;
    }
    if (ButtonA.isPressed() && AnglerPot.get() < AnglerPotMax){ //Button A pressed, raise tray
      int Error = AnglerPotMax - AnglerPot.get();
      double Voltage = Error * Angler_kP;
      if (Voltage > 12000){
        Voltage = 12000; //Maximum angler voltage for going up
      }
      else if (Voltage < 4000){
        Voltage = 4000; //Minimum angler voltage for going up
      }
      Angler.moveVoltage(Voltage); //Sets angler voltage
		}
    else if (AnglerPot.get() > AnglerPotMin){
      if (ButtonA.isPressed() || TrayDown == true){ //Button A pressed or TrayDown true, lower tray
        int Error = AnglerPot.get() - AnglerPotMin;
        double Voltage = Error * Angler_kP;
        if (Voltage > 12000){
          Voltage = 12000; //Maximum angler voltage for going down
        }
        else if (Voltage < 8000){
          Voltage = 8000; //Minimum angler voltage for going down
        }
        Angler.moveVoltage(-Voltage); //Sets angler voltage
      }
    }
    else { //Sets brake mode and stops tray when buttons A & B are not pressed & TrayDown = false
      if(AnglerPot.get() > (AnglerPotMax/2)){ //Set brake mode hold if over certain value
        Angler.setBrakeMode(AbstractMotor::brakeMode::hold);
      }
      else { //Set brake mode coast if anything else
        Angler.setBrakeMode(AbstractMotor::brakeMode::coast);
      }
      TrayDown = false;
      Angler.moveVelocity(0); //Stops angler
    }

    pros::delay(10); //Loop speed, prevent overload
  }
}
