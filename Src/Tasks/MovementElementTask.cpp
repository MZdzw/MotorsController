#include "FreeRTOS.h"
#include "task.h"
#include "MovementElementTask.h"
#include "stepperMotorDriver.h"
#include "HalWrapper.h"
#include "TaskInterfaces.h"


void MovementElementTask(void* Parameters_p)
{
    (void)Parameters_p;
    HalWrapper halWrapper;
    StpMotDriver_L293D<18> l293d_Driver(halWrapper);
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};
    l293d_Driver.SetPinOrder(pinOrderTmp);
    MovementElement_AxisZ<8> movElemAxisZ(l293d_Driver);


    int notificationValue;
    for(;;)
    {
        notificationValue = ulTaskNotifyTake(pdTRUE, (TickType_t) portMAX_DELAY);
        if (notificationValue > 0)
        {
            movElemAxisZ.SetPositionMmX100(setPosition_sh);
            while (!movElemAxisZ.IsPositionReached())
            {
                if (movElemAxisZ.GetPositionMmX100() < 
                    movElemAxisZ.GetActualPositionMmX100())
                {
                    movElemAxisZ.MoveElementDown();
                }
                else 
                {
                    movElemAxisZ.MoveElementUp();
                }
                vTaskDelay(5 / portTICK_RATE_MS);  // keep the velocity const by now
                movElemAxisZ.SetPositionMmX100(setPosition_sh);
            }
        }
    }

    vTaskDelete(NULL);
}

