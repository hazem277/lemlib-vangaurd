#include "auton.h"
#include "drivercontrol.h"
#include "fmt/format.h" // IWYU pragma: keep
#include "lemlib-tarball/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cmath>

auton_type autonType = SKILLS;
bool scoreAllianceStake = true;
bool autonConfirmed = true;

ASSET(skills_path_txt);

lemlib_tarball::Decoder decoder(skills_path_txt);

void clampSet(bool value) {
  clamp.set_value(value);
  clamp2.set_value(value);
}

enum wallStakePos { PASSIVE, ACTIVE, SCORING };

void setWallStakePos(wallStakePos pos) {
  if (pos == PASSIVE) {
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    lift.brake();
  } else if (pos == ACTIVE) {
    wallStakeEnc.reset_position();
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(20);
    while (wallStakeEnc.get_position() < 4500) {
      pros::delay(10);
    }
    lift.brake();
  } else if (pos == SCORING) {
    lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift.move_relative(310, 127);
  }
}

void runAuton() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  while (!autonConfirmed) {
    pros::delay(50);
  }
  pros::delay(1500);
  if (autonType == RED_POSITIVE && scoreAllianceStake) {

    chassis.setPose(60, 17, 0);
    chassis.moveToPose(60, 0, 0, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
    chassis.turnToHeading(0, 2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == RED_POSITIVE && !scoreAllianceStake) {
    // code
  }

  else if (autonType == RED_NEGATIVE && scoreAllianceStake) {
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, 0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 130) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, -27, 700, {.forwards = false});
    chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true); 
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);

    chassis.turnToPoint(19, -48, 500);
    chassis.moveToPoint(19, -48, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(30, -48, 1000, {.forwards = false});
    chassis.turnToPoint(19, -53, 700);
    chassis.moveToPoint(19, -53, 2000);
    // chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_POSITIVE && scoreAllianceStake) {
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, 0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 130) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, -27, 700, {.forwards = false});
    chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);
    chassis.turnToHeading(180,2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    // chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_POSITIVE && !scoreAllianceStake) {
    // code
  }

  else if (autonType == BLUE_NEGATIVE && scoreAllianceStake) {
    
    chassis.setPose(60, 17, 0);
    chassis.moveToPose(60, 0, 0, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
  
    chassis.turnToPoint(19, 48, 500);
    chassis.moveToPoint(19, 48, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(30, 48, 1000, {.forwards = false});
    chassis.turnToPoint(19, 53, 700);
    chassis.moveToPoint(19, 53, 2000);
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_NEGATIVE && !scoreAllianceStake) {
    // code
  }

  else if (autonType == SKILLS) {
    chassis.setPose(-62, 0, 90);
    intake.move(127);
    pros::delay(300);
    intake.brake();
    chassis.moveToPoint(-51, 0, 1000);
    chassis.turnToHeading(180, 700);
    chassis.moveToPoint(chassis.getPose().x, 23, 850, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();
    clampSet(true); // Mogo 1
    chassis.turnToHeading(90, 700);
    chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPoint(-23, 24, 1500, {.maxSpeed = 100}); // Ring 1
    chassis.turnToHeading(45, 700);
    chassis.moveToPose(27, 42, 90, 2500); // Ring 2
    chassis.turnToPoint(3, 35, 1000, {.forwards = false});
    chassis.moveToPoint(3, 35, 1000, {.forwards = false});
    chassis.turnToHeading(0, 700);
    chassis.waitUntilDone();
    setWallStakePos(ACTIVE);
    chassis.moveToPoint(chassis.getPose().x, 50, 1000, {.maxSpeed = 50}); // Wall Stake 1
    chassis.waitUntilDone();
    pros::delay(2000);
    intake.brake();
    chassis.moveToPoint(chassis.getPose().x, 53, 700);
    setWallStakePos(SCORING);
    pros::delay(1250);
    setWallStakePos(PASSIVE);
    pros::delay(1250);
    chassis.moveToPoint(chassis.getPose().x, 41, 1000, {.forwards = false});
    chassis.turnToHeading(270, 700);
    chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPoint(-56, 42, 3000, {.maxSpeed = 50}); // Ring 3
    chassis.turnToPoint(-44, 38, 700,{.forwards = false});
    chassis.moveToPoint(-44, 38, 700, {.forwards = false, .maxSpeed = 50}); // Align 1
    chassis.turnToHeading(0, 700);
    chassis.moveToPoint(chassis.getPose().x, 50, 700);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveToPoint(-44, 42, 700, {.forwards = false});
    chassis.turnToHeading(135, 700);
    chassis .waitUntilDone();
    intake.brake();
    clampSet(false);
    chassis.moveToPoint(-59, 59, 700, {.forwards = false});
    chassis.moveToPose(-47, 0, 180, 3000);
    chassis.turnToHeading(0, 700);
  }
}