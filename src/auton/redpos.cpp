#include "auton.h"
#include "main.h"

void red_pos() {
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0,10,10000);
   // chassis.setPose(60, 13, 145);
   // lift.move(127);
   // pros::delay(800);
   // lift.move(-127);
   
   // pros::delay(400);
   // chassis.turnToPoint(40, 40, 1500);
   // chassis.waitUntilDone();
   // lift.brake();    
   // chassis.moveToPose(10, 30, 270, 1250, { .maxSpeed = 80});
   // chassis.waitUntilDone();
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