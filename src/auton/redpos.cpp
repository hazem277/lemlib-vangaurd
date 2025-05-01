#include "auton.h"
#include "main.h"

void red_pos() {
   chassis.setPose(0, 0, 90);
   chassis.moveToPoint(chassis.getPose().x + 30, chassis.getPose().y, 1000, {.minSpeed = 30, .earlyExitRange = 1}, false);
   chassis.swingToHeading(45, lemlib::DriveSide::LEFT, 1000, {.minSpeed = 30, .earlyExitRange = 1}, false);
   chassis.moveToPoint(chassis.getPose().x + 10, chassis.getPose().y + 10, 1000, {.minSpeed = 30}, false);
   rightArm.set_value(true);
   pros::delay(100);
   chassis.swingToHeading(0, lemlib::DriveSide::RIGHT, 1000);
   chassis.turnToHeading(20, 1000, {.minSpeed = 30, .earlyExitRange = 1}, false);
   rightArm.set_value(false);
   pros::delay(1000);
   chassis.moveToPoint(chassis.getPose().x - 1, chassis.getPose().y - 2.67, 1000, {.forwards = false});
   lift.move(127);
   pros::delay(800);
   lift.move(-127);
   pros::delay(400);
   lift.brake();
}