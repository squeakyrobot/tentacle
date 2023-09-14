#include "stepper-driver.h"

#include "util.h"

StepperDriver::StepperDriver(StepperDriverConfig config) {
    this->config = config;
    this->stepsPerRev = config.stepsPerRevolution * config.microStepMultiplier;
    this->stepsPerDegree = this->stepsPerRev / (float)360;

    float rps = this->config.maxRPM / 60;
    this->maxStepsPerSecond = this->stepsPerRev * rps;
};

uint32_t StepperDriver::calculateRotateTime_ms(uint8_t speed, uint32_t rotationDegrees) {
    return 0.001 * this->calculateRotateTime_us(speed, rotationDegrees);
};

uint32_t StepperDriver::calculateRotateTime_us(uint8_t speed, uint32_t rotationDegrees) {
    if (speed < 1) {
        return 0;
    }

    uint32_t steps = rotationDegrees * this->stepsPerDegree;
    uint32_t spns = 1000000 / this->calculateStepsPerSecond(speed);

    return steps * spns;
};

bool StepperDriver::rotateDegrees(uint8_t speed, uint32_t degrees) {
    return this->rotateDegrees(speed, degrees, this->direction);
}

bool StepperDriver::rotateDegrees(uint8_t speed, uint32_t degrees, MotorDirection direction) {
    return this->rotateSteps(speed, degrees * this->stepsPerDegree, direction);
};

bool StepperDriver::rotateSteps(uint8_t speed, uint32_t steps) {
    return this->rotateSteps(speed, steps, this->direction);
}

MotorStatus StepperDriver::getStatus() {
    return this->status;
};

MotorDirection StepperDriver::getDirection() {
    return this->direction;
};

uint8_t StepperDriver::getStepPin() {
    return this->config.stepPin;
};

uint8_t StepperDriver::getDirectionPin() {
    return this->config.directionPin;
};

uint32_t StepperDriver::calculateStepsPerSecond(uint8_t speed) {
    return normalizeRange(speed, 0, this->maxStepsPerSecond, 0, 255);
};
