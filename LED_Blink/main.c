/*
* To toggle LED connected to PD12 and PD14 of STM32F407 Discovery Board
*Steps:
*Enable clock access to GPIOD
*Set PD12 AND PD14 as output
*Set ODR12 and ODR14 to 1(Turn ON)
*Call delay()
*Set ODR12 and ODR14 to 0(Turn OFF)
*/

#include <stdint.h>

void delay(void);

// RCC AHB1ENR base address
#define AHB1_BASE                  0x40020000U
#define RCC_BASE                   (AHB1_BASE + (0x3800U))
#define RCC_AHB1ENR                (uint32_t *)(RCC_BASE + (0x30U))
#define GPIOD_CLOCK_EN             (1U << 3U)

#define GPIOD_BASE                 (AHB1_BASE + (0x0C00U))
#define GPIOD_MODER                (uint32_t *)(GPIOD_BASE + (0x00U))
#define PD12_BIT_24_EN             (1U << 24U)
#define PD12_BIT_25_DISABLE        (~(1U << 25U))
#define PD14_BIT_28_EN             (1U << 28U)
#define PD14_BIT_29_DISABLE        (~(1U << 29U))

#define GPIOD_ODR                  (uint32_t *)(GPIOD_BASE + (0x14U))
#define PD12_OUTPUT_EN             (1U << 12U)
#define PD12_OUTPUT_DISABLE        (~(1U << 12U))
#define PD14_OUTPUT_EN             (1U << 14U)
#define PD14_OUTPUT_DISABLE        (~(1U << 14U))

int main(void)
{
    uint32_t *gpiod_clock, *gpiod_moder, *gpiod_odr;
    gpiod_clock = RCC_AHB1ENR;
    //Clock for GPIOD enabled
    *gpiod_clock |= GPIOD_CLOCK_EN;
   
    gpiod_moder = GPIOD_MODER;
    //PD12 set as output
    *gpiod_moder |= PD12_BIT_24_EN;
    *gpiod_moder &= PD12_BIT_25_DISABLE;
    //PD14 set as output
    *gpiod_moder |= PD14_BIT_28_EN;
    *gpiod_moder &= PD14_BIT_29_DISABLE;
    
     gpiod_odr = GPIOD_ODR;


    while (1)
    {
        //PD12 and PD14 set
        *gpiod_odr |= PD12_OUTPUT_EN;
        *gpiod_odr |= PD14_OUTPUT_EN;
        delay();
        //PD12 and PD14 reset
        *gpiod_odr &= PD12_OUTPUT_DISABLE;
        *gpiod_odr &= PD14_OUTPUT_DISABLE;
        delay();
    }

    return 0;
}

void delay(void)
{
    for (volatile int i = 0; i < 400000; i++);
}
