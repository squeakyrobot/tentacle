
#include <time.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "util.cpp"
#include "timer-motor-driver.h"

// TODO:
// 1. Create class
// 2. Be able to move n degrees
// 3. Be able to set limits
// 4. Be able to stop moving
// 5. Maybe track degrees moved, or location from start
//   5.1 MotorDirCW = positive, MotorDirCCW = negative???
//   5.2 Sensorless homing to set start point???

// 0-255
#define SPEED 200

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

TimerMotorDriver *driver = new TimerMotorDriver({
    directionPin : 16,
    stepPin : 17,
    stepsPerRevolution : 2048,
    microStepMultiplier : 8,
    maxPulsesPerSecond : 12000,
    minPulsesPerSecond : 1000
});

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    stdio_init_all();

    driver->rotate(SPEED, 720);

    printf("TEST: %d\n", driver->getStatus());

    uint32_t x = driver->calculateRotateTime_us(SPEED, 720);

    sleep_us(x);
    driver->stop();
    gpio_put(LED_PIN, 1);
    sleep_ms(1072);
    gpio_put(LED_PIN, 0);

    uint16_t degrees = 10;
    uint8_t speed = 10;

    for (;;)
    {

        degrees += 10;
        speed += 10;

        if (degrees > 360)
        {
            degrees = 10;
        }

        if (speed > 250)
        {
            speed = 10;
        }

        driver->rotate(speed, degrees, (driver->getDirection() == MotorDirCW) ? MotorDirCCW : MotorDirCW);

        while (driver->getStatus() == MotorRunning)
        {
            sleep_ms(100);
        }

        gpio_put(LED_PIN, !gpio_get(LED_PIN));
    }
}
