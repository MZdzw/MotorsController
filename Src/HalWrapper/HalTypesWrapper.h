#ifndef __HALTYPESWRAPPER_H__
#define __HALTYPESWRAPPER_H__

using GPIO_TypeDef = int;

#define NUM_OF_GPIOS 5
extern GPIO_TypeDef gpioAdresses[NUM_OF_GPIOS];

#define GPIOA ((GPIO_TypeDef*)(&gpioAdresses[0]))
#define GPIOB ((GPIO_TypeDef*)(&gpioAdresses[1]))
#define GPIOC ((GPIO_TypeDef*)(&gpioAdresses[2]))
#define GPIOD ((GPIO_TypeDef*)(&gpioAdresses[3]))
#define GPIOE ((GPIO_TypeDef*)(&gpioAdresses[4]))

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */

#endif

