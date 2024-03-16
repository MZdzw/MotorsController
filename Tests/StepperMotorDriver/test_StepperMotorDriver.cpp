#include <gtest/gtest.h>
#include "stepperMotorDriver.h"
#include "Mocks/HalWrapperMock.h"

GPIO_TypeDef gpioAdresses[NUM_OF_GPIOS];

// StepperDriver_L293D_Suite

// TEST1:  Creation Stepper Motor driver object

TEST(StepperDriver_L293D_Suite, CheckObjectCreation)
{
    constexpr StpMotDriver_L293D l293d_Driver(18);
    EXPECT_TRUE(1);
}

// TEST2:  Check different ICs (integrated circuits) name
//         sets in right way - ICs are in predefined enums

TEST(StepperDriver_L293D_Suite, CheckIfProperICIsSet)
{
    constexpr StpMotDriver_L293D l293d_Driver(18);
    EXPECT_TRUE(l293d_Driver.GetICDriver() == ICDriver_e::L293D);
}

// TEST3:  Check if object with ICs generate proper 
//         operation mode
TEST(StepperDriver_L293D_Suite, CheckIfProperOperationMode)
{
    constexpr StpMotDriver_L293D l293d_Driver(18);
    EXPECT_TRUE(l293d_Driver.GetOperationMode() == StpMotDriverMode_e::GPIO_TOGGLING);
}

// TEST4:  Check if ICs have right pins assignment
//         check it in compile time 
//         #TODO in future

// TEST5:  Check if object is created with proper angle step
//         of motor. The driver should handle only predefined
//         values. Should be checked at compile time
TEST(StepperDriver_L293D_Suite, CheckIfConstructedwithProperAngleValue)
{
    // Change Angle to not supported value. Compilation should not succeed
    const AngleX10 angle = 18;
    constexpr StpMotDriver_L293D l293d_Driver(angle); 
    EXPECT_TRUE(l293d_Driver.GetAngle() == angle);
}

// TEST6:  Check for GPIO_TOGGLING opeartion mode, that GPIOs
//         are set in right order

// TEST7:  Check for GPIO_TOGGLING opeartion mode,
//         clockwise rotation

// TEST8:  Check for GPIO_TOGGLING opeartion mode,
//         anti-clockwise rotation

// TEST9:  Check for GPIO_TOGGLING opeartion mode,
//         that pins in pair are not on in the same time

// TEST10: Check for GPIO_TOGGLING operation mode,
//         that HAL functions (HAL wrappers) are called
//         with proper parameters

