// include test framework
#include <gtest/gtest.h>
// include FreeRTOS headers
#include "FreeRTOS.h"
#include "task.h"
// inlcude header of the task which will be tested
#include "MovementElementTask.h"
#include "TaskInterfaces.h"

TaskHandle_t MovementElementTaskHanle_sh;
PositionMmX100 setPosition_sh = 0;
PositionMmX100 currentPosition_sh = 0;
bool isPositionReached_sh = false;
GPIO_TypeDef gpioAdresses[NUM_OF_GPIOS];

void SenderTask(void* Parameters_p)
{
    (void)Parameters_p;
    int cnt = *(int*) Parameters_p;
    for(int i = 0; i < cnt; ++i)
    {
        // Set delay to ensure startup of other task
        vTaskDelay(500 / portTICK_RATE_MS);
        xTaskNotifyGive(MovementElementTaskHanle_sh);
        // vTaskDelay(2000 / portTICK_RATE_MS);
    }
    
    // Set big delay that other tasks will end before this helper task
    // Other task should stop scheduler and then test should proceed to asserts
    vTaskDelay(30000 / portTICK_RATE_MS);
    vTaskDelete(NULL);
}

// MovementElementTask_AxisZ_Suite

// TEST1:  Check FreeRTOS working on Win
TEST(MovementElementTask_suite, CheckIfWorkingOnHost)
{
    int senderCnt = 1;
    setPosition_sh = 402;
    xTaskCreate(MovementElementTask, "MovementElementTask", 100, nullptr, 1, &MovementElementTaskHanle_sh);
    xTaskCreate(SenderTask, "SenderTask", 100, &senderCnt, 1, nullptr);

    vTaskStartScheduler();

    // After the task end its performance check currentPosition
    // should be same as the set one
    ASSERT_EQ(currentPosition_sh, 400);
}