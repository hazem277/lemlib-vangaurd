#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "liblvgl/core/lv_obj.h"

extern void lv_example_chart_5(void);

extern void recordPID();

extern void stopRecordingPID();

extern void autonSelector(void);

extern void debugTabs(void);

extern lv_obj_t *screenLogo;

extern lv_obj_t *screenDebug;

#endif