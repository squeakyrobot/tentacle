# Development Board

TODO: Add more details about the board

## Pinout

### Microstep Configuration

Both motors share microstep configuration pins

| **DRV8825 Pin** 	| **Pico Pin** 	|
|-----------------	|----------------	|
| MODE 0           	| GPIO2          	|
| MODE 1           	| GPIO3          	|
| MODE 2          	| GPIO4          	|


### Motor 1

| **DRV8825 Pin** 	| **Pico Pin** 	    |
|-----------------	|----------------   |
| DIR             	| GPIO7          	|
| STEP            	| GPIO6          	|
| ENABLE          	| GND          	    |
| SLEEP           	| GPIO8          	|
| RESET           	| GND          	    |
| FAULT           	| GND          	    |


### Motor 2

| **DRV8825 Pin** 	| **Pico Pin** 	    |
|-----------------	|----------------   |
| DIR             	| GPIO10          	|
| STEP            	| GPIO9          	|
| ENABLE          	| GND          	    |
| SLEEP           	| GPIO8          	|
| RESET           	| GND          	    |
| FAULT           	| GND          	    |


### Motor 3

| **DRV8825 Pin** 	| **Pico Pin** 	    |
|-----------------	|----------------   |
| DIR             	| GPIO13          	|
| STEP            	| GPIO12          	|
| ENABLE          	| GND          	    |
| SLEEP           	| GPIO11          	|
| RESET           	| GND          	    |
| FAULT           	| GND          	    |


### Motor 4

| **DRV8825 Pin** 	| **Pico Pin** 	    |
|-----------------	|----------------   |
| DIR             	| GPIO16          	|
| STEP            	| GPIO15          	|
| ENABLE          	| GND          	    |
| SLEEP           	| GPIO14          	|
| RESET           	| GND          	    |
| FAULT           	| GND          	    |


### Motor Connectors

All motor connectors map to the same pins of their corresponding DRV8825 modules 

| **Connector Pin** | **DRV8825 Pin**   |
|-----------------	|----------------	|
| 1             	| B2          	    |
| 2            	    | B1          	    |
| 3          	    | A1          	    |
| 4           	    | A2          	    |