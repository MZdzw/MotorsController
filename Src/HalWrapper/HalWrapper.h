#ifndef __HALWRAPPER_H__
#define __HALWRAPPER_H__
#include <stdint.h>
#ifndef TESTING
#include "gpio.h"
#else
#include "HalTypesWrapper.h"
#endif

using PinNr = uint16_t;

template <typename T>
class HalWrapperInterface
{
public:
    void GPIO_WritePin(GPIO_TypeDef* gpio, PinNr pinNr)
    {
        static_cast<T&>(*this).GPIO_WritePin(gpio, pinNr);
    }
    void GPIO_ResetPin(GPIO_TypeDef* gpio, PinNr pinNr)
    {
        static_cast<T&>(*this).GPIO_ResetPin(gpio, pinNr);
    }
    void GPIO_TogglePin(GPIO_TypeDef* gpio, PinNr pinNr)
    {
        static_cast<T&>(*this).GPIO_TogglePin(gpio, pinNr);
    }
    
};

class HalWrapper : public HalWrapperInterface<HalWrapper>
{
public:
    void GPIO_WritePin(GPIO_TypeDef* gpio, PinNr pinNr);
    void GPIO_ResetPin(GPIO_TypeDef* gpio, PinNr pinNr);
    void GPIO_TogglePin(GPIO_TypeDef* gpio, PinNr pinNr);
};

#endif

