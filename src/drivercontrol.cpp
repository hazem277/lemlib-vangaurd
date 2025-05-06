#include "drivercontrol.h" // IWYU pragma: keep
#include "auton/auton.h"         // IWYU pragma: keep
#include "graphics.h"
#include "main.h"
#include "pros/abstract_motor.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "pros/motors.h"
#include <ctime>

bool isClamped = false;
bool isIntaking = false;
bool intakeReversed = false;
bool wallStakeActive = false;
bool rightArmDown = false;
bool leftArmDown = false;
bool debugMode = false;
bool ejectOn = true;
bool isTopRing = false;

void buttonControls() {
  wallStakeEnc.reset_position();
  while (true) {
    // clamp
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (isClamped) {
        clamp.set_value(false);
        isClamped = false;
      } else {
        clamp.set_value(true);
        isClamped = true;
      }
    }

    // intake piston
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      if (isTopRing) {
        topRing.set_value(false);
        isTopRing = false;
      } else {
        topRing.set_value(true);
        isTopRing = true;
      }
    }

    // intake
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (!isIntaking || !intakeReversed) {
        intake.move(-127);
        chain.move(-85);
        isIntaking = true;
        intakeReversed = true;
      }
      else if (isIntaking && intakeReversed) {
        intake.brake();
        chain.brake();
        isIntaking = false;
        intakeReversed = false;
      }
    }
    else if (controller.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_R1)) {
      if (!isIntaking || intakeReversed) {
        intake.move(127);
        chain.move(85);
        isIntaking = true;
        intakeReversed = false;
      }
      else if (isIntaking && !intakeReversed && !wallStakeActive) {
        intake.brake();
        chain.brake();
        isIntaking = false;
      }
      else if (isIntaking && !intakeReversed && wallStakeActive) {
        chain.brake();
        isIntaking = false;
      }
    }

    // wall stake
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      if (!wallStakeActive) { // activate wall stake
        wallStakeEnc.reset_position();
        lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
        lift.move_absolute(9500, 50);
        while (wallStakeEnc.get_position() < 9250) {
          pros::delay(10);
        }
        wallStakeActive = true;
      }
      else { // retract wall stake
        if (!isIntaking) {
          intake.brake();
        }

        lift.move(-127);
        pros::delay(700);
        lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
        wallStakeActive = false;
        
        lift.brake();
      }
    }
    if (wallStakeActive) {
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) { // scoring
        lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        lift.move(127);
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
          pros::delay(50);
        }
      } else {
        lift.brake();
      }
    }

    // arms
    // ---------------------------------------------------------------------------------------------------------------------w
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      if (!rightArmDown) {
        rightArm.set_value(true);
        rightArmDown = true;
      } else {
        rightArm.set_value(false);
        rightArmDown = false;
      }
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      if (!leftArmDown) {
        leftArm.set_value(true);
        leftArmDown = true;
      } else {
        leftArm.set_value(false);
        leftArmDown = false;
      }
    }

    // DEBUG SCREEN (LVGL - graphics.cpp)
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && !debugMode) {
      lv_scr_load_anim(screenDebug, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
               debugMode) {
      lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        pros::delay(50);
      }
    }

    // Ejection toggle

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && ejectOn) {
      ejectOn = false;
      controller.clear_line(0);
      controller.set_text(1, 1, "Example text");
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) &&
               !ejectOn) {

      ejectOn = true;
      controller.clear_line(2);
      controller.set_text(0, 0, "Example text");
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        pros::delay(50);
      }
    }
  }
}