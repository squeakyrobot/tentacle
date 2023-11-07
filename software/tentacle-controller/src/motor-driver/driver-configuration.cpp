#include "driver-configuration.h"

StepperDriverConfig createMotorConfig(
    StepperDriverConfig config,
    uint8_t stepPin,
    uint8_t directionPin,
    uint8_t sleepPin) {
        StepperDriverConfig newConfig = config;
    newConfig.stepPin = stepPin;
    newConfig.directionPin = directionPin;
    newConfig.sleepPin = sleepPin;

    return newConfig;
}