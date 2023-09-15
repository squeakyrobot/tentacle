
#include <stdio.h>
#include <time.h>

#include "driver-configuration.h"
#include "pico/stdlib.h"
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

    StepperDriver *driver1 = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_64, 17, 16));
    StepperDriver *driver2 = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_64, 27, 26));

    puts("Motor 1");
    driver1->rotateDegrees(200, 360);
    sleep_us(driver1->calculateRotateTime_us(200, 360));

    puts("Motor 2");
    driver2->rotateDegrees(200, 360);
    while (driver2->getStatus() == Moving) {
        sleep_ms(100);
    }

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
