#include <stdio.h>

#ifndef _STEPPER_DRIVER_
#define _STEPPER_DRIVER_

struct StepperDriverConfig {
    uint8_t directionPin;
    uint8_t stepPin;
    uint16_t stepsPerRevolution;
    uint16_t microStepMultiplier = 0;
    float maxRPM;
};

enum MotorStatus {
    MotorStopped,
    MotorRunning,
};

enum MotorDirection {
    MotorDirCCW = 0,
    MotorDirCW = 1,
};

class StepperDriver {
   public:
    StepperDriver(StepperDriverConfig config);
    virtual ~StepperDriver(){};
    uint32_t calculateRotateTime_ms(uint8_t speed, uint32_t rotationDegrees);
    uint32_t calculateRotateTime_us(uint8_t speed, uint32_t rotationDegrees);
    bool rotateDegrees(uint8_t speed, uint32_t degrees);
    bool rotateDegrees(uint8_t speed, uint32_t degrees, MotorDirection direction);
    bool rotateSteps(uint8_t speed, uint32_t steps);
    virtual bool rotateSteps(uint8_t speed, uint32_t steps, MotorDirection direction) = 0;
    virtual bool stop() = 0;

    MotorStatus getStatus();
    MotorDirection getDirection();
    uint8_t getStepPin();
    uint8_t getDirectionPin();

   protected:
    uint32_t calculateStepsPerSecond(uint8_t speed);
    StepperDriverConfig config;
    uint32_t stepsPerRev;
    double stepsPerDegree;
    float maxStepsPerSecond;
    MotorStatus status = MotorStopped;
    MotorDirection direction = MotorDirCW;
};

#endif
