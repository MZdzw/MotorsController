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
    void GPIO_WritePin(GPIO_TypeDef* gpio, PinNr pinNr) const
    {
        static_cast<const T*>(this)->GPIO_WritePin();
    }
    void GPIO_ResetPin(GPIO_TypeDef* gpio, PinNr pinNr) const
    {
        static_cast<const T*>(this)->GPIO_WritePin();
    }
    void GPIO_TogglePin(GPIO_TypeDef* gpio, PinNr pinNr) const
    {
        static_cast<const T*>(this)->GPIO_TogglePin();
    }
    
};

class HalWrapper : public HalWrapperInterface<HalWrapper>
{
public:
    void GPIO_WritePin(GPIO_TypeDef* gpio, PinNr pinNr) const;
    void GPIO_ResetPin(GPIO_TypeDef* gpio, PinNr pinNr) const;
    void GPIO_TogglePin(GPIO_TypeDef* gpio, PinNr pinNr) const;
};

#endif

