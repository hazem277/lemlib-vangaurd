#include "auton.h"
#include "main.h"

void red_neg() {
  chassis.setPose(0, 0, 220);
  lift.move(127);
  pros::delay(800);
  chassis.moveToPoint(chassis.getPose().x + 5, chassis.getPose().y + 5, 1000);
  lift.move(-127);
  pros::delay(800);
  lift.brake();
  chassis.turnToPoint(chassis.getPose().x + 22, chassis.getPose().y + 2, 1000, {.forwards = false}, false);
  chassis.moveToPoint(chassis.getPose().x + 22, chassis.getPose().y + 2, 2000, {.forwards = false}, false);
  clamp.set_value(true);
}