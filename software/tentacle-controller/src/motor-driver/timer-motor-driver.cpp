#include "timer-motor-driver.h"

TimerMotorDriver::TimerMotorDriver(MotorDriverConfig config) : MotorDriver(config) {
    gpio_init(config.stepPin);
    gpio_init(config.directionPin);
    gpio_set_dir(config.stepPin, GPIO_OUT);
    gpio_set_dir(config.directionPin, GPIO_OUT);
    gpio_put(config.directionPin, MotorDirCW);
};

TimerMotorDriver::~TimerMotorDriver() {
    cancel_repeating_timer(&this->timer);
};

bool TimerMotorDriver::rotate(uint8_t speed, uint32_t degrees) {
    return this->rotate(speed, degrees, this->direction);
};

bool TimerMotorDriver::rotate(uint8_t speed, uint32_t degrees, MotorDirection direction) {
    if (this->direction != direction) {
        this->direction = direction;
        gpio_put(this->config.directionPin, direction);
    }

    int pulse = this->calculatePulseWidth(speed);

    if (this->timer.alarm_id > 0) {
        cancel_repeating_timer(&this->timer);
    }

    uint32_t steps = degrees * this->stepsPerDegree;
    double delay = 1000000 / pulse;

    this->status = MotorRunning;
    this->endTime = (steps * (delay * 2)) + time_us_32();

    return add_repeating_timer_us(-(delay), TimerMotorDriver::timerCallback, this, &timer);
};

bool TimerMotorDriver::stop() {
    this->status = MotorStopped;
    return cancel_repeating_timer(&this->timer);
};

uint32_t TimerMotorDriver::getRotationEndTime() {
    return this->endTime;
}

bool TimerMotorDriver::timerCallback(repeating_timer_t *repeatingTimer) {
    TimerMotorDriver *driver = (TimerMotorDriver *)(repeatingTimer->user_data);
    uint8_t stepPin = driver->getStepPin();
    gpio_put(stepPin, !gpio_get(stepPin));

    if (driver->getRotationEndTime() <= time_us_32()) {
        driver->stop();
        return false;
    }

    return true;  // keep repeating
};