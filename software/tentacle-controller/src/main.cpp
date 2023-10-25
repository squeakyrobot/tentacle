
#include <stdio.h>
#include <time.h>

#include "driver-configuration.h"
#include "pico/stdlib.h"
#include "tentacle-controller.h"
#include "timer-stepper-driver.h"
#include "util.h"

// TODO:
// 1. Create class - DONE
// 2. Be able to move n degrees - DONE
// 3. Be able to set limits - DONE
// 4. Be able to stop moving - DONE
// 5. Maybe track degrees moved, or location from start
//   5.1 Clockwise = positive, CounterClockwise = negative???
//   5.2 Sensorless homing to set start point???

// 0-255
#define SPEED 128

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

int main() {
    stdio_init_all();
    puts("Starting");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    TentacleConfig config;
    config.driver1Config = createMotorConfig(DRV8825_28BYJ48_64, 6, 7);
    config.driver2Config = createMotorConfig(DRV8825_28BYJ48_64, 9, 10);

    TentacleController *tc = TentacleController::create(config);

    // StepperDriver *driver1 = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_16, 17, 16));
    // StepperDriver *driver2 = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_16, 27, 26));
    tc->setSpeed(128);

    sleep_ms(1072);
    gpio_put(LED_PIN, 0);

    tc->moveTo(20, 0);
    while (tc->getStatus() == Moving) {
        sleep_ms(100);
    }

    tc->moveTo(0, 0);
    while (tc->getStatus() == Moving) {
        sleep_ms(100);
    }

    // tc->moveTo(0, 0);
    // while (tc->getStatus() == Moving) {
    //     sleep_ms(100);
    // }

    // tc->moveTo(25, 45);
    // while (tc->getStatus() == Moving) {
    //     sleep_ms(100);
    // }

    // tc->moveTo(25, 0);
    // while (tc->getStatus() == Moving) {
    //     sleep_ms(100);
    // }

    // tc->moveTo(0, 0);
    // while (tc->getStatus() == Moving) {
    //     sleep_ms(100);
    // }

    sleep_ms(1000);

    // tc->move(50, 45); // TODO: Check & fix move

    for (;;) {
        // puts("Entering Loop");

        tc->moveTo(25, 10);
        while (tc->getStatus() == Moving) {
            sleep_ms(500);
        }

        tc->moveTo(25, 90);
        while (tc->getStatus() == Moving) {
            sleep_ms(500);
        }

        tc->moveTo(25, 180);
        while (tc->getStatus() == Moving) {
            sleep_ms(500);
        }

        tc->moveTo(25, 270);
        while (tc->getStatus() == Moving) {
            sleep_ms(500);
        }

        tc->moveTo(25, 180);
        while (tc->getStatus() == Moving) {
            sleep_ms(500);
        }

        tc->moveTo(0, 0);
        while (tc->getStatus() == Moving) {
            sleep_ms(500);
        }

        sleep_ms(20000);
    }
}
