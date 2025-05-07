#include "auton.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/motors.h"

void blue_pos() {
  if (scoreAllianceStake) {
    chassis.setPose(0, 0, 213);
    // chassis.turnToHeading(180, 1000);
    lift.move(127);
    pros::delay(850);
    chassis.moveToPoint(chassis.getPose().x + 16, chassis.getPose().y + 5, 1000,
                        {.forwards = false});
    lift.move(-127);
    pros::delay(500);
    lift.brake();
    chassis.turnToHeading(180, 700, {}, false);
    topRing.set_value(true);
    intake.move(127);
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y - 10, 1000, {},
                        false);
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y + 3, 500, {},
                        false);
    topRing.set_value(false);
    chassis.turnToHeading(245, 700, {}, false);
    int temp_x, temp_y;
    temp_x = chassis.getPose().x + 23.4;
    temp_y = chassis.getPose().y + 11;
    chassis.moveToPoint(temp_x, temp_y, 700,
                        {.forwards       = false,
                         .maxSpeed       = 70,
                         .minSpeed       = 10,
                         .earlyExitRange = 17});
    chassis.moveToPoint(temp_x, temp_y, 700,
                        {.forwards = false, .maxSpeed = 40});
    pros::delay(700);
    clamp.set_value(true);
    chain.move(85);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.turnToHeading(0, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 5, chassis.getPose().y + 20, 1000,
                        {}, false);
    pros::delay(500);
    chassis.turnToHeading(180, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 12, chassis.getPose().y - 23,
                        1000);
    chassis.turnToHeading(135, 700);
  }
  else {
    chassis.setPose(0, 0, 90);
    chassis.moveToPoint(chassis.getPose().x + 34, chassis.getPose().y, 1200,
                        {.minSpeed = 30}, false);
    chassis.turnToPoint(chassis.getPose().x + 7, chassis.getPose().y - 1, 500,
                        {.minSpeed = 30}, false);
    chassis.moveToPoint(chassis.getPose().x + 7, chassis.getPose().y - 1, 600,
                        {.minSpeed = 10});
    pros::delay(200);
    rightArm.set_value(true);
    chassis.waitUntilDone();
    chassis.moveToPoint(chassis.getPose().x - 7, chassis.getPose().y + 1, 800,
                        {.forwards = false}, false);
    rightArm.set_value(false);
    chassis.turnToHeading(118, 600, {}, false);
    lift.move(127);
    pros::delay(700);
    lift.move(-127);
    pros::delay(700);
    lift.brake();
    chassis.turnToHeading(225, 500, {}, false);
    intake.move(127);
    chassis.moveToPoint(chassis.getPose().x - 20, chassis.getPose().y - 20, 1000);
    chassis.turnToHeading(315, 500, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 11, chassis.getPose().y - 11, 1000, {.forwards = false, .maxSpeed = 50});
    pros::delay(700);
    clamp.set_value(true);
    chain.move(85);
    chassis.turnToHeading(225, 500, {}, false);
    chassis.moveToPoint(chassis.getPose().x - 17, chassis.getPose().y - 23, 700);
    topRing.set_value(true);
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPoint(chassis.getPose().x + 10, chassis.getPose().y + 10, 700, {.forwards = false});
    pros::delay(200);
    topRing.set_value(false);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 8, chassis.getPose().y, 1000);
    // chassis.swingToHeading(135, lemlib::DriveSide::LEFT, 500);
    lift.move(127);
    pros::delay(550);
    lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift.brake();

    // OLD PATH CODE
    // ---------------------------------------------------------------------------------------------
    // chassis.moveToPoint(chassis.getPose().x + 29, chassis.getPose().y, 910,
    // {.minSpeed = 30, .earlyExitRange = 1},
    //                     false);
    // chassis.swingToHeading(135, lemlib::DriveSide::RIGHT, 800, {.minSpeed =
    // 30, .earlyExitRange = 1}, false); chassis.moveToPoint(chassis.getPose().x
    // + 10, chassis.getPose().y - 10, 700, {.minSpeed = 30}, false);
    // leftArm.set_value(true);
    // pros::delay(100);
    // chassis.swingToHeading(180, lemlib::DriveSide::LEFT, 500);
    // chassis.turnToHeading(154, 1000, {.minSpeed = 30, .earlyExitRange = 1},
    // false); leftArm.set_value(false); pros::delay(1000);
    // chassis.moveToPoint(chassis.getPose().x - 1, chassis.getPose().y + 2.5,
    // 500, {.forwards = false}); lift.move(127); pros::delay(1000);
    // lift.move(-127);
    // pros::delay(600);
    // lift.brake();
    // chassis.waitUntilDone();
    // chassis.turnToHeading(225, 1000, {}, false);
    // intake.move(127);
    // chassis.moveToPoint(chassis.getPose().x - 17, chassis.getPose().y - 13,
    // 900, {}, false); leftArm.set_value(true); chassis.turnToHeading(0, 1000,
    // {}, false); chassis.moveToPoint(chassis.getPose().x + 6,
    // chassis.getPose().y - 19, 1000, {.forwards = false}, false);
    // clamp.set_value(true);
    // chain.move(85);
    // pros::delay(200);
    // leftArm.set_value(false);
    // chassis.turnToHeading(135, 1000, {}, false);
    // chassis.moveToPoint(chassis.getPose().x + 9, chassis.getPose().y - 9,
    // 1000);
  }
}