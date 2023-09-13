#include <stdio.h>

struct MotorDriverConfig
{
  uint8_t directionPin;
  uint8_t stepPin;
  uint16_t stepsPerRevolution;
  uint16_t microStepMultiplier = 0;
  uint16_t maxPulsesPerSecond;
  uint16_t minPulsesPerSecond;
};

enum MotorStatus
{
  Stopped,
  Running,
};

enum MotorDirection
{
  CW = 0,
  CCW = 1
};

class MotorDriver
{
protected:
  uint32_t stepsPerRev;
  uint16_t stepsPerDegree;
  MotorStatus status = Stopped;
  MotorDirection direction = CW;
  uint32_t calculatePulseWidth(uint8_t speed);

public:
  MotorDriver(MotorDriverConfig config);
  virtual ~MotorDriver(){};
  uint32_t calculateRotateTime_ms(uint8_t speed, uint32_t rotationDegrees);
  uint32_t calculateRotateTime_us(uint8_t speed, uint32_t rotationDegrees);
  MotorDriverConfig config;

  virtual bool rotate(uint8_t speed, uint32_t degrees);
  virtual bool rotate(uint8_t speed, uint32_t degrees, MotorDirection direction) = 0;
  virtual bool stop() = 0;
  MotorStatus getStatus();
  MotorDirection getDirection();
};
