#include <gtest/gtest.h>
#include "stepperMotorDriver.h"
#include "Mocks/HalWrapperMock.h"
#include <iostream>

GPIO_TypeDef gpioAdresses[NUM_OF_GPIOS];

void MockCallsAfterPinSetup(HalWrapperMock& halWrapperMock);
void MockCallsFirstStep(HalWrapperMock& halWrapperMock);
void MockCallsSecondStep(HalWrapperMock& halWrapperMock);
void MockCallsThirdStep(HalWrapperMock& halWrapperMock);
void MockCallsFirstStepReverse(HalWrapperMock& halWrapperMock);
void MockCallsSecondStepReverse(HalWrapperMock& halWrapperMock);
void MockCallsThirdStepReverse(HalWrapperMock& halWrapperMock);

// StepperDriver_L293D_Suite

// TEST1:  Creation Stepper Motor driver object

TEST(StepperDriver_L293D_Suite, CheckObjectCreation)
{
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    ASSERT_NE(&l293d_Driver, nullptr);
}

// TEST2:  Check different ICs (integrated circuits) name
//         sets in right way - ICs are in predefined enums

TEST(StepperDriver_L293D_Suite, CheckIfProperICIsSet)
{
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    ASSERT_EQ(l293d_Driver.GetICDriver(), ICDriver_e::L293D);
}

// TEST3:  Check if object with ICs generate proper 
//         operation mode
TEST(StepperDriver_L293D_Suite, CheckIfProperOperationMode)
{
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    ASSERT_EQ(l293d_Driver.GetOperationMode(), StpMotDriverMode_e::GPIO_TOGGLING);
}

// TEST4:  Check if ICs have right pins assignment
//         check it in compile time 
//         #TODO in future

// TEST5:  Check if object is created with proper angle step
//         of motor. The driver should handle only predefined
//         gpioValues. Should be checked at compile time
TEST(StepperDriver_L293D_Suite, CheckIfConstructedwithProperAngleValue)
{
    // Change Angle to not supported gpioValue. Compilation should not succeed
    const AngleX10 angle = 18;
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<angle> l293d_Driver(halWrapperMock);
    ASSERT_EQ(l293d_Driver.GetAngle(), angle);
}

// TEST6:  Check for GPIO_TOGGLING opeartion mode, that GPIOs
//         are set in right order
TEST(StepperDriver_L293D_Suite, CheckIfOrderOfPinsAssignedToDriver)
{
    // Where (Arrange)
    // Change Angle to not supported gpioValue. Compilation should not succeed
    // std::array<std::pair<GPIO_TypeDef*, PinNr>, 4> pinOrder = 
    // {{{GPIOA, GPIO_PIN_6}, {GPIOA, GPIO_PIN_7},
    //   {GPIOA, GPIO_PIN_8}, {GPIOA, GPIO_PIN_9}}};
    HalWrapperMock halWrapperMock;
    ::testing::NiceMock<HalWrapperMock> naggyMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};
    MockCallsAfterPinSetup(halWrapperMock);

    // When (Act)
    l293d_Driver.SetPinOrder(pinOrderTmp);

    // Then (Assert)
    EXPECT_TRUE(std::equal(pinOrderTmp.begin(), pinOrderTmp.end(), l293d_Driver.GetPinOrder().begin()));
}

// TEST7:  Check for GPIO_TOGGLING operation mode,
//         that HAL functions (HAL wrappers) are called
//         with proper parameters. Do one step of stepper motor
TEST(StepperDriver_L293D_Suite, CheckHalTogglePinInvocation)
{
    // Where (Arrange)
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};
    MockCallsAfterPinSetup(halWrapperMock);

    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(GPIOA, GPIO_PIN_6))
    .Times(1);
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(GPIOA, GPIO_PIN_7))
    .Times(1);

    // When (Act)
    l293d_Driver.SetPinOrder(pinOrderTmp);
    l293d_Driver.RotateMotorOneStep();

    // Then (Assert)
}
// TEST8:  Check for GPIO_TOGGLING operation mode,
//         that Pin logic level (voltage) is set by software.
//         The pins level should be set by HAL function
//         PA6 - 1, PA7 - 0, PA8 - 1, PA9 - 0
TEST(StepperDriver_L293D_Suite, CheckHalSetPinsState)
{
    // Where (Arrange)
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};

    EXPECT_CALL(halWrapperMock, GPIO_WritePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_6;
            *gpioPtr |= GPIO_PIN_6;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_8;
            *gpioPtr |= GPIO_PIN_8;
            }));
    EXPECT_CALL(halWrapperMock, GPIO_ResetPin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_7;
            *gpioPtr &= ~GPIO_PIN_7;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_9;
            *gpioPtr &= ~GPIO_PIN_9;
            }));

    // When (Act)
    l293d_Driver.SetPinOrder(pinOrderTmp);

    // Then (Assert)
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, GPIO_PIN_6);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, GPIO_PIN_8);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, 0);
}

