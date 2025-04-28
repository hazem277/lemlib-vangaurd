#include "auton.h"
#include "main.h"

void red_neg() {
   chassis.setPose(60, -17, 180);
   chassis.moveToPose(60, 0, 180, 1500, {.forwards = false, .maxSpeed = 70});
   chassis.turnToHeading(270, 700);
   chassis.moveToPoint(73, chassis.getPose().y, 10000, {.forwards = false, .maxSpeed = 45});
   while (distance.get_distance() > 90) {
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