#include <stdio.h>

#ifndef _STEPPER_DRIVER_
#define _STEPPER_DRIVER_

#include "util.h"

enum StepperDriverType {
    TimerDriver = 1,
};

typedef struct {
    uint8_t directionPin;
    uint8_t stepPin;
    uint16_t stepsPerRevolution;
    uint16_t microStepMultiplier = 1;
    bool invertDirection = false;
    float maxRPM;
    StepperDriverType driverType = TimerDriver;
} StepperDriverConfig;

// TODO: add `bool homingSupported` and `home`
class StepperDriver {
   public:
    StepperDriver(StepperDriverConfig config);
    virtual ~StepperDriver(){};
    uint32_t calculateRotateTime_ms(uint8_t speed, uint32_t rotationDegrees);
    uint32_t calculateRotateTime_us(uint8_t speed, uint32_t rotationDegrees);
    bool rotateDegrees(uint8_t speed, uint32_t degrees);
    bool rotateDegrees(uint8_t speed, uint32_t degrees, RotationDirection direction);
    bool rotateSteps(uint8_t speed, int32_t steps);
    virtual bool rotateSteps(uint8_t speed, uint32_t steps, RotationDirection direction) = 0;
    virtual bool stop() = 0;

    MotionStatus getStatus();
    RotationDirection getDirection();
    uint8_t getStepPin();
    uint8_t getDirectionPin();
    uint32_t getStepsPerRevolution();
    int32_t getStepLocation();
    void getStepLocation(int64_t steps);

   protected:
    uint32_t calculateStepsPerSecond(uint8_t speed);
    StepperDriverConfig config;
    uint32_t stepsPerRev;
    double stepsPerDegree;
    float maxStepsPerSecond;
    MotionStatus status = Stopped;
    RotationDirection direction = Clockwise;
    int32_t stepsFromHome;
};

#endif