// TEST9:  Check for GPIO_TOGGLING opeartion mode,
//         clockwise rotation
//         Sequence order:
// ---------------------------------------------------------
//         | PA6 | 1 | 0 | 0 | 1 |
//         |-----|---------------|
//         | PA7 | 0 | 1 | 1 | 0 |
//         |-----|---------------|
//         | PA8 | 1 | 1 | 0 | 0 |
//         |-----|---------------|
//         | PA9 | 0 | 0 | 1 | 1 |
//         |-----|---------------|
TEST(StepperDriver_L293D_Suite, CheckClockwiseRotation)
{
    // Where (Arrange)
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};
    MockCallsAfterPinSetup(halWrapperMock);
    // Mock calls when step motor rotate
    // Mock calls after first step
    MockCallsFirstStep(halWrapperMock);

    // // When (Act)
    l293d_Driver.SetPinOrder(pinOrderTmp);
    l293d_Driver.RotateMotorOneStep();
    // Then (Assert)
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, GPIO_PIN_7);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, GPIO_PIN_8);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, 0);

    // Mock calls after second step
    MockCallsSecondStep(halWrapperMock);
    l293d_Driver.RotateMotorOneStep();
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, GPIO_PIN_7);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, GPIO_PIN_9);

    // Mock calls after third step
    MockCallsThirdStep(halWrapperMock);
    l293d_Driver.RotateMotorOneStep();
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, GPIO_PIN_6);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, GPIO_PIN_9);
}

// TEST10:  Check for GPIO_TOGGLING opeartion mode,
//         anti-clockwise rotation
TEST(StepperDriver_L293D_Suite, CheckAntiClockwiseRotation)
{
    // Where (Arrange)
    HalWrapperMock halWrapperMock;
    StpMotDriver_L293D<18> l293d_Driver(halWrapperMock);
    PinOrder pinOrderTmp =  {{
                        std::make_pair(GPIOA, GPIO_PIN_6),
                        std::make_pair(GPIOA, GPIO_PIN_7),
                        std::make_pair(GPIOA, GPIO_PIN_8),
                        std::make_pair(GPIOA, GPIO_PIN_9)
    }};
    MockCallsAfterPinSetup(halWrapperMock);
    // Mock calls when step motor rotate
    // Mock calls after first step
    MockCallsFirstStepReverse(halWrapperMock);

    // // When (Act)
    l293d_Driver.SetPinOrder(pinOrderTmp);
    l293d_Driver.RotateMotorOneStepReverse();
    // Then (Assert)
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, GPIO_PIN_6);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, GPIO_PIN_9);

    // Mock calls after second step
    MockCallsSecondStepReverse(halWrapperMock);
    l293d_Driver.RotateMotorOneStepReverse();
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, GPIO_PIN_7);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, GPIO_PIN_9);

    // Mock calls after third step
    MockCallsThirdStepReverse(halWrapperMock);
    l293d_Driver.RotateMotorOneStepReverse();
    EXPECT_EQ(*GPIOA & GPIO_PIN_6, 0);
    EXPECT_EQ(*GPIOA & GPIO_PIN_7, GPIO_PIN_7);
    EXPECT_EQ(*GPIOA & GPIO_PIN_8, GPIO_PIN_8);
    EXPECT_EQ(*GPIOA & GPIO_PIN_9, 0);
}

// TEST11:  Check for GPIO_TOGGLING opeartion mode,
//         that pins in pair are not on in the same time


// ####################### Mock calls wrapped in functions ########################

void MockCallsAfterPinSetup(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_WritePin(GPIOA, GPIO_PIN_6))
    .Times(1);
    EXPECT_CALL(halWrapperMock, GPIO_ResetPin(GPIOA, GPIO_PIN_7))
    .Times(1);
    EXPECT_CALL(halWrapperMock, GPIO_WritePin(GPIOA, GPIO_PIN_8))
    .Times(1);
    EXPECT_CALL(halWrapperMock, GPIO_ResetPin(GPIOA, GPIO_PIN_9))
    .Times(1);
}

void MockCallsFirstStep(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_6;
            *gpioPtr &= ~GPIO_PIN_6;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_7;
            *gpioPtr |= GPIO_PIN_7;
            }));
}

void MockCallsSecondStep(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_8;
            *gpioPtr &= ~GPIO_PIN_8;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_9;
            *gpioPtr |= GPIO_PIN_9;
            }));
}

void MockCallsThirdStep(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_6;
            *gpioPtr |= GPIO_PIN_6;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_7;
            *gpioPtr &= ~GPIO_PIN_7;
            }));
}


void MockCallsFirstStepReverse(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_8;
            *gpioPtr &= ~GPIO_PIN_8;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_9;
            *gpioPtr |= GPIO_PIN_9;
            }));
}

void MockCallsSecondStepReverse(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_6;
            *gpioPtr &= ~GPIO_PIN_6;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_7;
            *gpioPtr |= GPIO_PIN_7;
            }));
}

void MockCallsThirdStepReverse(HalWrapperMock& halWrapperMock)
{
    EXPECT_CALL(halWrapperMock, GPIO_TogglePin(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_8;
            *gpioPtr |= GPIO_PIN_8;
            }))
        .WillOnce(::testing::Invoke([&](GPIO_TypeDef* gpioPtr, uint16_t gpioValue) {
            gpioValue = GPIO_PIN_9;
            *gpioPtr &= ~GPIO_PIN_9;
            }));
}
