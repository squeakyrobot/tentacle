#ifndef _DRIVER_CONFIG_
#define _DRIVER_CONFIG_

#include "stepper-driver.h"

/**
 * 28BYJ-48 (1/64 gear ratio) with a TMC2209 configured for 8 micro steps
 * TESTED:
 *  * 5v Motor: 15 RPM @ 5v, 27 RPM @ 12v (gets hot)
 *  * 12v Motor: 16 RPM @ 12v
 */
const StepperDriverConfig TMC2209_28BYJ48_64 = {
    directionPin : 0,
    stepPin : 0,
    sleepPin : 0,
    stepsPerRevolution : 2052,  // 2038???
    microStepMultiplier : 8,
    invertDirection : true,
    maxRPM : 20
};

/**
 * 28BYJ-48 (1/16 gear ratio) with a TMC2209 configured for 8 micro steps
 * TESTED: 70 RPM @ 12v
 */
const StepperDriverConfig TMC2209_28BYJ48_16 = {
    directionPin : 0,
    stepPin : 0,
    sleepPin : 0,
    stepsPerRevolution : 516,
    microStepMultiplier : 8,
    invertDirection : true,
    maxRPM : 70
};

/**
 * 28BYJ-48 (1/64 gear ratio) with a DRV8825 configured for no microsteps
 */
const StepperDriverConfig DRV8825_28BYJ48_64 = {
    directionPin : 0,
    stepPin : 0,
    sleepPin : 0,
    stepsPerRevolution : 2052,  // 2052,  // 2038???
    microStepMultiplier : 1,
    invertDirection : false,
    maxRPM : 25
};

const StepperDriverConfig DRV8825_28BYJ48_16 = {
    directionPin : 0,
    stepPin : 0,
    sleepPin : 0,
    stepsPerRevolution : 516,
    microStepMultiplier : 1,
    invertDirection : false,
    maxRPM : 25
};

const StepperDriverConfig DRV8825_NEMA11 = {
    directionPin : 0,
    stepPin : 0,
    sleepPin : 0,
    stepsPerRevolution : 200,
    microStepMultiplier : 2,
    invertDirection : false,
    maxRPM : 60
};

/**
 * NEMA-8, 1.8° per step with a TMC2209 configured for 8 micro steps
 */
const StepperDriverConfig TMC2209_NEMA8 = {
    directionPin : 0,
    stepPin : 0,
    sleepPin : 0,
    stepsPerRevolution : 200,
    microStepMultiplier : 8,
    invertDirection : true,
    maxRPM : 150
};

// TODO: add type
StepperDriverConfig createMotorConfig(StepperDriverConfig config, uint8_t stepPin, uint8_t directionPin, uint8_t sleepPin);

#endif
