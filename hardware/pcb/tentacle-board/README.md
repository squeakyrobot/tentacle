# Tentacle Controller PCB

TODO: Add more details about the board

## Pinout

Both motors share microstep configuration pins and the enable pin.

### Microstep Configuration

| **DRV8825 Pin** 	| **RP2040 Pin** 	|
|-----------------	|----------------	|
| MODE 0           	| GPIO3          	|
| MODE 1           	| GPIO2          	|
| MODE 2          	| GPIO1          	|



### Motor A

| **DRV8825 Pin** 	| **RP2040 Pin** 	|
|-----------------	|----------------	|
| DIR             	| GPIO6          	|
| STEP            	| GPIO4          	|
| ENABLE          	| GPIO5          	|
| SLEEP           	| GPIO8          	|
| RESET           	| GPIO9          	|
| HOME            	| GPIO0          	|
| FAULT           	| GPIO7          	|


### Motor B

| **DRV8825 Pin** 	| **RP2040 Pin** 	|
|-----------------	|----------------	|
| DIR             	| GPIO12          	|
| STEP            	| GPIO11          	|
| ENABLE          	| GPIO5          	|
| SLEEP           	| GPIO14          	|
| RESET           	| GPIO15          	|
| HOME            	| GPIO10          	|
| FAULT           	| GPIO13          	|


### Debug Connector

| **Connector Pin** | **RP2040 Pin** |
|-----------------	|----------------|
| 1             	| SWCLK          |
| 2            	    | GND          	 |
| 3           	    | SWD          	 |


### UART Connector

| **Connector Pin** | **RP2040 Pin**    | **Pin Functions** |
|-----------------	|----------------   |----------------   |
| 1             	| GPIO17            | UART0 RX          |
| 2            	    | GND          	    |                   |
| 3           	    | GPIO16            | UART0 TX          |


### CTRL Connector

| **Connector Pin** | **RP2040 Pin**    | **Pin Functions**     |
|-----------------	|----------------   |----------------       |
| 1             	| GND               |                       |
| 2            	    | RUN      	        | Reset when driven low |
| 3           	    | GPIO19            |                       |
| 4           	    | GPIO20            | UART1 TX, I2C0 SDA    |
| 5           	    | GPIO21            | UART1 RX, I2C0 SCL    |


### AUX1 Connector

| **Connector Pin** | **RP2040 Pin**    | **Pin Functions**     |
|-----------------	|----------------   |----------------       |
| 1             	| GND               |                       |
| 2            	    | GPIO22      	    |                       |
| 3           	    | GPIO23            |                       |
| 4           	    | GPIO24            |                       |
| 5           	    | GPIO25            |                       |


### AUX2 Connector

| **Connector Pin** | **RP2040 Pin**    | **Pin Functions**     |
|-----------------	|----------------   |----------------       |
| 1             	| GND               |                       |
| 2            	    | GPIO26      	    | ADC0                  |
| 3           	    | GPIO27            | ADC1                  |
| 4           	    | GPIO28            | ADC2                  |
| 5           	    | GPIO29            | ADC3                  |


### Motor Connectors

All motor connectors map to the same pins of their corresponding DRV8825 modules 

| **Connector Pin** | **DRV8825 Pin**   |
|-----------------	|----------------	|
| 1             	| B2          	    |
| 2            	    | B1          	    |
| 3          	    | A1          	    |
| 4           	    | A2          	    |


## Revision History

### v1.0

 * Initial Release

### v1.1

 * **NOT COMPLETE**
 * Fix issue with missing silkscreen items

## TODO:

 * Investigate alternative motor connectors
 * Investigate alternative power connector
