#include "auton.h"                    // IWYU pragma: keep
#include "drivercontrol.h"            // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp" // IWYU pragma: keep
#include "main.h"                     // IWYU pragma: keep

void skills() {
  chassis.setPose(0, 0, 289);
  pros::Task AVERAGE_IMU(imuAverage);
  pros::Task detectTheColor(colorDetector2);

  pros::delay(200);
  intake.move(100);
  chassis.moveToPoint(chassis.getPose().x - 15, chassis.getPose().y + 5.33, 800,
                      {.maxSpeed = 70}, false);
  chassis.moveToPoint(chassis.getPose().x - 10, chassis.getPose().y + (3), 800,
                      {}, false);
  chassis.turnToPoint(chassis.getPose().x - 6.7, chassis.getPose().y - 7.7, 600,
                      {}, false);
  intake.move(0);
  chassis.moveToPoint(chassis.getPose().x - 6.7, chassis.getPose().y - 7.7, 800,
                      {}, false);
  intake.move(-127);
  liftM.move(-127);
  pros::delay(1000);
  intake.move(0);
  liftM.move(0);
  chassis.moveToPoint(chassis.getPose().x + 4, chassis.getPose().y + 4, 500,
                      {.forwards = false}, false);
  chassis.turnToPoint(chassis.getPose().x + 24.6, chassis.getPose().y + 29.2,
                      800, {}, false);
  chassis.moveToPoint(chassis.getPose().x + 24.6, chassis.getPose().y + 29.2,
                      2000, {.maxSpeed = 70}, false);
  chassis.turnToPoint(chassis.getPose().x + 60, chassis.getPose().y, 800,
                      {}, false);
  matchL1.set_value(1);
  matchL2.set_value(1);
  pros::delay(200);
  intake.move(127);
  liftM.move(127);
  chassis.moveToPoint(chassis.getPose().x + 60, chassis.getPose().y , 1000,
                      {.maxSpeed = 60}, false);
  detectTopColor();
  pros::delay(1000);
  chassis.turnToPoint(chassis.getPose().x - 30, chassis.getPose().y +.25, 800,
                      {.forwards = false}, false);
  chassis.moveToPoint(chassis.getPose().x - 30, chassis.getPose().y+.25 , 1200,
                      {.forwards = false, .maxSpeed = 80}, false);

  intake.move(125);
  liftM.move(125);
  liftI.move(125);
  pros::delay(1000);
  chassis.setPose(0, 0, 90);
  pros::delay(2000);
  matchL1.set_value(0);
  matchL2.set_value(0);
  liftM.move(0);
  liftI.move(0);
  chassis.moveToPoint(chassis.getPose().x + 5, chassis.getPose().y, 1000, {},
                      false);
  chassis.turnToPoint(chassis.getPose().x, chassis.getPose().y - 50, 700, {},
                      false);
  chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y - 50, 2500, {},
                      false);
  chassis.turnToPoint(chassis.getPose().x - 8.4, chassis.getPose().y - 20, 700,
                      {}, false);
  chassis.moveToPoint(chassis.getPose().x - 13.2, chassis.getPose().y - 30, 2500,
                      {.maxSpeed = 50}, false);
  pros::delay(300);
  chassis.turnToPoint(chassis.getPose().x - 11.5, chassis.getPose().y + 12.88, 800,
                      {.forwards = false}, false);
  chassis.moveToPoint(chassis.getPose().x - 11.5, chassis.getPose().y + 12.88,
                      1500, {.forwards = false, .maxSpeed = 40}, false);
  liftM.move(127);
  liftI.move(-127);
  pros::delay(2000);
  chassis.moveToPoint(chassis.getPose().x + 4, chassis.getPose().y - 4, 500,
                      {.forwards = false}, false);
  chassis.turnToPoint(chassis.getPose().x + 25, chassis.getPose().y - 32, 800,
                      {}, false);
  chassis.moveToPoint(chassis.getPose().x + 25, chassis.getPose().y - 32,
                      2000, {.maxSpeed = 80}, false);
  chassis.turnToPoint(chassis.getPose().x + 60, chassis.getPose().y, 800,
                      {.maxSpeed = 60}, false);
  matchL1.set_value(1);
  matchL2.set_value(1);
  pros::delay(200);
  intake.move(127);
  liftM.move(60);
  chassis.moveToPoint(chassis.getPose().x + 60, chassis.getPose().y, 1000,
                      {.maxSpeed = 70}, false);
  pros::delay(100);
  detectTopColor();
  chassis.turnToPoint(chassis.getPose().x - 30, chassis.getPose().y-.5, 1200,
                      {.forwards = false}, false);
  chassis.moveToPoint(chassis.getPose().x - 30, chassis.getPose().y-.5, 1200,
                      {.forwards = false, .maxSpeed = 80}, false);
  matchL1.set_value(0);
  matchL2.set_value(0);
  intake.move(125);
  liftM.move(125);
  liftI.move(125);
  pros::delay(2000);
  
  chassis.turnToPoint(chassis.getPose().x+4,chassis.getPose().y,600,{.maxSpeed=50},false);
  chassis.moveToPoint(chassis.getPose().x+4,chassis.getPose().y,600,{.maxSpeed=50},false);
  chassis.turnToPoint(chassis.getPose().x,chassis.getPose().y+20, 800,{},false);

  chassis.moveToPoint(chassis.getPose().x,chassis.getPose().y+50, 2400,{.maxSpeed=80},false);

  chassis.turnToPoint(chassis.getPose().x+30,chassis.getPose().y,600,{.forwards=false,.minSpeed=127},false);
  chassis.moveToPoint(chassis.getPose().x+30,chassis.getPose().y,7000,{.forwards=false,.minSpeed=127},false);
}