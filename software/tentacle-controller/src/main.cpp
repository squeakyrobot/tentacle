
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

int main() {
    stdio_init_all();
    puts("Starting");
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    // gpio_put(LED_PIN, 1);

    // Setup micro stepping
    // TODO: wrap this into an easy to use function
    gpio_init(M0_PIN);
    gpio_set_dir(M0_PIN, GPIO_OUT);
    gpio_put(M0_PIN, 0);

    gpio_init(M1_PIN);
    gpio_set_dir(M1_PIN, GPIO_OUT);
    gpio_put(M1_PIN, 0);

    gpio_init(M2_PIN);
    gpio_set_dir(M2_PIN, GPIO_OUT);
    gpio_put(M2_PIN, 0);

    // Enable, this should not be needed
    gpio_init(MOTOR_ENABLE_PIN);
    gpio_set_dir(MOTOR_ENABLE_PIN, GPIO_OUT);
    gpio_put(MOTOR_ENABLE_PIN, 0);

    // Sleep, this should not be needed
    gpio_init(MA_SLEEP_PIN);
    gpio_set_dir(MA_SLEEP_PIN, GPIO_OUT);
    gpio_put(MA_SLEEP_PIN, 1);

    gpio_init(MB_SLEEP_PIN);
    gpio_set_dir(MB_SLEEP_PIN, GPIO_OUT);
    gpio_put(MB_SLEEP_PIN, 1);

    // Reset
    gpio_init(MA_RESET_PIN);
    gpio_set_dir(MA_RESET_PIN, GPIO_OUT);
    gpio_put(MA_RESET_PIN, 1);

    gpio_init(MB_RESET_PIN);
    gpio_set_dir(MB_RESET_PIN, GPIO_OUT);
    gpio_put(MB_RESET_PIN, 1);

    TentacleConfig config;
    // config.driver1Config = createMotorConfig(DRV8825_28BYJ48_64, 6, 7);
    // config.driver2Config = createMotorConfig(DRV8825_28BYJ48_64, 9, 10);

    config.driver1Config = createMotorConfig(DRV8825_28BYJ48_16, MA_STEP_PIN, MA_DIR_PIN);
    config.driver2Config = createMotorConfig(DRV8825_28BYJ48_16, MB_STEP_PIN, MB_DIR_PIN);

    TentacleController *tc = TentacleController::create(config);

    tc->setSpeed(220);

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

        sleep_ms(10000);
    }
}
