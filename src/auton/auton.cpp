#include "auton.h"
#include "blueRight.h"
#include "blueLeft.h"
#include "drivercontrol.h"
#include "main.h"
#include "redLeft.h"
#include "redRight.h"
#include "skills.h"
/**
* @brief
* Defines autonomous codes for each side, Ex. blue left, blue right, and skills
**/

auton_type autonType = NONE;
/**
* @brief
* Boolean that, when true, will make the autonomous run.
**/
bool autonConfirmed = false;
/**
* @brief
* Used to know what color to eject in the autonomous
**/
bool isRed = true;
/**
* @brief
* Testing variable that is used to run a specific code without needing to select an autonomous
**/
bool testing = false;
/**
* @brief
* boolean to know if the intake was just stopped by the optical sensor
**/
bool intakeStopped = false;
/**
* @brief
* function that averages the inertial sensor values to reduce drift
**/
void imuAverage(){
  imu.set_heading(chassis.getPose().theta);
  imu2.set_heading(chassis.getPose().theta);
  while(true){
    imuAvg.set_heading((imu.get_heading()+(imu2.get_heading()))/2);
  }

}
/**
* @brief
* function that flips a boolean if it detects the correct color in the top intake.
*Used to stop the intake.
**/
void colorDetector(){
  while(true){
    if((topticalSensor.get_hue() > 165 && !isRed) || (topticalSensor.get_hue() < 20 && isRed)){
      colorDetect = true;
    }else {
    colorDetect=false;
    }
  }
}
/**
* @brief
* Same as previous fn but it is impartial to the alliance color
**/

void colorDetector2(){
  while(true){
    if((topticalSensor.get_hue() > 165 || (topticalSensor.get_hue() < 20))){
      colorDetect = true;
    }else {
    colorDetect=false;
    }
  }
}
/**
* @brief
* delays the code until it detects a block in the bottom intake and then stops the intake. 
*This is used in auton when we are at the match loader
**/
void detectColor(){
  while(((bottomSensor.get_hue() < 165 && !isRed) || (bottomSensor.get_hue() > 20 && isRed))){
    pros::delay(10);
  }
    intake.brake();
}
/**
* @brief
* delays the code until it detects a block in the top lift and then stops the intake and lift. 
*This is used in auton when we are at the match loader
**/
void detectTopColor(){
  while(topticalSensor.get_hue() < 165 && topticalSensor.get_hue() > 20){
    pros::delay(1);
  }
  
    liftM.brake();
}
/**
* @brief
* used with the aforementioned colordetect and stopIntake booleans to stop the intake when we first intake our alliance colors block.
*This stops the block from flying out of our intake, and gets rid of the need to micromanage the lift to keep the blocks in.
**/
void stopTheIntake(){
  while(true){
    if(stopIntake && colorDetect&&!intakeStopped){
      liftI.brake();
      liftM.brake();
      intakeStopped = true;
      stopIntake = false;
      chainFwd=false;
      chainRvs=false;
    }
    pros::delay(10);
  }
}

/**
* @brief
* Called during the beginning of the match and starts the autonomous task using a switch.

**/

void runAuton() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

  pros::delay(100);
  if (autonType == RED_RIGHT || autonType == RED_LEFT) {
    isRed = 1;
  } else if (autonType == BLUE_RIGHT || autonType == BLUE_LEFT) {
    isRed = 0;
  }
  switch (autonType) {
  case NONE:
    break;

  case RED_RIGHT:
    red_right();
    break;

  case RED_LEFT:
    red_left();
    break;

  case BLUE_LEFT:
    blue_left();
    break;

  case BLUE_RIGHT:
    blue_right();
    break;

  case SKILLS:
    skills();
    break;
  }
}