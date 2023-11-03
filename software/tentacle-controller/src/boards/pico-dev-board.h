/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_PICO_DEV_BOARD_H
#define _BOARDS_PICO_DEV_BOARD_H

// For board detection
#define PICO_DEV_BOARD

// TENTACLE CONTROLLER PIN CONFIGURATION
// --------------------------------------

#define MODE0_PIN 2
#define MODE1_PIN 3
#define MODE2_PIN 4

// Not present on dev board
// #define MOTOR_ENABLE_PIN 5

#define MOTOR_A_DIR_PIN 7
#define MOTOR_A_STEP_PIN 6
#define MOTOR_A_SLEEP_PIN 8

// Not present on dev board
// #define MOTOR_A_RESET_PIN 9
// #define MOTOR_A_HOME_PIN 0
// #define MOTOR_A_FAULT_PIN 7

#define MOTOR_1_DIR_PIN MOTOR_A_DIR_PIN
#define MOTOR_1_STEP_PIN MOTOR_A_STEP_PIN
#define MOTOR_1_SLEEP_PIN MOTOR_A_SLEEP_PIN

#define MOTOR_B_DIR_PIN 10
#define MOTOR_B_STEP_PIN 9
#define MOTOR_B_SLEEP_PIN 8

// Not present on dev board
// #define MOTOR_B_RESET_PIN 15
// #define MOTOR_B_HOME_PIN 10
// #define MOTOR_B_FAULT_PIN 13

#define MOTOR_2_DIR_PIN MOTOR_B_DIR_PIN
#define MOTOR_2_STEP_PIN MOTOR_B_STEP_PIN
#define MOTOR_2_SLEEP_PIN MOTOR_B_SLEEP_PIN

#define MOTOR_3_DIR_PIN 13
#define MOTOR_3_STEP_PIN 12
#define MOTOR_3_SLEEP_PIN 11

#define MOTOR_4_DIR_PIN 16
#define MOTOR_4_STEP_PIN 15
#define MOTOR_4_SLEEP_PIN 14

// --- UART ---
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 0
#endif
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 1
#endif

// --- LED ---
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25
#endif
// no PICO_DEFAULT_WS2812_PIN

// --- I2C ---
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 4
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif

// --- SPI ---
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
#endif
#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN 18
#endif
#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN 19
#endif
#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN 16
#endif
#ifndef PICO_DEFAULT_SPI_CSN_PIN
#define PICO_DEFAULT_SPI_CSN_PIN 17
#endif

// --- FLASH ---

#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif

// Drive high to force power supply into PWM mode (lower ripple on 3V3 at light loads)
#define PICO_SMPS_MODE_PIN 23

#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 1
#endif

// The GPIO Pin used to read VBUS to determine if the device is battery powered.
#ifndef PICO_VBUS_PIN
#define PICO_VBUS_PIN 24
#endif

// The GPIO Pin used to monitor VSYS. Typically you would use this with ADC.
// There is an example in adc/read_vsys in pico-examples.
#ifndef PICO_VSYS_PIN
#define PICO_VSYS_PIN 29
#endif

#endif
