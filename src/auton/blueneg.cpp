#include "auton.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"

void blue_neg() {
  if (scoreAllianceStake) {
    chassis.setPose(0, 0, 320);
    lift.move(127);
    pros::delay(800);
    chassis.moveToPoint(chassis.getPose().x + 20, chassis.getPose().y - 20,
                        1000, {.forwards = false});
    lift.move(-127);
    pros::delay(500);
    lift.brake();
    intake.move(127);
    chassis.waitUntilDone();
    chassis.turnToPoint(chassis.getPose().x + 37, chassis.getPose().y - 7,700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 37, chassis.getPose().y - 7, 1350, {}, false);
    rightArm.set_value(true);
    chassis.moveToPoint(chassis.getPose().x - 16, chassis.getPose().y + 18, 1000, {.forwards = false}, false);
    rightArm.set_value(false);
    clamp.set_value(true);
    pros::delay(500);
    chain.move(85);
    chassis.turnToPoint(chassis.getPose().x + 4, chassis.getPose().y - 25, 700,
                        {}, false);
    chassis.moveToPoint(chassis.getPose().x + 4, chassis.getPose().y - 25, 1000,
                        {}, false);
    chassis.turnToPoint(chassis.getPose().x - 4, chassis.getPose().y - 10, 700,
                        {}, false);
    chassis.moveToPoint(chassis.getPose().x - 4, chassis.getPose().y - 10, 1000,
                        {}, false);
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y + 20, 700, {.forwards = false}, false);
    chassis.turnToPoint(8, 10, 1000, {}, false);
    topRing.set_value(true);
    chassis.moveToPoint(8, 10, 1000, {}, false);
    pros::delay(1000);
    chassis.turnToHeading(90, 700, {}, false);
    topRing.set_value(false);
    chassis.moveToPoint(chassis.getPose().x + 18, chassis.getPose().y, 1000, {}, false);
    lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(127);
    pros::delay(500);
    lift.brake();

    isClamped = true;
  }
  else {
    chassis.setPose(0, 0, 90);
    chassis.moveToPoint(chassis.getPose().x + 38, chassis.getPose().y, 1000, {}, false);
    chassis.turnToPoint(chassis.getPose().x + 7, chassis.getPose().y - 3, 600, {});
    intake.move(127);
    chassis.moveToPoint(chassis.getPose().x + 7, chassis.getPose().y - 3, 1000, {.minSpeed = 90}, false);
    rightArm.set_value(true);
    int temp_x = chassis.getPose().x - 20;
    int temp_y = chassis.getPose().y + 20;
    chassis.moveToPoint(temp_x, temp_y, 1000, {.forwards = false, .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 10});
    chassis.moveToPoint(temp_x, temp_y, 700, {.forwards = false, .maxSpeed = 30});
    pros::delay(600);
    clamp.set_value(true);
    chain.move(85);
    chassis.waitUntilDone();
    rightArm.set_value(false);
    chassis.swingToHeading(180, lemlib::DriveSide::RIGHT, 1000, {}, false);
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y, 1000);
    chassis.turnToHeading(315, 700);
  }
}