#include "FreeRTOS.h"
#include "task.h"
#include "BlinkingLEDTask.h"
#include "gpio.h"

void LEDTask(void* Parameters_p)
{
    (void)Parameters_p;
    for(;;)
    {
        vTaskDelay(500 / portTICK_RATE_MS);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }

    vTaskDelete(NULL);
}

