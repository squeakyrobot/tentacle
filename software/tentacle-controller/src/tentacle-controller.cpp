#include "tentacle-controller.h"

#include <cmath>

#include "timer-stepper-driver.h"

// TODO: Implement motor limits based on number of tentacle segments
//          - 4.4mm travel per segment
//          - Test tentacle: 18 segments - 79.2mm of travel - each direction
//              - Pulley: 18mm Diameter - 1.4 wraps per direction, 2.8 Total
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

bool TentacleController::move(int16_t amplitude, int16_t degrees) {
    return this->move(amplitude, degrees, this->systemSpeed);
}

bool TentacleController::move(int16_t amplitude, int16_t degrees, uint8_t speed) {
    TentacleLocation targetLocation;

    return this->move(amplitude, degrees, speed, targetLocation);
}

bool TentacleController::move(int16_t amplitude, int16_t degrees, TentacleLocation& targetLocation) {
    return this->move(amplitude, degrees, this->systemSpeed, targetLocation);
}

bool TentacleController::move(int16_t amplitude, int16_t degrees, uint8_t speed, TentacleLocation& targetLocation) {
    // Find the final target location after the move
    uint16_t angle = (degrees + 360) % 360;

    targetLocation.angle = (targetLocation.angle + angle) % 360;
    targetLocation.amplitude = clamp(targetLocation.amplitude + amplitude, 0, MAX_AMPLITUDE);

    // Find the target locatioin in motor steps
    TentacleLocationSteps locationSteps = this->calculateMotorLocation(targetLocation.amplitude, targetLocation.angle);

    // Find the difference from the current location
    this->motor1->stop();
    this->motor2->stop();
    uint32_t m1Travel = this->motor1->getStepLocation() - locationSteps.motor1Steps;
    uint32_t m2Travel = this->motor2->getStepLocation() - locationSteps.motor2Steps;

    this->motor1->rotateSteps(speed, m1Travel);
    this->motor2->rotateSteps(speed, m2Travel);

    // TODO: Figure out how to update status & location and get a callback when the move is complete

    return true;
}

bool TentacleController::moveTo(uint8_t amplitude, uint16_t angle) {
    return this->moveTo(amplitude, angle, this->systemSpeed);
}

bool TentacleController::moveTo(uint8_t amplitude, uint16_t angle, uint8_t speed) {
    angle = clampDegrees(angle);
    amplitude = clamp(amplitude, 0, MAX_AMPLITUDE);

    // Find the target locatioin in motor steps
    TentacleLocationSteps locationSteps = this->calculateMotorLocation(amplitude, angle);

    printf("M1 Target Steps: %d\n", locationSteps.motor1Steps);
    printf("\tLocation: %d\n", this->motor1->getStepLocation());

    // Find the difference from the current location
    this->motor1->stop();
    this->motor2->stop();
    uint32_t m1Travel = locationSteps.motor1Steps - this->motor1->getStepLocation();
    uint32_t m2Travel = locationSteps.motor2Steps - this->motor2->getStepLocation();

    printf("M1 Location: %d\n", this->motor1->getStepLocation());
    printf("M1 Travel Steps: %d\n", m1Travel);

    this->motor1->rotateSteps(speed, m1Travel);
    this->motor2->rotateSteps(speed, m2Travel);

    return true;
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

bool TentacleController::rotateTo(uint16_t angle) {
    return this->rotateTo(angle, this->systemSpeed);
}

bool TentacleController::rotateTo(uint16_t angle, uint8_t speed) {
    // return this->rotateTo(angle, this->calculateRotationPath(angle), speed);

    return false;
}

bool TentacleController::rotateTo(uint16_t angle, RotationDirection direction) {
    return this->rotateTo(angle, direction, this->systemSpeed);
}

bool TentacleController::rotateTo(uint16_t angle, RotationDirection direction, uint8_t speed) {
    // TODO: implement
    return false;
}

bool TentacleController::stop() {
    this->motor1->stop();
    this->motor2->stop();

    // TODO: figure out how the location is updated
    return true;
}

void TentacleController::resetPosition(uint8_t amplitude, uint16_t angle) {
    this->location.amplitude = amplitude;
    this->location.angle - angle;
}

void TentacleController::setSpeed(uint8_t speed) {
    this->systemSpeed = speed;
}

uint8_t TentacleController::getSpeed() {
    return this->systemSpeed;
}

MotionStatus TentacleController::getStatus() {
    return (this->motor1->getStatus() == Moving || this->motor2->getStatus() == Moving) ? Moving : Stopped;
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
        angle : 0,
    };

    // Hopefully this can be replaced with homing
    double maxTravel = (config.segments * config.travelPerSegment_um) * 2;
    double maxRotations = maxTravel / config.pulleyCircumference_um;
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
    uint16_t current = this->location.angle;
    uint16_t distance = abs(targetDegrees - current);

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

TentacleLocationSteps TentacleController::calculateMotorLocation(uint8_t amplitude, uint16_t angle) {
    uint8_t quadrant = (angle / 90) % 4 + 1;

    // Q1, 0-89: Motor1+, motor2+
    // Q2, 90-179: Motor1-, motor2+
    // Q3, 180-269: Motor1-, motor2-
    // Q4, 270-359: Motor1+, motor2-

    float mul = (float)(angle % 90) / 90;
    uint8_t m1Amp, m2Amp;
    TentacleLocationSteps location;

    if (quadrant == 1) {
        m1Amp = round(amplitude * (float)(1 - mul));
        m2Amp = amplitude - m1Amp;

        location.motor1Steps = m1Amp * this->m1StepsPerAmpUnit;
        location.motor2Steps = m2Amp * this->m2StepsPerAmpUnit;
    } else if (quadrant == 2) {
        m1Amp = round(amplitude * mul);
        m2Amp = amplitude - m1Amp;

        location.motor1Steps = -(m1Amp * this->m1StepsPerAmpUnit);
        location.motor2Steps = m2Amp * this->m2StepsPerAmpUnit;

    } else if (quadrant == 3) {
        m1Amp = round(amplitude * (float)(1 - mul));
        m2Amp = amplitude - m1Amp;

        location.motor1Steps = -(m1Amp * this->m1StepsPerAmpUnit);
        location.motor2Steps = -(m2Amp * this->m2StepsPerAmpUnit);

    } else if (quadrant == 4) {
        m1Amp = round(amplitude * mul);
        m2Amp = amplitude - m1Amp;

        location.motor1Steps = m1Amp * this->m1StepsPerAmpUnit;
        location.motor2Steps = -(m2Amp * this->m2StepsPerAmpUnit);
    }

    return location;
}
