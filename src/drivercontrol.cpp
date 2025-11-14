#include "drivercontrol.h" // IWYU pragma: keep
#include "auton/auton.h"         // IWYU pragma: keep
#include "graphics.h"
#include "main.h"
#include "pros/abstract_motor.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "pros/motors.h" // IWYU pragma: keep
#include <ctime>
/** 
*@brief
*Toggle variable for the match loader
**/
bool isPoppedDown = false;
/** 
*@brief
*Toggle variable for intake system
**/
bool isIntaking = false;
/** 
*@brief
*Toggle variable to know if the intake is reversed
**/
bool intakeReversed = false;
/** 
*@brief
*boolean that is true when same color block is in your top intake
**/
bool colorDetect = false;
/** 
*@brief
*boolean that turns on debug screen if needed
**/
bool debugMode = false;
/** 
*@brief
*When on then the blocks will be thrown out of our intake
**/
bool ejectOn = true;
/** 
*@brief
*Boolean that flips if top intake chain is moving fwds
**/
bool chainFwd= false;
/** 
*@brief
*Boolean that flips if top intake chain is moving in reverse
**/
bool chainRvs = false;
/** 
*@brief
*When true, indexer spins in reverse to score on the middle goal
**/
bool scoreToggle = false;
/** 
*@brief
*Boolean for toggle on the top descore mech
**/
bool descoreMech = false;
/** 
*@brief
*Boolean to know if it needs to stop the intake when it detects the color
**/
bool stopIntake = false;
/** 
*@brief
*Boolean for toggle on the side descore mechanism
**/
bool isDescoring = true;
/** 
*@brief
*Runs toggles for all of the buttons on the controller to carry out tasks. Used in conjunction with the variables (See below)
**/
void buttonControls() {
  while (true) {
    // clamp
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      if (isPoppedDown) {
        matchL1.set_value(false);
        matchL2.set_value(false);
        isPoppedDown = false;
        pros::delay(100);
      } else if (!isPoppedDown){
        matchL1.set_value(true);
        matchL2.set_value(true);
        isPoppedDown = true;
        pros::delay(100);
      }
    }


    // intake
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (!isIntaking || !intakeReversed) {
        intake.move(-127);
        isIntaking = true;
        intakeReversed = true;
      }
      else if (isIntaking && intakeReversed) {
        intake.brake();
        isIntaking = false;
        intakeReversed = false;
      }
    }
    else if (controller.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_R1)) {
      if (!isIntaking || intakeReversed) {
        intake.move(127);
  
        isIntaking = true;
        intakeReversed = false;
      }
      else if (isIntaking && !intakeReversed ) {
        intake.brake();
     
        isIntaking = false;
      }
      else if (isIntaking && !intakeReversed) {

        isIntaking = false;
      }
      
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
    if(intakeStopped){
      intakeStopped=false;
      stopIntake=false;
      controller.clear_line(0);
      if(!chainFwd && scoreToggle){
        liftI.move(-127);
        liftM.move(127);
        chainFwd = true;
        chainRvs = false;
      }else if (!chainFwd && !scoreToggle){
        liftI.move(127);
        liftM.move(127);
        chainFwd = true;
        chainRvs = false;
      }else if (chainFwd){
        liftI.move(0);
        liftM.move(0);
        chainFwd = false;
        chainRvs=false;
      }
    pros::delay(75);
      controller.set_text(0,0,"off");
    }else if (!intakeStopped){
        stopIntake=true;
        controller.clear_line(0);
          if(!chainFwd && scoreToggle){
          liftI.move(-127);
          liftM.move(127);
          chainFwd = true;
          chainRvs = false;
      }else if (!chainFwd && !scoreToggle){
         liftI.move(127);
         liftM.move(127);
         chainFwd = true;
         chainRvs = false;
      }else if (chainFwd){
         liftI.move(0);
         liftM.move(0);
         chainFwd = false;
         chainRvs=false;
      }
        pros::delay(75);
        controller.set_text(0,0,"on");
    }
    }else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
      if(!chainRvs){
        liftM.move(-127);
        liftI.move(0);
        chainFwd = false;
        chainRvs=true;
      }else{
        liftM.move(0);
        liftI.move(0);
        chainRvs = false;
        chainFwd=false;
      }
    }
    
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
      scoreToggle= !scoreToggle;
      if(scoreToggle){
        controller.clear_line(1);
        pros::delay(100);
        controller.set_text(1,0,"Top");
      }else{
      controller.clear_line(1);
      pros::delay(100);
      controller.set_text(1,0,"middle");
    }
      }
    // DESCORE MECH
    //----------------------------------------------------------------------------------------------------------------------
      if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        if(!descoreMech){
          descore.set_value(1);
        descoreMech = true;
      }else if(descoreMech){
        descore.set_value(0);
        descoreMech = false;
        }
      }


    // DEBUG SCREEN (LVGL - graphics.cpp)
    // ---------------------------------------------------------------------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && !debugMode) {
      lv_scr_load_anim(screenDebug, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
               debugMode) {
      // lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        pros::delay(50);
      }
    }

    // Ejection toggle

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && ejectOn) {
      ejectOn = false;
      controller.clear_line(0);
      controller.set_text(1, 1, "Example text");
      
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) &&
               !ejectOn) {

      ejectOn = true;
      controller.clear_line(2);
      controller.set_text(0, 0, "Example text");
    }

     //top descore mech

  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
    if(isDescoring){
      topDescore.set_value(0);
      isDescoring = false;
    }else{
      topDescore.set_value(1);
      isDescoring = true;
    }
  }
  } 

 
}