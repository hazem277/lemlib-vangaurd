#ifndef AUTON_H
#define AUTON_H

extern bool isRed;
extern bool testing;
extern bool intakeStopped;
void imuAverage();
void runAuton();
void detectColor();
void colorDetector();
void colorDetector2();
void stopTheIntake();
void detectTopColor();
enum auton_type {
    RED_LEFT,
    RED_RIGHT,
    BLUE_LEFT,
    BLUE_RIGHT,
    SKILLS,
    NONE
};

extern auton_type autonType;

extern bool autonConfirmed;

extern bool isClamped;

#endif