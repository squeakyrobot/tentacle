#include "timer-motor-driver.h"

bool timerCallback(repeating_timer_t *rt)
{
    TimerMotorDriver *driver = (TimerMotorDriver *)(rt->user_data);

    gpio_put(driver->config.stepPin, !gpio_get(driver->config.stepPin));

    if (driver->endTime <= time_us_32())
    {
        driver->stop();
        return false;
    }

    return true; // keep repeating
};

TimerMotorDriver::TimerMotorDriver(MotorDriverConfig config) : MotorDriver(config)
{
    gpio_init(config.stepPin);
    gpio_init(config.directionPin);
    gpio_set_dir(config.stepPin, GPIO_OUT);
    gpio_set_dir(config.directionPin, GPIO_OUT);
    gpio_put(config.directionPin, CW);
};

TimerMotorDriver::~TimerMotorDriver()
{
    cancel_repeating_timer(&this->timer);
};

bool TimerMotorDriver::rotate(uint8_t speed, uint32_t degrees)
{
    return this->rotate(speed, degrees, this->direction);
};

bool TimerMotorDriver::rotate(uint8_t speed, uint32_t degrees, MotorDirection direction)
{
    if (this->direction != direction)
    {
        this->direction = direction;
        gpio_put(this->config.directionPin, direction);
    }

    int pulse = this->calculatePulseWidth(speed);

    if (this->timer.alarm_id > 0)
    {
        cancel_repeating_timer(&this->timer);
    }

    uint32_t steps = degrees * this->stepsPerDegree;
    double delay = 1000000 / pulse;

    this->status = Running;
    this->endTime = (steps * (delay * 2)) + time_us_32();

    return add_repeating_timer_us(-(delay), timerCallback, this, &timer);
};

bool TimerMotorDriver::stop()
{
    this->status = Stopped;
    return cancel_repeating_timer(&this->timer);
};
