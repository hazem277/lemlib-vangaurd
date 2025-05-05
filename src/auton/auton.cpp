#include "main.h"
#include "auton.h"
#include "blueneg.h"
#include "bluepos.h"
#include "redneg.h"
#include "redpos.h"
#include "drivercontrol.h"
#include "skills.h"

auton_type autonType    = BLUE_POSITIVE;
bool autonConfirmed     = true;
bool scoreAllianceStake = false;
bool isRed              = true;

enum wallStakePos { PASSIVE, ACTIVE, SCORING };

void eject() {
  while (true) {
    if (isIntaking && ejectOn) { // red ≈ 14 | blue ≈ 219 | none ≈ 63
      if ((opticalSensor.get_hue() > 210 && opticalSensor.get_hue() < 230 &&
           isRed) ||
          (opticalSensor.get_hue() > 5 && opticalSensor.get_hue() < 20 &&
           (!isRed))) {
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
  }
  else if (pos == ACTIVE) {
    wallStakeEnc.reset_position();
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(25);
    while (wallStakeEnc.get_position() < 4700) { pros::delay(10); }
    lift.brake();
  }
  else if (pos == SCORING) {
    lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift.move_relative(310, 127);
  }
}

void runAuton() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

  pros::delay(100);
  if (autonType == RED_POSITIVE || autonType == RED_NEGATIVE) { isRed = 1; }
  else if (autonType == BLUE_POSITIVE || autonType == BLUE_NEGATIVE) {
    isRed = 0;
  }
  pros::Task EJECT_RING(eject);

  switch (autonType) {
    case NONE: break;

    case RED_POSITIVE: red_pos(); break;

    case RED_NEGATIVE: red_neg(); break;

    case BLUE_POSITIVE: blue_pos(); break;

    case BLUE_NEGATIVE: blue_neg(); break;

    case SKILLS: skills(); break;
  }

  EJECT_RING.remove();
}