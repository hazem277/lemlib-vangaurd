#include "auton.h"
#include "main.h"

void red_pos() {
  if (scoreAllianceStake) {
    chassis.setPose(0, 0, 322);
    lift.move(127);
    pros::delay(850);
    chassis.moveToPoint(chassis.getPose().x + 10, chassis.getPose().y - 5, 1000, {.forwards = false});
    lift.move(-127);
    pros::delay(500);
    lift.brake();
    chassis.turnToHeading(0, 700, {}, false);
    topRing.set_value(true);
    intake.move(127);
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y + 10, 1000, {}, false);
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y - 3, 500, {}, false);
    topRing.set_value(false);
    chassis.turnToHeading(295, 700, {}, false);
    int temp_x, temp_y;
    temp_x = chassis.getPose().x + 23.4;
    temp_y = chassis.getPose().y - 10;
    chassis.moveToPoint(temp_x, temp_y, 700, {.forwards = false, .maxSpeed = 70, .minSpeed = 10, .earlyExitRange = 17});
    chassis.moveToPoint(temp_x, temp_y, 700, {.forwards = false, .maxSpeed = 40});
    pros::delay(700);
    clamp.set_value(true);
    chain.move(85);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(180, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 5, chassis.getPose().y - 19, 1000, {}, false);
    pros::delay(500);
    chassis.turnToHeading(0, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + 12, chassis.getPose().y + 21, 1000);
    chassis.turnToHeading(45, 700);
  }
  else {
    chassis.setPose(0, 0, 90);
    chassis.moveToPoint(chassis.getPose().x + 30, chassis.getPose().y, 1000, {.minSpeed = 30, .earlyExitRange = 1},
                        false);
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
}