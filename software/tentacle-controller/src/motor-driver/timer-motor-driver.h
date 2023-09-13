#include "motor-driver.h"
#include "pico/stdlib.h"

class TimerMotorDriver : public MotorDriver
{
private:
  repeating_timer_t timer;

public:
  uint32_t endTime;
  TimerMotorDriver(MotorDriverConfig config);
  ~TimerMotorDriver();
  bool rotate(uint8_t speed, uint32_t degrees);
  bool rotate(uint8_t speed, uint32_t degrees, MotorDirection direction);
  bool stop();
};
