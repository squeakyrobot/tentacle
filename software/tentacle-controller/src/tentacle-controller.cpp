
#include <stdio.h>
#include "pico/stdlib.h"
#include "util.cpp"

#define DELAY 3 // 4 // 2

#define LED 0

#define STEP_PIN 17
#define DIR_PIN 16
#define FULL_STEPS_PER_REV 2048
#define MICRO_STEP_MULTIPLIER 0.125
#define STEPS_PER_REV FULL_STEPS_PER_REV / MICRO_STEP_MULTIPLIER
#define STEPS_PER_DEGREE STEPS_PER_REV / 360
#define MS 1000000

// TMC2209 with microsteps at 1/8 can go to 14000, but it gets too hot
// 12000 is a better upper limit
// 2100 is the fastest for DRV8830

#define MAX_SPEED 12000
#define MIN_SPEED 1000

// 0-100
#define SPEED 20

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
bool ledOn = false;

// int stepsPerRevolution = FULL_STEPS_PER_REV / MICRO_STEP_MULTIPLIER;

repeating_timer_t timer;

bool timer_callback(repeating_timer_t *rt)
{

    ledOn = !ledOn;
    gpio_put(LED_PIN, ledOn ? 1 : 0);

    uint8_t v = gpio_get(STEP_PIN);
    gpio_put(STEP_PIN, v == 1 ? 0 : 1);

    return true; // keep repeating
}

bool rotateMotor(int speed)
{
    int delay = normalizeRange(speed, MIN_SPEED, MAX_SPEED);

    return add_repeating_timer_us(-(MS / delay), timer_callback, NULL, &timer);
}

bool stopMotor()
{
    return cancel_repeating_timer(&timer);
}

uint32_t getWaitTimeUs(int speed, int rotationDegrees)
{
    int steps = rotationDegrees * STEPS_PER_DEGREE;
    int delay = normalizeRange(speed, MIN_SPEED, MAX_SPEED);

    float stepTime = (MS / delay) * 2;

    return stepTime * steps;
}

int main()
{
    gpio_init(STEP_PIN);
    gpio_init(DIR_PIN);
    gpio_set_dir(STEP_PIN, GPIO_OUT);
    gpio_set_dir(DIR_PIN, GPIO_OUT);

    gpio_put(DIR_PIN, 0);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // gpio_put(LED_PIN, 1);
    ledOn = true;

    stdio_init_all();

    // rotateMotor(1500);
    // sleep_ms(STEPS_PER_REV * 2);
    // stopMotor();

    rotateMotor(SPEED);
    uint32_t x = getWaitTimeUs(SPEED, 180);
    printf("x Wait Time %d\n", x);
    sleep_us(x);
    stopMotor();
    gpio_put(LED_PIN, 1);
    sleep_ms(1072);
    gpio_put(LED_PIN, 0);

    for (;;)
    {
        gpio_put(DIR_PIN, 1);
        rotateMotor(SPEED);
        sleep_us(getWaitTimeUs(SPEED, 360));
        stopMotor();
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        sleep_ms(SPEED);

        gpio_put(DIR_PIN, 0);
        rotateMotor(SPEED);
        sleep_us(getWaitTimeUs(SPEED, 360));
        stopMotor();

        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        sleep_ms(2000);
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
    }
}
