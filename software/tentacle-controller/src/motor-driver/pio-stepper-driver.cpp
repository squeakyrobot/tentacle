// #include "pio-stepper-driver.h"

// PioStepperDriver::PioStepperDriver(StepperDriverConfig config) : StepperDriver(config) {
//     gpio_init(config.stepPin);
//     gpio_init(config.directionPin);
//     gpio_set_dir(config.stepPin, GPIO_OUT);
//     gpio_set_dir(config.directionPin, GPIO_OUT);
//     gpio_put(config.directionPin, (this->config.invertDirection) ? !Clockwise : Clockwise);
// };

// PioStepperDriver::~PioStepperDriver(){
//     // TODO: clean up
// };

// bool PioStepperDriver::rotateSteps(uint8_t speed, uint32_t steps, RotationDirection direction) {
//     if (this->direction != direction) {
//         this->direction = direction;
//         gpio_put(this->config.directionPin, (this->config.invertDirection) ? !direction : direction);
//     }

//     if (this->timer.alarm_id > 0) {
//         cancel_repeating_timer(&this->timer);
//     }

//     if (speed < 1) {
//         return false;
//     }

//     uint32_t stepsPerSecond = this->calculateStepsPerSecond(speed);

//     this->remainingSteps = steps;
//     this->status = Moving;

//     // It takes two timer triggers to complete one step
//     uint32_t delay = stepsPerSecond * 2;

//     return add_repeating_timer_us(-(1000000 / (double)delay), PioStepperDriver::timerCallback, this, &this->timer);
// };

// bool PioStepperDriver::stop() {
//     this->status = Stopped;

//     return false
// };
