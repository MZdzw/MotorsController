#include "HalWrapper.h"

void HalWrapper::GPIO_WritePin(GPIO_TypeDef* gpio, PinNr pinNr) const
{
    HAL_GPIO_WritePin(gpio, pinNr, GPIO_PIN_SET);
}

void HalWrapper::GPIO_ResetPin(GPIO_TypeDef* gpio, PinNr pinNr) const
{
    HAL_GPIO_WritePin(gpio, pinNr, GPIO_PIN_RESET);
}

void HalWrapper::GPIO_TogglePin(GPIO_TypeDef* gpio, PinNr pinNr) const
{
    HAL_GPIO_TogglePin(gpio, pinNr);
}

