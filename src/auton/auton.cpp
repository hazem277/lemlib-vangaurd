#include "auton.h"
#include "redpos.h"
#include "redneg.h"
#include "bluepos.h"
#include "blueneg.h"
#include "skills.h"
#include "drivercontrol.h"
#include "fmt/format.h" // IWYU pragma: keep
#include "lemlib-tarball/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/abstract_motor.hpp"// IWYU pragma: keep
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cmath>
#include <ratio>

auton_type autonType = NONE;
bool scoreAllianceStake = true;
bool autonConfirmed = false;

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
    red_pos();
  }
  else if (autonType == RED_POSITIVE && !scoreAllianceStake) {
    // chassis.setPose(60, 27,90);
    // chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    // chassis.waitUntilDone();
    // clamp.set_value(true);
    // pros::delay(200);
    // intake.move(127);
    // chassis.turnToHeading(180, 200);
    
    // chassis.moveToPoint(30, 47, 2300);
    // chassis.turnToPoint(25,0, 2000);
    // chassis.moveToPoint(25, 0, 2000, {.maxSpeed = 80});
    // chassis.waitUntilDone();
    // isClamped = true;
  }
  else if (autonType == RED_NEGATIVE && scoreAllianceStake) {
    red_neg();
  }
  else if (autonType == RED_NEGATIVE && !scoreAllianceStake){
    // chassis.setPose(60, -27, 90);
    // chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    // chassis.waitUntilDone();
    // clamp.set_value(true);
    // pros::delay(200);
    // intake.move(127);
    // chassis.turnToHeading(0, 200);

    // chassis.moveToPoint(30, -47, 2300);

    // chassis.turnToPoint(16, -48, 500);
    // chassis.moveToPoint(16, -48, 2000, {.maxSpeed = 70});
    // chassis.waitUntilDone();
    // pros::delay(500);
    // chassis.moveToPoint(32, -48, 1000, {.forwards = false});
    // chassis.turnToPoint(17, -53, 700);
    // chassis.moveToPoint(17, -53, 2000);
    // chassis.waitUntilDone();
    // pros::delay(300);
    // chassis.turnToPoint(30,0,800);
    // chassis.moveToPoint(30,-5,1000);
    // isClamped = true;

  }
  else if (autonType == BLUE_POSITIVE && scoreAllianceStake) {
    blue_pos();
  }

  else if (autonType == BLUE_POSITIVE && !scoreAllianceStake) {
    // chassis.setPose(60, -27, 90);
    // chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    // chassis.waitUntilDone();
    // clamp.set_value(true);
    // pros::delay(200);
    // intake.move(127);
    // chassis.turnToHeading(0, 200);

    // chassis.moveToPoint(30, -47, 2300);
    // chassis.turnToHeading(180,2000);
    // chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    // // chassis.waitUntilDone();
    // isClamped = true;
  }

  else if (autonType == BLUE_NEGATIVE && scoreAllianceStake) {
    blue_neg();
  }

  else if (autonType == BLUE_NEGATIVE && !scoreAllianceStake) {
    // chassis.setPose(60, 27, 90 );
    
    // chassis.turnToPoint(30, 27, 700, {.forwards = false});
    // chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    // chassis.waitUntilDone();
    // clamp.set_value(true);
    // pros::delay(200);
    // intake.move(127);
    // chassis.turnToHeading(180, 200);
    
    // chassis.moveToPoint(30, 47, 2300);
  
    // chassis.turnToPoint(14.5, 48, 500);
    // chassis.moveToPoint(14.5, 48, 2000, {.maxSpeed = 70});
    // chassis.waitUntilDone();
    // pros::delay(500);
    // chassis.moveToPoint(30, 48, 1000, {.forwards = false});
    // chassis.turnToPoint(15, 54, 700);
    // chassis.moveToPoint(15, 54, 2000);
    // chassis.waitUntilDone();
    // chassis.turnToPoint(38,0,1000);
    // chassis.moveToPoint(38,0,1000);
    // intake.brake();
    // chassis.turnToPoint(50,-30,2000);
    // chassis.moveToPose(50,-27,180,2400);
    // isClamped = true;
  }

  else if (autonType == SKILLS) {
    skills();
  }
  EJECT_RING.remove();
}