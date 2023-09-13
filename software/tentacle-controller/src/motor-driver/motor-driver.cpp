#include "motor-driver.h"

#include "util.h"

MotorDriver::MotorDriver(MotorDriverConfig config) {
    this->config = config;
    this->stepsPerRev = config.stepsPerRevolution * config.microStepMultiplier;
    this->stepsPerDegree = this->stepsPerRev / 360;
};

uint32_t MotorDriver::calculateRotateTime_ms(uint8_t speed, uint32_t rotationDegrees) {
    return this->calculateRotateTime_us(speed, rotationDegrees) / 1000000;
};

uint32_t MotorDriver::calculateRotateTime_us(uint8_t speed, uint32_t rotationDegrees) {
    int steps = rotationDegrees * this->stepsPerDegree;
    float stepTime = (1000000 / this->calculatePulseWidth(speed)) * 2;

    return stepTime * steps;
};

bool MotorDriver::rotate(uint8_t speed, uint32_t degrees) {
    return this->rotate(speed, degrees, this->direction);
}
MotorStatus MotorDriver::getStatus() {
    return this->status;
};

MotorDirection MotorDriver::getDirection() {
    return this->direction;
};

uint8_t MotorDriver::getStepPin() {
    return this->config.stepPin;
};

uint8_t MotorDriver::getDirectionPin() {
    return this->config.directionPin;
};

uint32_t MotorDriver::calculatePulseWidth(uint8_t speed) {
    return normalizeRange(speed, this->config.minPulsesPerSecond, this->config.maxPulsesPerSecond, 0, 255);
};
