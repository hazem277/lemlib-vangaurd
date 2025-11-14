#include "main.h"
#include "auton/auton.h"
#include "drivercontrol.h"
#include "graphics.h" // IWYU pragma: keep
#include "lemlib-tarball/api.hpp" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/asset.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/device.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h" // IWYU pragma: keep
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

// controller
/**
* @brief 
*defines the main controller that we use for moving the robot
**/
pros::Controller controller(pros::E_CONTROLLER_MASTER);
/**
* @brief 
*defines a secondary controller if we want to use one
**/
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
// motor groups
/**
* @brief 
*Left drivetrain motorgroup, negative values indicate it is reversed
**/
pros::MotorGroup leftMotors({-18, 19, -20}, pros::MotorGearset::blue);
/**
* @brief 
*Right drivetrain motorgroup, negative values indicate it is reversed
**/
pros::MotorGroup rightMotors({8, -9, 10}, pros::MotorGearset::blue);
/**
* @brief 
*Bottom intake motor that spins the flex wheels
**/
pros::Motor intake(-11, pros::MotorGearset::blue);
/**
* @brief 
*Middle part of the lift that brings blocks up to the indexer
**/
pros::Motor liftM(-1, pros::MotorGearset::blue);
/**
* @brief 
*Top indexer that can spin to either score in the long goal or middle center goal
**/
pros::Motor liftI(-12, pros::MotorGearset::blue);
/**
* @brief 
*Pneumatics for the match loader
**/
pros::adi::DigitalOut matchL1('a');
/**
* @brief 
*Pneumatics for the match loader
**/
pros::adi::DigitalOut matchL2('h');
/**
* @brief 
*Pneumatics for the side descore mech
**/
pros::adi::DigitalOut descore('b');
/**
* @brief 
*Pneumatics for the top descore mech
**/
pros::adi::DigitalOut topDescore('c');
/**
* @brief 
*Top optical sensor for detecting which color block is in our top intake
**/
pros::Optical topticalSensor(3);
/**
* @brief 
*Bottom optical sensor for detecting which color block is in our bottom intake
**/
pros::Optical bottomSensor(16);
/**
* @brief 
*1st inertial sensor for odometry
**/
pros::Imu imu(13);
/**
* @brief 
*2nd Inertial sensor for odometry
**/
pros::Imu imu2(14);
/**
* @brief 
*Averages the two inertial sensor values out
**/
pros::Imu imuAvg(17);


// tracking wheels
/**
* @brief 
*Horizontal rotational sensor for odometry
**/
pros::Rotation horizontalEnc(6);
/**
* @brief 
*Left Vertical rotational sensor for odometry
**/
pros::Rotation leftVerticalEnc(-15);
/**
* @brief 
*Right Vertical rotational sensor for odometry
**/
pros::Rotation rightVerticalEnc(5);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, -2.125);
lemlib::TrackingWheel leftVertical(&leftVerticalEnc, lemlib::Omniwheel::NEW_2,
                                   -0.75);
lemlib::TrackingWheel rightVertical(&rightVerticalEnc, lemlib::Omniwheel::NEW_2,
                                    0.75);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 12.55,
                              lemlib::Omniwheel::NEW_325, 360, 2);

// lateral motion controller
/**
* @brief 
*The PID values that control linear motion
**/
lemlib::ControllerSettings
    linearController(10, // proportional gain (kP)
                     0, // integral gain (kI)
                     3, // derivative gain (kD)
                     0, // anti windup
                     0.1, // small error range, in inches
                     100, // small error range timeout, in milliseconds
                     0, // large error range, in inches
                     0, // large error range timeout, in milliseconds
                     0 // maximum acceleration (slew)
    );
/**
* @brief 
*The PID values that control angular motion
**/
// angular motion controller
lemlib::ControllerSettings
    angularController(11, // proportional gain (kP)
                      0, // integral gain (kI)
                      94.5, // derivative gain (kD)
             0, // anti windup
              0, // small error range, in inches
       0, // small error range timeout, in milliseconds
              0, // large error range, in inches
       0, // large error range timeout, in milliseconds
                    0 // maximum acceleration (slew)
    );

// sensors for odometry
/**
* @brief 
*Defines the necessary lemlib classes using the motors and sensors defined in pros
**/
lemlib::OdomSensors sensors(&leftVertical, nullptr, &horizontal, nullptr, &imuAvg);


/**
* @brief 
*input curve for throttle input during driver control
**/
lemlib::ExpoDriveCurve
    throttleCurve(3, // joystick deadband out of 127
                  10, // minimum output where drivetrain will move out of 127
                  1.019 // expo curve gain
    );

/**
* @brief 
*input curve for steer input during driver control
**/

lemlib::ExpoDriveCurve
    steerCurve(3, // joystick deadband out of 127
               10, // minimum output where drivetrain will move out of 127
               1.019 // expo curve gain
    );
/**
* @brief 
*defines the chassis with the motors and sensors defined earlier
**/
lemlib::Chassis chassis(drivetrain, linearController, angularController,
                        sensors, &throttleCurve, &steerCurve);
/**
* @brief 
*Part of the code that runs when you first start the program.
*Used to turn on lights for sensors, calibrate chassis/sensors, ect.
**/
void initialize() {
  topticalSensor.set_led_pwm(100);
  bottomSensor.set_led_pwm(100);
  chassis.calibrate(); // calibrate sensors
  autonSelector();
  if (autonType == SKILLS && autonConfirmed) {
    // lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
  }
  if (testing) {
    autonType = BLUE_RIGHT;
    autonConfirmed = true;
  }

  // thread to for brain screen and position logging
  pros::Task screenTask([&]() {
    while (true) {
      // log position telemetry
      lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

      std::cout << '\r' << std::setw(20) << "Chassis X: " << chassis.getPose().x
                << std::setw(20) << "Chassis Y: " << chassis.getPose().y
                << std::setw(20) << "Theta: " << chassis.getPose().theta
                << std::setw(20) << "Bool: " << colorDetect
                <<std::setw(20)  << "color" << topticalSensor.get_hue()
                << " " << std::flush;
      // delay to save resources
      pros::delay(50);
    }
  });
}
/**
* @brief 
*Runs when the robot is in the disabled state, before autonomous.
*This is where we reset our IMU's
**/
void disabled() {
  imu.reset(true);
  imu2.reset(true);
  controller.clear();
}

void competition_initialize() {}
/**
* @brief 
*This function runs our autonomous code after we select it on the brain screen
**/
void autonomous() {
  
  topDescore.set_value(1);
  while (!autonConfirmed) { pros::delay(50); }
  runAuton();
}
/**
* @brief 
*Runs after autonomous is finished.
*Uses tasks to run the button controls and joystick inputs for moving around the field
**/
void opcontrol() {
   if (autonType == RED_LEFT || autonType == RED_RIGHT) {
    isRed = 1;
  } else if (autonType == BLUE_LEFT || autonType == BLUE_RIGHT) {
    isRed = 0;
  }
  drivetrain.leftMotors->set_brake_mode_all(MOTOR_BRAKE_COAST);
  drivetrain.rightMotors->set_brake_mode_all(MOTOR_BRAKE_COAST);
  pros::Task AVERAGE_IMU(imuAverage);
  pros::Task BUTTON_CONTROLS(buttonControls);
if(autonType != NONE){
  pros::Task detectTheColor(colorDetector);
  
}else {
  pros::Task detectTheColor(colorDetector2);
}
pros::Task stop(stopTheIntake);
  while (true) {
    int leftY  = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    chassis.tank(leftY, rightY);
    pros::delay(10);
  }
}