#ifndef __HALWRAPPERMOCK_H__
#define __HALWRAPPERMOCK_H__
#include "HalWrapper.h"
#include "gmock/gmock.h"

struct HalWrapperMock : public HalWrapperInterface<HalWrapperMock>
{
    HalWrapperMock() : HalWrapperInterface() { }
    // void GPIO_WritePin(GPIO_TypeDef* gpio, PinNr pinNr) const { }
    // void GPIO_ResetPin(GPIO_TypeDef* gpio, PinNr pinNr) const { }

    MOCK_METHOD(void, GPIO_WritePin, (GPIO_TypeDef* gpio, PinNr pinNr));
    MOCK_METHOD(void, GPIO_ResetPin, (GPIO_TypeDef* gpio, PinNr pinNr));
    MOCK_METHOD(void, GPIO_TogglePin, (GPIO_TypeDef* gpio, PinNr pinNr));

};

#endif

