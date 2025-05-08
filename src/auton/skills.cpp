#include "main.h"

void skills() {
   chassis.setPose(0, 0, 270);
   chassis.moveToPoint(chassis.getPose().x + 5, chassis.getPose().y, 1000, {.forwards = false, .minSpeed = 30});
}