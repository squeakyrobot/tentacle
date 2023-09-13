#include "motor-driver.h"
#include "pico/stdlib.h"

class TimerMotorDriver : public MotorDriver {
   public:
    TimerMotorDriver(MotorDriverConfig config);
    ~TimerMotorDriver();
    bool rotate(uint8_t speed, uint32_t degrees);
    bool rotate(uint8_t speed, uint32_t degrees, MotorDirection direction);
    bool stop();
    uint32_t getRotationEndTime();

   protected:
    static bool timerCallback(repeating_timer_t *repeatingTimer);

   private:
    repeating_timer_t timer;
    uint32_t endTime;
};
