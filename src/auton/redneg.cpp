#include "auton.h"
#include "main.h"

void red_neg() {
  chassis.setPose(0, 0, 220);
  lift.move(127);
  pros::delay(800);
  chassis.moveToPoint(chassis.getPose().x + 10, chassis.getPose().y + 10, 1000, {.forwards = false});
  lift.move(-127);
  pros::delay(500);
  lift.brake();
  intake.move(127);
  // chassis.turnToHeading(50, 1000);
  // chassis.moveToPose(chassis.getPose().x + 35, chassis.getPose().y + 7, 90, 4000, {.lead = 0.6, .minSpeed = 90, .earlyExitRange = 40});
  chassis.turnToPoint(chassis.getPose().x + 49, chassis.getPose().y + 8, 1000, {}, false);
  chassis.moveToPoint(chassis.getPose().x + 49, chassis.getPose().y + 8, 2000, {}, false);
  leftArm.set_value(true);
}