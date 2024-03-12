#include "stepperMotorDriver.h"

enum class StpMotDriverMode
{
    GPIO_TOGGLING, PWM
};

enum class StpMotGpio
{
    PA0, PA1, PA2, PA3,
    PA4, PA5, PA6, PA7,
    PA8, PA9, PA10, PA11,
    PA12, PA13, PA14, PA15,

    PB0, PB1, PB2, PB3,
    PB4, PB5, PB6, PB7,
    PB8, PB9, PB10, PB11,
    PB12, PB13, PB14, PB15,

    PC0, PC1, PC2, PC3,
    PC4, PC5, PC6, PC7,
    PC8, PC9, PC10, PC11,
    PC12, PC13, PC14, PC15,

    PD2,
    PF0, PF1, PF4, PF5, PF6, PF7
};

enum class StpMotGpioPWM
{
    PC7, PA6, PA7, PA9, PA8,
    PB10, PB4, PB5, PB3, PA10, PC8, PC6,
    PA11, PB11, PB1, PB15, PB14, PB13
};

