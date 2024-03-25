#ifndef __STEPPERMOTOR_L293DMOCK_H__
#define __STEPPERMOTOR_L293DMOCK_H__
#include "stepperMotorDriver.h"
#include "gmock/gmock.h"
#include <iostream>

template<AngleX10 angle>
struct StpMotDriver_L293DMock : public StpMotDriver<StpMotDriver_L293DMock<angle>>
{
    StpMotDriver_L293DMock() : StpMotDriver<StpMotDriver_L293DMock<angle>>() { }

    // void RotateMotorOneStep()
    // {
    //     std::cout << "Rotate One Step\n";
    // }

    // void RotateMotorOneStepReverse()
    // {
    //     std::cout << "Rotate One Step Reverse\n";
    // }

    MOCK_METHOD(void, RotateMotorOneStep, ());
    MOCK_METHOD(void, RotateMotorOneStepReverse, ());
    // MOCK_METHOD(void, GPIO_TogglePin, (GPIO_TypeDef* gpio, PinNr pinNr));
};

#endif

