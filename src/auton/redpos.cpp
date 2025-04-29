#include "auton.h"
#include "main.h"

void red_pos() {
   chassis.setPose(60, 10, 145);
   lift.move(127);
   pros::delay(800);
   lift.move(-127);
   
   pros::delay(400);
   chassis.turnToPoint(25, 40, 5000, {}, false);
   lift.brake(); 
   chassis.moveToPose(0, 20, 270, 5000, { .lead = .8, .earlyExitRange = 40 });
   // // chassis.waitUntilDone();
   // clamp.set_value(true);



   // pros::delay(200);
   // intake.move(127);
   // chassis.turnToHeading(180, 200);
   
   // chassis.moveToPoint(30, 47, 2300);
   // chassis.turnToHeading(0, 2000);
   // chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
   // chassis.waitUntilDone();
   // isClamped = true;
}