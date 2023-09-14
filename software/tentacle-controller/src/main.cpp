
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
//   5.1 MotorDirCW = positive, MotorDirCCW = negative???
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

    StepperDriver *driver = new TimerStepperDriver(createMotorConfig(TMC2209_28BYJ48_64, 17, 16));

    puts("First Rotation");
    driver->rotateDegrees(255, 1440);
    sleep_us(driver->calculateRotateTime_us(255, 1440));

    printf("TEST: %d\n", driver->getStatus());

    while (driver->getStatus() == MotorRunning) {
        sleep_ms(100);
    }

    sleep_ms(1072);
    gpio_put(LED_PIN, 0);

    uint16_t degrees = 10;
    uint8_t speed = 10;

    for (;;) {
        puts("Entering Loop");

        driver->rotateDegrees(255, 360, (driver->getDirection() == MotorDirCW) ? MotorDirCCW : MotorDirCW);
        uint32_t ms = driver->calculateRotateTime_ms(255, 360);

        while (driver->getStatus() == MotorRunning) {
            sleep_ms(100);
        }

        puts("Turn Complete");
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        sleep_ms(1000);
    }
}
