#include "auton.h" // IWYU pragma: keep
#include "main.h" // IWYU pragma: keep
#include "drivercontrol.h"
/**
* @brief
*
**/
void blue_left() {   
chassis.setPose(0,0,251);
  pros::Task AVERAGE_IMU(imuAverage);
  pros::Task detectTheColor(colorDetector);
  pros::delay(200);
  intake.move(100);
  chassis.moveToPoint(chassis.getPose().x-15,chassis.getPose().y-5.33,800,{.maxSpeed=70},false);
  chassis.moveToPoint(chassis.getPose().x-9,chassis.getPose().y-(2.7),800,{},false);
  
  chassis.turnToPoint(-35,1.5,800,{.forwards=false},false);
  intake.move(0);

  chassis.moveToPoint(-35,1.5,1000,{.forwards=false},false);
  intake.move(127);
  liftM.move(127);
  liftI.move(-60);
  pros::delay(1600);
  intake.move(0);
  liftM.move(0);
  liftI.move(0);
  chassis.moveToPoint(chassis.getPose().x+4,chassis.getPose().y-4,500,{.forwards=false},false);
  chassis.turnToPoint(chassis.getPose().x+27,chassis.getPose().y-33,800,{},false);
  chassis.moveToPoint(chassis.getPose().x+27,chassis.getPose().y-33,1800,{.maxSpeed=90},false);
  chassis.turnToHeading(90,800,{},false);
  matchL1.set_value(1);
  matchL2.set_value(1);
  pros::delay(200);
  intake.move(127);
  chassis.moveToPoint(chassis.getPose().x+60,chassis.getPose().y,1000,{.maxSpeed=60},false);
  pros::delay(500);
  detectColor();
chassis.turnToPoint(chassis.getPose().x-30,chassis.getPose().y-.25,600,{.forwards=false},false);
chassis.moveToPoint(chassis.getPose().x-30,chassis.getPose().y-.25,1200,{.forwards=false, .maxSpeed=80},false);
matchL1.set_value(0);
matchL2.set_value(0);
intake.move(125);
liftM.move(125);
liftI.move(125);
isRed=true;
while(1){
if(!colorDetect){
  liftI.move(127);
}else{
   liftI.move(-127);  
        pros::delay(400);
}

}
}