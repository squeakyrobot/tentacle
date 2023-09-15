#include "tentacle-controller.h"

#include "timer-stepper-driver.h"

// TODO: Implement motor limits based on number of tentacle segments
//          - 4.4mm travel per segment
//          - Test tentacle: 18 segments - 79.2mm of travel
//              - Pulley: 18mm ID - 4.4 wraps total, 2.2 neutral position (4.5 is about max without pulley modification)
//              - TODO: Expand pulley diameter, or make the inside diameter smaller
// TODO: Implement realtime location updates

TentacleController* TentacleController::create(TentacleConfig config) {
    // TODO: Update this to support driver type when and if we have more than one

    StepperDriver* driver1 = new TimerStepperDriver(config.driver1Config);
    StepperDriver* driver2 = new TimerStepperDriver(config.driver2Config);

    return new TentacleController(config, driver1, driver2);
}

TentacleController::~TentacleController() {
    // delete this->location;

    delete this->motor1;
    delete this->motor2;
}

bool TentacleController::move(uint8_t amplitude, int16_t rotationDegrees) {
    return this->move(amplitude, rotationDegrees, this->systemSpeed);
}

bool TentacleController::move(uint8_t amplitude, int16_t rotationDegrees, uint8_t speed) {
    TentacleLocation targetLocation;

    return this->move(amplitude, rotationDegrees, speed, targetLocation);
}

bool TentacleController::move(uint8_t amplitude, int16_t rotationDegrees, TentacleLocation& targetLocation) {
    return this->move(amplitude, rotationDegrees, this->systemSpeed, targetLocation);
}

bool TentacleController::move(uint8_t amplitude, int16_t rotationDegrees, uint8_t speed, TentacleLocation& targetLocation) {
    // TODO: Implement

    return false;
}

bool TentacleController::moveTo(uint8_t amplitude, uint16_t rotationDegrees) {
    return this->moveTo(amplitude, rotationDegrees, this->systemSpeed);
}

bool TentacleController::moveTo(uint8_t amplitude, uint16_t rotationDegrees, uint8_t speed) {
    // clamp the values
    rotationDegrees = clampDegrees(rotationDegrees);
    amplitude = clamp(amplitude, 0, MAX_AMPLITUDE);

    // find the difference from current location
    int16_t travelAmplitude = amplitude - this->location.amplitude;
    RotationPath rotationPath = this->calculateRotationPath(rotationDegrees);

    return this->move(travelAmplitude, rotationPath.degrees, rotationPath.direction);
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
    // return this->rotateTo(rotationDegrees, this->calculateRotationPath(rotationDegrees), speed);

    return false;
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

void TentacleController::resetPosition(uint8_t amplitude, uint16_t rotationDegrees) {
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

TentacleController::TentacleController(TentacleConfig config, StepperDriver* stepperDriver1, StepperDriver* stepperDriver2) {
    // Motor 1 moves the tentacle on the y axis, from 0-180 degrees
    this->motor1 = stepperDriver1;

    // Motor 2 moves the tentacle on the x axis from 90-270 degrees
    this->motor2 = stepperDriver2;

    this->location = {
        amplitude : 0,
        rotationDegrees : 0,
    };

    // Hopefully this can be replaced with homing
    double maxTravel = config.segments * config.travelPerSegment_um;
    double maxRotations = maxTravel / config.pulleyDiameter_um;
    // double maxDegrees = maxRotations * 360;

    uint32_t m1MaxSteps = maxRotations * this->motor1->getStepsPerRevolution();
    uint32_t m2MaxSteps = maxRotations * this->motor2->getStepsPerRevolution();

    printf(": %d\n", this->motor2->getStepsPerRevolution());
    printf("Max Rotations: %f\n", maxRotations);
    // printf("Max Degrees: %f\n", maxDegrees);
    printf("Max Steps M1: %d\n", m1MaxSteps);
    printf("Max Steps M2: %d\n", m2MaxSteps);

    // Calculate the steps per each unit of amplitude.
    // We lose some steps with the integer division, but I think thats ok as it
    // gives us a natural buffer to not run against the edge
    //  28BYJ-48 1/16 Example: 181.63 becomes 181 giving us an upper end of 18100
    //  instead of the actual 18163, losing 63 steps in this example.
    //  That is a loss of range of ~0.9%
    this->m1StepsPerAmpUnit = m1MaxSteps / MAX_AMPLITUDE;
    this->m2StepsPerAmpUnit = m2MaxSteps / MAX_AMPLITUDE;

    printf("Max Steps per Unit M1: %d\n", m1StepsPerAmpUnit);
    printf("Max Steps per Unit M2: %d\n", m2StepsPerAmpUnit);
}

RotationPath TentacleController::calculateRotationPath(uint16_t targetDegrees) {
    uint16_t current = this->location.rotationDegrees;
    uint16_t distance = (targetDegrees > current) ? targetDegrees - current : current - targetDegrees;

    if (distance > 180) {
        return {
            direction : CounterClockwise,
            degrees : (uint16_t)(360 - distance),
        };
    } else {
        return {
            direction : Clockwise,
            degrees : distance,
        };
    }
}