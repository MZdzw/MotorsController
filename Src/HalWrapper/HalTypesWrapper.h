#ifndef __HALTYPESWRAPPER_H__
#define __HALTYPESWRAPPER_H__

using GPIO_TypeDef = int;

#define NUM_OF_GPIOS 5
GPIO_TypeDef gpioAdresses[NUM_OF_GPIOS];

#define GPIOA ((GPIO_TypeDef*)(&gpioAdresses[0]))
#define GPIOB ((GPIO_TypeDef*)(&gpioAdresses[1]))
#define GPIOC ((GPIO_TypeDef*)(&gpioAdresses[2]))
#define GPIOD ((GPIO_TypeDef*)(&gpioAdresses[3]))
#define GPIOE ((GPIO_TypeDef*)(&gpioAdresses[4]))

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

#endif

