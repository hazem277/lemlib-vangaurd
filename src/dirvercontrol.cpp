#include "auton.h"
#include "drivercontrol.h" // IWYU pragma: keep
#include "graphics.h"
#include "main.h"
#include "pros/abstract_motor.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "pros/motors.h" 

bool isClamped = false;
bool isIntaking = false;
bool intakeReversed = false;
bool wallStakeActive = false;
bool armDown = false;
bool debugMode = false;

void buttonControls(void *param) {
  wallStakeEnc.reset_position();
  while (true) {
    // clamp
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && isClamped) {
      clamp.set_value(false);
      clamp2.set_value(false);
      isClamped = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) &&
               !isClamped) {
      clamp.set_value(true);
      clamp2.set_value(true);
      isClamped = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        pros::delay(50);
      }
    }

    // intake
    if (isIntaking && !intakeReversed) { // red ≈ 14 | blue ≈ 219 | none ≈ 63
      if ((opticalSensor.get_hue() > 210 && opticalSensor.get_hue() < 225 && (autonType == RED_POSITIVE || autonType == RED_NEGATIVE || autonType == SKILLS)) || (opticalSensor.get_hue() > 210 && opticalSensor.get_hue() < 225 && (autonType == BLUE_POSITIVE || autonType == BLUE_NEGATIVE))) {
        pros::delay(350);
        intake.brake();
        pros::delay(200);
        intake.move(127);
      }
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) &&
        (!isIntaking || intakeReversed)) {
      intake.move(-127);
      isIntaking = true;
      intakeReversed = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) &&
               isIntaking && !intakeReversed) {
      intake.brake();
      isIntaking = false;
      intakeReversed = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
               (!isIntaking || !intakeReversed)) {
      intake.move(127);
      isIntaking = true;
      intakeReversed = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
               isIntaking && intakeReversed) {
      intake.brake();
      isIntaking = false;
      intakeReversed = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        pros::delay(50);
      }
    }

    // wall stake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) &&
    !wallStakeActive) {
      wallStakeEnc.reset_position();
      lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
      lift.move(25);
      while (wallStakeEnc.get_position() < 4700) {
        pros::delay(10);
      }
      lift.brake();
      wallStakeActive = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
      lift.brake();
      wallStakeActive = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        pros::delay(50);
      }
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) &&
        wallStakeActive && wallStakeEnc.get_position() / 100 < 250) {
      lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      lift.move_relative(310, 127);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        pros::delay(50);
      }
    }

    // arm
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !armDown) {
      arm.set_value(true);
      armDown = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(50);
      }
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && armDown) {
      arm.set_value(false);
      armDown = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(50);
      }
    }

    // DEBUG SCREEN (LVGL - graphics.cpp)
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && !debugMode) {
      lv_scr_load_anim(screenDebug, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000,
        false);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        pros::delay(50);
      }
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && debugMode) {
      lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000,
        false);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        pros::delay(50);
      }
    }
  }
}