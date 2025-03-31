#include "auton.h"
#include "drivercontrol.h"
#include "fmt/format.h" // IWYU pragma: keep
#include "lemlib-tarball/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cmath>

auton_type autonType = SKILLS;
bool scoreAllianceStake = true;
bool autonConfirmed = true;

ASSET(skills_path_txt);

lemlib_tarball::Decoder decoder(skills_path_txt);

void clampSet(bool value) {
  clamp.set_value(value);
  clamp2.set_value(value);
}

enum wallStakePos { PASSIVE, ACTIVE, SCORING };
bool isRed = 1;
void eject(){
  while(1){
  if (isIntaking && ejectOn) { // red ≈ 14 | blue ≈ 219 | none ≈ 63
    if ((opticalSensor.get_hue() > 210 && opticalSensor.get_hue() < 230 && isRed) || (opticalSensor.get_hue() > 5 && opticalSensor.get_hue() < 20 && (!isRed))) {
      pros::delay(295);
      intake.brake();
      pros::delay(200);
      intake.move(127);
    }
  }
    pros::delay(33);
  }
}

void setWallStakePos(wallStakePos pos) {
  if (pos == PASSIVE) {
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    lift.brake();
  } else if (pos == ACTIVE) {
    wallStakeEnc.reset_position();
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(25);
    while (wallStakeEnc.get_position() < 4700) {
      pros::delay(10);
    }
    lift.brake();
  } else if (pos == SCORING) {
    lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift.move_relative(310, 127);
  }
}

