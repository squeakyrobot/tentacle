#ifndef _DRIVER_CONFIG_
#define _DRIVER_CONFIG_

#include "stepper-driver.h"

/**
 * 28BYJ-48 (1/64 gear ratio) with a TMC2209 configured for 8 micro steps
 * TESTED: 15 RPM @ 5v, 27 RPM @ 12v
 */
const StepperDriverConfig TMC2209_28BYJ48_64 = {
    directionPin : 0,
    stepPin : 0,
    stepsPerRevolution : 2052,
    microStepMultiplier : 8,
    invertDirection : true,
    maxRPM : 25
};

/**
 * 28BYJ-48 (1/64 gear ratio) with a DRV8825 configured for no microsteps
 */
const StepperDriverConfig DRV8825_28BYJ48_64 = {
    directionPin : 0,
    stepPin : 0,
    stepsPerRevolution : 2052,
    microStepMultiplier : 1,
    invertDirection : false,
    maxRPM : 25
};

/**
 * NEMA-8, 1.8° per step with a TMC2209 configured for 8 micro steps
 */
const StepperDriverConfig TMC2209_NEMA8 = {
    directionPin : 0,
    stepPin : 0,
    stepsPerRevolution : 200,
    microStepMultiplier : 8,
    invertDirection : true,
    maxRPM : 150
};

StepperDriverConfig createMotorConfig(StepperDriverConfig config, uint8_t stepPin, uint8_t directionPin);

#endif
