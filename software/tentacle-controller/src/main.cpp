
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

    // Setup micro stepping -
    // TODO: wrap this into an easy to use function
    gpio_init(MODE0_PIN);
    gpio_set_dir(MODE0_PIN, GPIO_OUT);
    gpio_put(MODE0_PIN, 0);

    gpio_init(MODE1_PIN);
    gpio_set_dir(MODE1_PIN, GPIO_OUT);
    gpio_put(MODE1_PIN, 0);

    gpio_init(MODE2_PIN);
    gpio_set_dir(MODE2_PIN, GPIO_OUT);
    gpio_put(MODE2_PIN, 0);

    // // Enable - NOT REQUIRED
    // gpio_init(MOTOR_ENABLE_PIN);
    // gpio_set_dir(MOTOR_ENABLE_PIN, GPIO_OUT);
    // gpio_put(MOTOR_ENABLE_PIN, 0);

    // Sleep - REQUIRED
    gpio_init(MOTOR_A_SLEEP_PIN);
    gpio_set_dir(MOTOR_A_SLEEP_PIN, GPIO_OUT);
    gpio_put(MOTOR_A_SLEEP_PIN, 1);

    gpio_init(MOTOR_B_SLEEP_PIN);
    gpio_set_dir(MOTOR_B_SLEEP_PIN, GPIO_OUT);
    gpio_put(MOTOR_B_SLEEP_PIN, 1);

    // Reset - REQUIRED
    gpio_init(MOTOR_A_RESET_PIN);
    gpio_set_dir(MOTOR_A_RESET_PIN, GPIO_OUT);
    gpio_put(MOTOR_A_RESET_PIN, 1);

    gpio_init(MOTOR_B_RESET_PIN);
    gpio_set_dir(MOTOR_B_RESET_PIN, GPIO_OUT);
    gpio_put(MOTOR_B_RESET_PIN, 1);

    TentacleConfig config;
    // config.driver1Config = createMotorConfig(DRV8825_28BYJ48_64, 6, 7);
    // config.driver2Config = createMotorConfig(DRV8825_28BYJ48_64, 9, 10);

    config.driver1Config = createMotorConfig(DRV8825_28BYJ48_64, MOTOR_A_STEP_PIN, MOTOR_A_DIR_PIN);
    config.driver2Config = createMotorConfig(DRV8825_28BYJ48_64, MOTOR_B_STEP_PIN, MOTOR_B_DIR_PIN);

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
