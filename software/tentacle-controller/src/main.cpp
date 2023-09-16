
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

    // TentacleConfig config;
    // config.driver1Config = createMotorConfig(TMC2209_28BYJ48_16, 17, 16);
    // config.driver2Config = createMotorConfig(TMC2209_28BYJ48_16, 27, 26);

    // TentacleController *tc = TentacleController::create(config);

    StepperDriver *driver1 = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_16, 17, 16));
    StepperDriver *driver2 = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_16, 27, 26));

    printf("Motor 1 location: %d\n", driver1->getStepLocation());
    printf("Motor 2 location: %d\n", driver2->getStepLocation());
    sleep_ms(500);

    puts("Motor 1");
    driver1->rotateDegrees(255, 360);
    sleep_us(driver1->calculateRotateTime_us(255, 360));

    printf("Motor 1 location: %d\n", driver1->getStepLocation());
    printf("Motor 2 location: %d\n", driver2->getStepLocation());

    driver1->rotateDegrees(255, 360, CounterClockwise);
    while (driver1->getStatus() == Moving) {
        sleep_ms(100);
    }

    printf("Motor 1 location: %d\n", driver1->getStepLocation());
    printf("Motor 2 location: %d\n", driver2->getStepLocation());

    puts("Motor 2");
    driver2->rotateDegrees(200, 360);
    while (driver2->getStatus() == Moving) {
        sleep_ms(100);
    }

    printf("Motor 1 location: %d\n", driver1->getStepLocation());
    printf("Motor 2 location: %d\n", driver2->getStepLocation());

    sleep_ms(1072);
    gpio_put(LED_PIN, 0);

    for (;;) {
        puts("Entering Loop");

        bool dir = !driver1->getDirection();
        driver1->rotateDegrees(200, 700, (RotationDirection)dir);
        driver2->rotateDegrees(200, 700, (RotationDirection)dir);

        while (driver1->getStatus() == Moving) {
            sleep_ms(100);
        }

        driver1->rotateDegrees(200, 500, (RotationDirection)!dir);
        while (driver1->getStatus() == Moving) {
            sleep_ms(100);
        }

        driver1->rotateDegrees(200, 500, (RotationDirection)dir);
        while (driver1->getStatus() == Moving) {
            sleep_ms(100);
        }

        sleep_ms(500);
        driver2->rotateDegrees(200, 700, (RotationDirection)!dir);
        while (driver2->getStatus() == Moving) {
            sleep_ms(100);
        }

        puts("Turn Complete");
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        sleep_ms(1000);
    }
}
