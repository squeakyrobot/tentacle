#include "driver-configuration.h"

StepperDriverConfig createMotorConfig(StepperDriverConfig config, uint8_t stepPin, uint8_t directionPin) {
    StepperDriverConfig newConfig = config;
    newConfig.stepPin = stepPin;
    newConfig.directionPin = directionPin;

    return newConfig;
}