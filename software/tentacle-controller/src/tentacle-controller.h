#ifndef _TENTACLE_CONTROLLER_
#define _TENTACLE_CONTROLLER_

#include "motor-driver/stepper-driver.h"
#include "util.h"

typedef struct {
    uint16_t amplitude;
    uint16_t rotationDegrees;
} TentacleLocation;

/**
 * Class that is used to control a robotic tentacle
 */
class TentacleController {
   public:
    ~TentacleController();

    /**
     * Facotry method for creating a TentacleController instance
     */
    static TentacleController create(StepperDriverConfig driver1Config, StepperDriverConfig driver2Config);

    /**
     * Moves the given amount from the current location.
     * For rotation positive values move clockwise and negative values move counter clockwise.
     */
    bool move(int16_t amplitude, int16_t degrees);
    bool move(int16_t amplitude, int16_t degrees, uint8_t speed);
    bool move(int16_t amplitude, int16_t degrees, TentacleLocation& targetLocation);
    bool move(int16_t amplitude, int16_t degrees, uint8_t speed, TentacleLocation& targetLocation);

    /**
     * Moves to the provided location.
     */
    bool moveTo(uint16_t amplitude, uint16_t rotationDegrees);
    bool moveTo(uint16_t amplitude, uint16_t rotationDegrees, uint8_t speed);

    /**
     * Rotates the given amount from the current location.
     * Positive values move clockwise and negative values move counter clockwise.
     */
    bool rotate(int16_t degrees, RotationDirection direction);
    bool rotate(int16_t degrees, RotationDirection direction, uint8_t speed);
    bool rotate(int16_t degrees, RotationDirection direction, TentacleLocation& targetLocation);
    bool rotate(int16_t degrees, RotationDirection direction, uint8_t speed, TentacleLocation& targetLocation);

    /**
     * Rotates to the provided location.
     * If no direction is provided then it will take the shortest path
     */
    bool rotateTo(uint16_t rotationDegrees);
    bool rotateTo(uint16_t rotationDegrees, uint8_t speed);
    bool rotateTo(uint16_t rotationDegrees, RotationDirection direction);
    bool rotateTo(uint16_t rotationDegrees, RotationDirection direction, uint8_t speed);

    /**
     * Stops any moves that are in progress
     */
    bool stop();

    /**
     * Sets the internal amplitude and location values without moving the tentacle
     */
    void resetPosition(uint16_t amplitude, uint16_t rotationDegrees);

    /**
     * Readonly pointer to the thentacles current location
     */
    const TentacleLocation* currentLocation;

    /**
     * Sets the system speed.
     * This is the speed that is used when no speed is specified in a motion command.
     */
    void setSpeed(uint8_t speed);

    /**
     * Gets the system speed.
     * This is the speed that is used when no speed is specified in a motion command.
     */
    uint8_t getSpeed();

    /**
     * Gets the current motion status.
     */
    MotionStatus getStatus();

   private:
    TentacleController(StepperDriver* stepperDriver1, StepperDriver* stepperDriver2);
    RotationDirection getShortestDirection(uint16_t targetDegrees);
    TentacleLocation location;
    StepperDriver* motor1;
    StepperDriver* motor2;
    uint8_t systemSpeed = 128;
    MotionStatus status = Stopped;
};

#endif