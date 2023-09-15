#include <stdio.h>

#ifndef _UTIL_
#define _UTIL_

enum MotionStatus {
    Stopped,
    Moving,
};

enum RotationDirection {
    Clockwise = 0,
    CounterClockwise = 1,
};

uint32_t normalizeRange(uint32_t value, uint32_t min, uint32_t max, uint32_t inMin = 0, uint32_t inMax = 255);

#endif
