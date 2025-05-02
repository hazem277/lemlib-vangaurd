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
   chassis.moveToPoint(chassis.getPose().x - 0.75, chassis.getPose().y - 2, 1000, {.forwards = false});
   lift.move(127);
   pros::delay(1000);
   lift.move(-127);
   pros::delay(600);
   lift.brake();
   chassis.waitUntilDone();
   chassis.turnToHeading(315, 1000, {}, false);
   intake.move(127);
   chassis.moveToPoint(chassis.getPose().x - 17, chassis.getPose().y + 11, 900, {}, false);
   rightArm.set_value(true);
   chassis.turnToHeading(180, 1000, {}, false);
   chassis.moveToPoint(chassis.getPose().x + 3, chassis.getPose().y + 19, 1000, {.forwards = false}, false);
   clamp.set_value(true);
   chain.move(85);
   pros::delay(200);
   rightArm.set_value(false);
   chassis.turnToHeading(45, 1000, {}, false);
   chassis.moveToPoint(chassis.getPose().x + 9, chassis.getPose().y + 9, 1000);
}