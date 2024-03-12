#include <gtest/gtest.h>
#include "stepperMotorDriver.h"

// OneSuiteName

// TEST1: Creation Stepper Motor driver object

TEST(TestSuiteName, TestName)
{
    constexpr StpMotDriver_L293D l293d_Driver(1.8F);
    EXPECT_TRUE(1);
}

// TEST2: Check different ICs (integrated circuits) name
//        sets in right way - ICs are in predefined enums

// TEST3: Check if object with ICs generate proper 
//        operation mode

// TEST4: Check if ICs have right pins assignment
//        check it in compile time 
//        TODO

// TEST5: Check if object is created with proper angle step
//        of motor. The driver should handle only predefined
//        values. Should be checked at compile time

// TEST6: Check for GPIO_TOGGLING opeartion mode, that GPIOs
//        are set in right order

// TEST7: Check for GPIO_TOGGLING opeartion mode,
//        clockwise rotation

// TEST8: Check for GPIO_TOGGLING opeartion mode,
//        anti-clockwise rotation

// TEST9: Verify for GPIO_TOGGLING opeartion mode,
//        that pins in pair are not on in the same time

