#ifndef _TIMER_STEPPER_DRIVER_
#define _TIMER_STEPPER_DRIVER_

#include "pico/stdlib.h"
#include "stepper-driver.h"

class TimerStepperDriver : public StepperDriver {
   public:
    TimerStepperDriver(StepperDriverConfig config);
    ~TimerStepperDriver();
    bool rotateSteps(uint8_t speed, uint32_t steps, RotationDirection direction);
    bool stop();
    uint32_t remainingSteps;

   protected:
    static bool timerCallback(repeating_timer_t* repeatingTimer);

   private:
    repeating_timer_t timer{};
};

#endif
