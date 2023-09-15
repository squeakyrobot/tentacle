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

inline uint32_t normalizeRange(uint32_t value, uint32_t min, uint32_t max, uint32_t inMin, uint32_t inMax) {
    return (value - inMin) * (max - min) / (inMax - inMin) + min;
}

inline uint16_t clamp(uint16_t value, uint16_t min, uint16_t max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

inline uint16_t clampDegrees(uint16_t degrees) {
    return clamp(degrees, 0, 360);
}

#endif
