#include <gtest/gtest.h>
#include "stepperMotorDriver.h"
#include "Mocks/HalWrapperMock.h"
#include <iostream>

GPIO_TypeDef gpioAdresses[NUM_OF_GPIOS];

// StepperDriver_L293D_Suite

// TEST1:  Creation Stepper Motor driver object

TEST(StepperDriver_L293D_Suite, CheckObjectCreation)
{
    StpMotDriver_L293D<18> l293d_Driver;
    ASSERT_NE(&l293d_Driver, nullptr);
}

// TEST2:  Check different ICs (integrated circuits) name
//         sets in right way - ICs are in predefined enums

TEST(StepperDriver_L293D_Suite, CheckIfProperICIsSet)
{
    StpMotDriver_L293D<18> l293d_Driver;
    ASSERT_EQ(l293d_Driver.GetICDriver(), ICDriver_e::L293D);
}

// TEST3:  Check if object with ICs generate proper 
//         operation mode
TEST(StepperDriver_L293D_Suite, CheckIfProperOperationMode)
{
    StpMotDriver_L293D<18> l293d_Driver;
    ASSERT_EQ(l293d_Driver.GetOperationMode(), StpMotDriverMode_e::GPIO_TOGGLING);
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
    StpMotDriver_L293D<angle> l293d_Driver; 
    ASSERT_EQ(l293d_Driver.GetAngle(), angle);
}

// TEST6:  Check for GPIO_TOGGLING opeartion mode, that GPIOs
//         are set in right order
TEST(StepperDriver_L293D_Suite, CheckIfOrderOfPinsAssignedToDriver)
{
    // Where (Arrange)
    // Change Angle to not supported value. Compilation should not succeed
    // std::array<std::pair<GPIO_TypeDef*, PinNr>, 4> pinOrder = 
    // {{{GPIOA, GPIO_PIN_6}, {GPIOA, GPIO_PIN_7},
    //   {GPIOA, GPIO_PIN_8}, {GPIOA, GPIO_PIN_9}}};
    StpMotDriver_L293D<18> obj;
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};

    // When (Act)
    obj.SetPinOrder(pinOrderTmp);

    // Then (Assert)
    EXPECT_TRUE(std::equal(pinOrderTmp.begin(), pinOrderTmp.end(), obj.GetPinOrder().begin()));
}

// TEST7:  Check for GPIO_TOGGLING opeartion mode,
//         clockwise rotation

// TEST8:  Check for GPIO_TOGGLING opeartion mode,
//         anti-clockwise rotation

// TEST9:  Check for GPIO_TOGGLING opeartion mode,
//         that pins in pair are not on in the same time

// TEST10: Check for GPIO_TOGGLING operation mode,
//         that HAL functions (HAL wrappers) are called
//         with proper parameters

