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
#include "pros/motor_group.hpp"
#include "pros/motors.h" // IWYU pragma: keep
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

// motor groups
pros::MotorGroup leftMotors({-8, -9, 10}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({5, 6, -7}, pros::MotorGearset::blue);

pros::Motor intake(17, pros::MotorGearset::blue);
pros::Motor chain(-19, pros::MotorGearset::blue);
pros::adi::DigitalOut clamp('a');
pros::adi::DigitalOut topRing('b');
pros::adi::DigitalOut leftArm('c');
pros::adi::DigitalOut rightArm('h');
pros::Rotation wallStakeEnc(-2);
pros::Optical opticalSensor(12);
pros::Motor lift(11, pros::MotorGearset::green,
                 pros::v5::MotorEncoderUnits::degrees);
pros::Imu imu(4);
pros::Distance distance(3);

// tracking wheels
pros::Rotation horizontalEnc(16);
pros::Rotation leftVerticalEnc(-20);
pros::Rotation rightVerticalEnc(15);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, -4);
lemlib::TrackingWheel leftVertical(&leftVerticalEnc, lemlib::Omniwheel::NEW_2,
                                   -2.125);
lemlib::TrackingWheel rightVertical(&rightVerticalEnc, lemlib::Omniwheel::NEW_2,
                                    2.125);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 12.55,
                              lemlib::Omniwheel::NEW_325, 360, 2);

// lateral motion controller
lemlib::ControllerSettings
    linearController(10, // proportional gain (kP)
                     0, // integral gain (kI)
                     60, // derivative gain (kD)
                     0, // anti windup
                     0.1, // small error range, in inches
                     100, // small error range timeout, in milliseconds
                     0, // large error range, in inches
                     0, // large error range timeout, in milliseconds
                     0 // maximum acceleration (slew)
    );

// angular motion controller
lemlib::ControllerSettings
    angularController(10, // proportional gain (kP)
                      0, // integral gain (kI)
                      75, // derivative gain (kD)
                      0, // anti windup
                      0.1, // small error range, in degrees
                      100, // small error range timeout, in milliseconds
                      0, // large error range, in degrees
                      0, // large error range timeout, in milliseconds
                      0 // maximum acceleration (slew)
    );

// sensors for odometry
lemlib::OdomSensors sensors(&leftVertical, nullptr, &horizontal, nullptr, &imu);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve
    throttleCurve(3, // joystick deadband out of 127
                  10, // minimum output where drivetrain will move out of 127
                  1.019 // expo curve gain
    );

// input curve for steer input during driver control
lemlib::ExpoDriveCurve
    steerCurve(3, // joystick deadband out of 127
               10, // minimum output where drivetrain will move out of 127
               1.019 // expo curve gain
    );

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController,
                        sensors, &throttleCurve, &steerCurve);

void initialize() {
  opticalSensor.set_led_pwm(100);
  chassis.calibrate(); // calibrate sensors
  autonSelector();
  if (autonType == SKILLS && autonConfirmed) {
    lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
  }
  if (testing) {
    autonType = BLUE_NEGATIVE;
    scoreAllianceStake = false;
    autonConfirmed = true;
  }

  // thread to for brain screen and position logging
  pros::Task screenTask([&]() {
    while (true) {
      // log position telemetry
      lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

      std::cout << '\r' << std::setw(20) << "X: " << chassis.getPose().x
                << std::setw(20) << "Y: " << chassis.getPose().y
                << std::setw(20) << "Theta: " << chassis.getPose().theta
                << std::setw(20) << "autonConfirmation" << autonConfirmed << std::setw(20)
                << " " << std::flush;
      // delay to save resources
      pros::delay(50);
    }
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  while (!autonConfirmed) { pros::delay(50); }
  runAuton();
}

void opcontrol() {
  drivetrain.leftMotors->set_brake_mode_all(MOTOR_BRAKE_COAST);
  drivetrain.rightMotors->set_brake_mode_all(MOTOR_BRAKE_COAST);
  
  pros::Task EJECT_RING(eject);
  pros::Task BUTTON_CONTROLS(buttonControls);
  while (true) {
    int leftY  = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    chassis.tank(leftY, rightY);
    pros::delay(10);
  }
}