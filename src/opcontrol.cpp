#include "main.h"
#include "define.hpp"
#include "voids.hpp"


void opcontrol(){
  driveMode("brake");
  while(1){

    /* ********** Senor Readout ********** */

    //Dsplay sensor information for debugging
    lcd::print(1,"Inertial Sensor: %0.3f Degrees\n",IMU.get_rotation());
    lcd::print(2,"Right Encoder: %d Ticks\n",rEnc.get_value());
    lcd::print(3,"Left Encoder: %d Ticks\n",lEnc.get_value());

    /* ********** Drivetrain ********** */

    LFD.move(Main.get_analog(ANALOG_LEFT_Y));
    LBD.move(Main.get_analog(ANALOG_LEFT_Y));
    RFD.move(Main.get_analog(ANALOG_RIGHT_Y));
    RBD.move(Main.get_analog(ANALOG_RIGHT_Y));

    /* ********** Cube Intake ********** */

    if (Main.get_digital(DIGITAL_L1)){ //Button L1 pressed, intake cubes
      LI.move_velocity(200);
      RI.move_velocity(200);
    }
    else if (Main.get_digital(DIGITAL_L2)){ //Button L2 pressed, outtake cubes
      LI.move_velocity(-200);
      RI.move_velocity(-200);
    }
    else {
      LI.set_brake_mode(MOTOR_BRAKE_BRAKE); //Sets brake mode of intake to brake
      RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
      LI.move_velocity(0);
      RI.move_velocity(0);
    }

    /* ********** Arm ********** */

    if (Main.get_digital(DIGITAL_R1)){ //Button R1 pressed, arm up
      arm.move_velocity(200);
    }
    else if (Main.get_digital(DIGITAL_R2)){ //Button R2 pressed, arm down
      arm.move_velocity(-200);
    }
    else {
      armBrakeMode(); //Sets the brake mode of the arm depending on its position
      arm.move_velocity(0);
    }

    /* ********** Angler ********** */

    if (Main.get_digital_new_press(DIGITAL_Y)){ //Angler macro key
      trayDown = !trayDown;
    }
    if (trayDown == true && anglerPot.get_value() > anglerHomeVar){ //trayDown = true, tray down
      angler.move_voltage(-10000);
    }
    else if (Main.get_digital(DIGITAL_B) && anglerPot.get_value() > anglerHomeVar){ //Button B pressed, tray down
      angler.move_voltage(-10000);
      trayDown = false;
    }
    else if (Main.get_digital(DIGITAL_A) && anglerPot.get_value() < anglerStackVar){ //Button A pressed, tray up
      float error = anglerStackVar - anglerPot.get_value();
      float voltage = error * angler_kP;
      if (voltage > 12000){ //Max voltage
        voltage = 12000;
      }
      if (voltage < 5000){ //Min voltage
        voltage = 5000;
      }
      angler.move_voltage(voltage); //Sets angler voltage
      trayDown = false;
    }
    else {
      trayDown = false;
      anglerBrakeMode(); //Sets the brake mode of the angler depending on its position
      angler.move_velocity(0);
    }
    delay(10); //Loop speed, prevent overload
  }
}
