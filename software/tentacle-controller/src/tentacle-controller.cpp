#include "tentacle-controller.h"

#include "timer-stepper-driver.h"

// TODO: Implement motor limits based on number of tentacle segments
// TODO: Implement realtime location updates

TentacleController TentacleController::create(StepperDriverConfig driver1Config, StepperDriverConfig driver2Config) {
    // TODO: Update this to support driver type when and if we have more than one

    StepperDriver* driver1 = new TimerStepperDriver(driver1Config);
    StepperDriver* driver2 = new TimerStepperDriver(driver2Config);

    return TentacleController(driver1, driver2);
}

TentacleController::~TentacleController() {
    // delete this->location;

    delete this->motor1;
    delete this->motor2;
}

bool TentacleController::move(int16_t amplitude, int16_t rotationDegrees) {
    return this->move(amplitude, rotationDegrees, this->systemSpeed);
}

bool TentacleController::move(int16_t amplitude, int16_t rotationDegrees, uint8_t speed) {
    TentacleLocation targetLocation;

    return this->move(amplitude, rotationDegrees, speed, targetLocation);
}

bool TentacleController::move(int16_t amplitude, int16_t rotationDegrees, TentacleLocation& targetLocation) {
    return this->move(amplitude, rotationDegrees, this->systemSpeed, targetLocation);
}

bool TentacleController::move(int16_t amplitude, int16_t rotationDegrees, uint8_t speed, TentacleLocation& targetLocation) {
    // TODO: Implement

    return false;
}

bool TentacleController::moveTo(uint16_t amplitude, uint16_t rotationDegrees) {
    return this->moveTo(amplitude, rotationDegrees, this->systemSpeed);
}

bool TentacleController::moveTo(uint16_t amplitude, uint16_t rotationDegrees, uint8_t speed) {
    // TODO: implement
    return false;
}

bool TentacleController::rotate(int16_t degrees, RotationDirection direction) {
    return this->rotate(degrees, direction, this->systemSpeed);
}

bool TentacleController::rotate(int16_t degrees, RotationDirection direction, uint8_t speed) {
    TentacleLocation targetLocation;

    return this->rotate(degrees, direction, speed, targetLocation);
}

bool TentacleController::rotate(int16_t degrees, RotationDirection direction, TentacleLocation& targetLocation) {
    return this->rotate(degrees, direction, this->systemSpeed, targetLocation);
}

bool TentacleController::rotate(int16_t degrees, RotationDirection direction, uint8_t speed, TentacleLocation& targetLocation) {
    // TODO: implement
    return false;
}

bool TentacleController::rotateTo(uint16_t rotationDegrees) {
    return this->rotateTo(rotationDegrees, this->systemSpeed);
}

bool TentacleController::rotateTo(uint16_t rotationDegrees, uint8_t speed) {
    return this->rotateTo(rotationDegrees, this->getShortestDirection(rotationDegrees), speed);
}

bool TentacleController::rotateTo(uint16_t rotationDegrees, RotationDirection direction) {
    return this->rotateTo(rotationDegrees, direction, this->systemSpeed);
}

bool TentacleController::rotateTo(uint16_t rotationDegrees, RotationDirection direction, uint8_t speed) {
    // TODO: implement
    return false;
}

bool TentacleController::stop() {
    this->motor1->stop();
    this->motor2->stop();

    // TODO: figure out how the location is updated
    return true;
}

void TentacleController::resetPosition(uint16_t amplitude, uint16_t rotationDegrees) {
    this->location.amplitude = amplitude;
    this->location.rotationDegrees - rotationDegrees;
}

void TentacleController::setSpeed(uint8_t speed) {
    this->systemSpeed = speed;
}

uint8_t TentacleController::getSpeed() {
    return this->systemSpeed;
}

MotionStatus TentacleController::getStatus() {
    return MotionStatus();
}

// ---------------------------------------------------
// PRIVATE
//----------------------------------------------------

TentacleController::TentacleController(StepperDriver* stepperDriver1, StepperDriver* stepperDriver2) {
    this->motor1 = stepperDriver1;
    this->motor2 = stepperDriver2;
}

RotationDirection TentacleController::getShortestDirection(uint16_t targetDegrees) {
    uint16_t current = this->location.rotationDegrees;
    uint16_t distance = (targetDegrees > current) ? targetDegrees - current : current - targetDegrees;

    if (distance > 180) {
        return CounterClockwise;
    } else {
        return Clockwise;
    }
}