#include "main.h"
#include "auton/auton.h"
#include "drivercontrol.h"
#include "graphics.h"             // IWYU pragma: keep
#include "lemlib-tarball/api.hpp" // IWYU pragma: keep
#include "lemlib/api.hpp"         // IWYU pragma: keep
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
pros::MotorGroup
    leftMotors({-8, -9, 10},
               pros::MotorGearset::blue); // left motor group - ports 3
                                          // (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors(
    {5, 6, -7},
    pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

pros::Motor intake(17, pros::MotorGearset::blue);
pros::Motor chain(-19, pros::MotorGearset::blue);

pros::adi::DigitalOut clamp('a');

pros::adi::DigitalOut topRing('b');

pros::adi::DigitalOut leftArm('c');
pros::adi::DigitalOut rightArm('h');

pros::Rotation wallStakeEnc(-2);

pros::Optical opticalSensor(12);

pros::Motor lift(
  11,
  pros::MotorGearset::green,
  pros::v5::MotorEncoderUnits::degrees
);
// Inertial Sensor on port 10
pros::Imu imu(3);

pros::Distance ringDistance(4);
pros::Distance distance(3);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(16);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation leftVerticalEnc(-20);
pros::Rotation rightVerticalEnc(15);
// horizontal tracking wheel. 2" diameter, 3.25" offset, back of the robot
// (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2,
                                 -4);
// vertical tracking wheel. 2" diameter, 1.75" offset, left of the robot
// (negative)
lemlib::TrackingWheel leftVertical(&leftVerticalEnc, lemlib::Omniwheel::NEW_2,
                                   -2.125);
// vertical tracking wheel. 2" diameter, 1.75" offset, right of the robot
// (positive)
lemlib::TrackingWheel rightVertical(&rightVerticalEnc, lemlib::Omniwheel::NEW_2,
                                    2.125);

// drivetrain settings
lemlib::Drivetrain drivetrain(
    &leftMotors,                // left motor group
    &rightMotors,               // right motor group
    12.55,                      // 7 inch track width
    lemlib::Omniwheel::NEW_325, // using new 4" omnis
    360,                        // drivetrain rpm is 360
    2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings
    linearController(10, // proportional gain (kP)
                     0, // integral gain (kI)
                     3, // derivative gain (kD)
            3, // anti windup
             1, // small error range, in inches
      100, // small error range timeout, in milliseconds
             3, // large error range, in inches
      500, // large error range timeout, in milliseconds
                   20 // maximum acceleration (slew)
    );

// angular motion controller
lemlib::ControllerSettings
    angularController(13.5,    // proportional gain (kP)
                      0,    // integral gain (kI)
                      89.7, // derivative gain (kD)
             0,    // anti windup
              0,  // small error range, in degrees
       100,    // small error range timeout, in milliseconds
              0,    // large error range, in degrees
       0,    // large error range timeout, in milliseconds
                    0     // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&leftVertical, // vertical tracking wheel
                            nullptr,       // vertical tracking wheel 2, set to
                                     // nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr,     // horizontal tracking wheel 2, set to
                                     // nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve
    throttleCurve(3,    // joystick deadband out of 127
                  10,   // minimum output where drivetrain will move out of 127
                  1.019 // expo curve gain
    );

// input curve for steer input during driver control
lemlib::ExpoDriveCurve
    steerCurve(3,    // joystick deadband out of 127
               10,   // minimum output where drivetrain will move out of 127
               1.019 // expo curve gain
    );

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController,
                        sensors, &throttleCurve, &steerCurve);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

//  ASSET(skills_path_txt);

void initialize() {
  // pros::lcd::initialize(); // initialize brain screen
  opticalSensor.set_led_pwm(100);
  chassis.calibrate(); // calibrate sensors
  autonSelector();
  if (autonType == SKILLS && autonConfirmed) {
    lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000,
      false);
  }

  // the default rate is 50. however, if you need to change the rate, you
  // can do the following.
  // lemlib::bufferedStdout().setRate(...);
  // If you use bluetooth or a wired connection, you will want to have a rate of
  // 10ms

  // for more information on how the formatting for the loggers
  // works, refer to the fmtlib docs

  // thread to for brain screen and position logging
  pros::Task screenTask([&]() {
    while (true) {
      // print robot location to the brain screen
      pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
      pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
      pros::lcd::print(3, "Heading: %f", imu.get_heading()); // heading
      // log position telemetry
      lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

      std::cout << '\r' << std::setw(20) << "X: " << chassis.getPose().x
                << std::setw(20) << "Y: " << chassis.getPose().y
                << std::setw(20) << "Theta: " << chassis.getPose().theta
                << std::setw(20) << "intake torque:" << chain.get_torque()
                << std::setw(20) << " "
                << std::flush;
      // delay to save resources
      pros::delay(100);
    }
  });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control              
 */
void competition_initialize() {}

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the
 * features LemLib has to offer
 */
void autonomous() {
  while (!autonConfirmed) {
    pros::delay(50);
  }
  runAuton(); 
}

/**
 * Runs in driver control
 */
void opcontrol() {
  // controller
  // loop to continuously update motors
  pros::Task EJECT_RING(eject);
  pros::Task BUTTON_CONTROLS(buttonControls);
  while (true) {
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    // move the chassis with curvature drive
    chassis.tank(leftY, rightY);
    // delay to save resources
    pros::delay(10);
  }
}