#ifndef _TENTACLE_CONTROLLER_
#define _TENTACLE_CONTROLLER_

#include "motor-driver/stepper-driver.h"
#include "util.h"

#define MAX_AMPLITUDE 100

typedef struct {
    // amplitude will be clamped between 0-100 (MAX_AMPLITUDE)
    uint8_t amplitude;

    // Degrees will be clamped between 0-360
    uint16_t angle;
} TentacleLocation;

typedef struct {
    int32_t motor1Steps;
    int32_t motor2Steps;
} TentacleLocationSteps;

typedef struct {
    RotationDirection direction;
    uint16_t degrees;
} RotationPath;

typedef struct {
    StepperDriverConfig driver1Config;
    StepperDriverConfig driver2Config;
    uint8_t segments = 20;
    uint16_t travelPerSegment_um = 4000;      // 4mm     // 4.4mm
    uint16_t pulleyCircumference_um = 56549;  // 18mm Diameter (56.549mm CIR)
} TentacleConfig;

/**
 * Class that is used to control a robotic tentacle
 */
class TentacleController {
   public:
    ~TentacleController();

    /**
     * Facotry method for creating a TentacleController instance
     */
    static TentacleController* create(TentacleConfig config);

    /**
     * Moves the given amount from the current location.
     * TODO: explain that this is a direct move th the final calculated location
     * For rotation positive values move clockwise and negative values move counter clockwise.
     */
    bool move(int16_t amplitude, int16_t degrees);
    bool move(int16_t amplitude, int16_t degrees, uint8_t speed);
    bool move(int16_t amplitude, int16_t degrees, TentacleLocation& targetLocation);
    bool move(int16_t amplitude, int16_t degrees, uint8_t speed, TentacleLocation& targetLocation);

    /**
     * Moves to the provided location.
     */
    bool moveTo(uint8_t amplitude, uint16_t angle);
    bool moveTo(uint8_t amplitude, uint16_t angle, uint8_t speed);

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
    bool rotateTo(uint16_t angle);
    bool rotateTo(uint16_t angle, uint8_t speed);
    bool rotateTo(uint16_t angle, RotationDirection direction);
    bool rotateTo(uint16_t angle, RotationDirection direction, uint8_t speed);

    /**
     * Stops any moves that are in progress
     */
    bool stop();

    /**
     * Sets the internal amplitude and location values without moving the tentacle
     */
    void resetPosition(uint8_t amplitude, uint16_t angle);

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
    TentacleController(TentacleConfig config, StepperDriver* stepperDriver1, StepperDriver* stepperDriver2);
    TentacleLocationSteps calculateMotorLocation(uint8_t amplitude, uint16_t angle);
    RotationPath calculateRotationPath(uint16_t targetDegrees);
    TentacleLocation location;
    StepperDriver* motor1;
    StepperDriver* motor2;
    uint16_t m1StepsPerAmpUnit;
    uint16_t m2StepsPerAmpUnit;
    uint8_t systemSpeed = 128;
    MotionStatus status = Stopped;
};

#endif