void runAuton() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

  while (!autonConfirmed) {
    pros::delay(50);
  }
  pros::delay(100);
  if(autonType == RED_POSITIVE || autonType == RED_NEGATIVE){
    isRed = 1;
  }else if (autonType == BLUE_POSITIVE || autonType == BLUE_NEGATIVE){
    isRed = 0;
  }
  pros::Task EJECT_RING(eject);
  if (autonType == RED_POSITIVE && scoreAllianceStake) {
 
    chassis.setPose(60, 17, 0);
    chassis.moveToPose(60, 0, 0, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, chassis.getPose().y, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 90) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
    chassis.turnToHeading(0, 2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == RED_POSITIVE && !scoreAllianceStake) {
    chassis.setPose(60, 27,90);
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
    chassis.turnToPoint(25,0, 2000);
    chassis.moveToPoint(25, 0, 2000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == RED_NEGATIVE && scoreAllianceStake) {
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
    clamp2.set_value(true); 
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
  else if (autonType == RED_NEGATIVE && !scoreAllianceStake){
    chassis.setPose(60, -27, 90);
    chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clampSet(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);

    chassis.turnToPoint(16, -48, 500);
    chassis.moveToPoint(16, -48, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(32, -48, 1000, {.forwards = false});
    chassis.turnToPoint(17, -53, 700);
    chassis.moveToPoint(17, -53, 2000);
    chassis.waitUntilDone();
    pros::delay(300);
    chassis.turnToPoint(30,0,800);
    chassis.moveToPoint(30,-5,1000);
    isClamped = true;

  }
  else if (autonType == BLUE_POSITIVE && scoreAllianceStake) {
 
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, 0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, chassis.getPose().y, 10000, {.forwards = false, .maxSpeed = 27});
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
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);
    chassis.turnToHeading(180,2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    // chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_POSITIVE && !scoreAllianceStake) {
    chassis.setPose(60, -27, 90);
    chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);
    chassis.turnToHeading(180,2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    // chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_NEGATIVE && scoreAllianceStake) {
   
    chassis.setPose(60, 17, 0);
    chassis.moveToPose(60, 0, 0, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 90) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
  
    chassis.turnToPoint(19, 47.5, 500);
    chassis.moveToPoint(19, 47.5, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(30, 48, 1000, {.forwards = false});
    chassis.turnToPoint(19, 53, 700);
    chassis.moveToPoint(19, 53, 2000);
    chassis.waitUntilDone();
    
    // chassis.turnToPoint(30,0, 700,{.forwards = false});
    // chassis.moveToPoint(42, -48, 10000, {.forwards = false});
    // pros::delay(500);
    // intake.brake();
    // isClamped = true;
   
  }

  else if (autonType == BLUE_NEGATIVE && !scoreAllianceStake) {
    chassis.setPose(60, 27, 90 );
    
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
  
    chassis.turnToPoint(14.5, 48, 500);
    chassis.moveToPoint(14.5, 48, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(30, 48, 1000, {.forwards = false});
    chassis.turnToPoint(15, 54, 700);
    chassis.moveToPoint(15, 54, 2000);
    chassis.waitUntilDone();
    chassis.turnToPoint(38,0,1000);
    chassis.moveToPoint(38,0,1000);
    intake.brake();
    chassis.turnToPoint(50,-30,2000);
    chassis.moveToPose(50,-27,180,2400);
    isClamped = true;
  }

  else if (autonType == SKILLS) {
    chassis.setPose(-62, 0, 90);
    intake.move(127);
    pros::delay(300);
    intake.brake();
    chassis.moveToPoint(-56, 0, 700, {.minSpeed = 100});
    chassis.turnToHeading(180, 700, {.minSpeed = 100});
    chassis.moveToPoint(chassis.getPose().x, 20, 850, {.forwards = false, .maxSpeed = 80}, false);
    // chassis.waitUntilDone();
    clampSet(true); // Mogo 1
    chassis.turnToHeading(90, 700, {.minSpeed = 100}, false);
    // chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPoint(-32, chassis.getPose().y, 1500, {.minSpeed = 100}); // Ring 1
    chassis.turnToHeading(45, 700, {.minSpeed = 100});
    chassis.moveToPose(27, 42, 90, 2500, {.minSpeed = 100}, false); // Ring 2
    // chassis.waitUntilDone();
    chassis.turnToPoint(6, chassis.getPose().y - 4, 1000, {.forwards = false, .minSpeed = 100});
    chassis.moveToPoint(6, chassis.getPose().y - 4, 1000, {.forwards = false, .minSpeed = 100});
    chassis.turnToHeading(0, 700, {}, false);
    // chassis.waitUntilDone();
    
    setWallStakePos(ACTIVE); // Wall Stake 1
    chassis.moveToPoint(chassis.getPose().x, 45, 1000, {.minSpeed = 100}, false);
    // chassis.waitUntilDone();
    pros::delay(1500);
    intake.brake();
    chassis.moveToPoint(chassis.getPose().x, 53, 700, {.minSpeed = 100});
    setWallStakePos(SCORING);
    pros::delay(1750);
    setWallStakePos(PASSIVE);

    chassis.moveToPoint(chassis.getPose().x, 38, 1000, {.forwards = false});
    chassis.turnToHeading(270, 700, {}, false);
    // chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPoint(-58, chassis.getPose().y, 3000, {.maxSpeed = 70, .minSpeed = 10, .earlyExitRange = 30}); // Ring 3
    chassis.moveToPoint(-58, chassis.getPose().y, 3000, {.maxSpeed = 40});
    chassis.turnToPoint(-46, 38, 700,{.forwards = false});
    chassis.moveToPoint(-46, 38, 700, {.forwards = false, .maxSpeed = 70}); // Align 1
    chassis.turnToHeading(0, 700, {}, false);
    // chassis.waitUntilDone();
    chassis.moveToPoint(chassis.getPose().x, 52, 1000, {}, false);
    // chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveToPoint(-44, 42, 700, {.forwards = false});
    chassis.turnToHeading(135, 700);
    chassis.moveToPoint(-70, 70, 1000, {.forwards = false});
    chassis.turnToHeading(135,400, {}, false);
    // chassis.waitUntilDone();
    chassis.setPose(-62,64,135); // SET POSE HERE!!!
    intake.brake();
    clampSet(false);
    pros::delay(500);
    chassis.moveToPoint(-52.5, 38, 900);
    chassis.turnToHeading(0, 800);
    pros::delay(1000);
    chassis.moveToPoint(chassis.getPose().x, -17, 1500, {.forwards = false}, false); // AUTO STOPS HERE! ------------------------------------------------

    // chassis.waitUntilDone();
    clampSet(true); // Mogo 2

    // mirrored
    chassis.turnToHeading(90, 700, {}, false);
    // chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPoint(-23, -18, 1500, {.maxSpeed = 80});
    chassis.turnToHeading(145, 700, {.minSpeed = 100});
    chassis.moveToPose(29, -36, 90, 2500, {.minSpeed = 100});
    chassis.turnToPoint(0, -29, 1000, {.forwards = false},false);
    chassis.moveToPoint(0, -29, 1000, {.forwards = false},false);
    chassis.turnToHeading(180, 700, {}, false);
    // chassis.waitUntilDone();
    setWallStakePos(ACTIVE); // Wall Stake 2
    chassis.moveToPoint(chassis.getPose().x, -45, 1000, {.minSpeed = 100}, false);
    // chassis.waitUntilDone();
    pros::delay(2000);
    intake.brake();
    chassis.moveToPoint(chassis.getPose().x, -53, 700);
    setWallStakePos(SCORING);
    pros::delay(1250);
    setWallStakePos(PASSIVE);

    chassis.moveToPoint(chassis.getPose().x, -38, 1000, {.forwards = false},false);
    chassis.turnToHeading(270, 700,{},false);
    // chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPoint(-56, chassis.getPose().y, 3000, {.maxSpeed = 50},false); // Ring 3
    chassis.turnToPoint(-47, -34, 700,{.forwards = false});
    chassis.moveToPoint(-47, -34, 700, {.forwards = false, .maxSpeed = 50},false); // Align 1
    chassis.turnToHeading(180, 700);
    chassis.moveToPoint(chassis.getPose().x, -52, 1000, {}, false);
    // chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveToPoint(-44, -42, 700, {.forwards = false});
    chassis.turnToHeading(45, 700,{},false);
    chassis.moveToPoint(-59, -59, 700, {.forwards = false}, false);
    // chassis.waitUntilDone();
    intake.brake();
    clampSet(false);
    // MOGO 3 PATH
    intake.move(-127);
    clampSet(false);
    pros::delay(500);
    intake.brake();
    chassis.moveToPoint(-53, -57, 900);
    chassis.turnToHeading(270, 700, {.minSpeed = 100},false);
    chassis.moveToPose(58, 10, 60, 3000, {.forwards = false, .lead = 0.8},false);
    clampSet(true);
  }
  EJECT_RING.remove();
}