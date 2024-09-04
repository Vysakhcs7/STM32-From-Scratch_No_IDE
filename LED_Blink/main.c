#include <stdint.h>

void delay(void)
{
    for (volatile int i = 0; i < 100000; i++);
}

// RCC AHB1ENR base address
#define RCC_BASE_ADDR               (0x40023800U)
#define RCC_AHB1ENR_OFFSET          (0x30U)
#define RCC_AHB1ENR_ADDR            (RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET)

// GPIOD base address
#define AHB1_BASE_ADDR              (0x40020000U)
#define GPIOD_BASE_OFFSET           (0x0C00U)
#define GPIOD_BASE_ADDR             (AHB1_BASE_ADDR + GPIOD_BASE_OFFSET)

// GPIO port mode register base address
#define GPIOD_MODER_OFFSET          (0x00U)
#define GPIOD_MODER_BASE_ADDR       (GPIOD_BASE_ADDR + GPIOD_MODER_OFFSET)

// GPIO port output data register base address
#define GPIOD_ODR_OFFSET            (0x14U)
#define GPIOD_ODR_BASE_ADDR         (GPIOD_BASE_ADDR + GPIOD_ODR_OFFSET)

int main(void)
{
    // Enable clock for GPIOD (Bit 3 GPIODEN: IO port D clock enable in RCC_AHB1ENR register)
    uint32_t *pRCC = (uint32_t *)RCC_AHB1ENR_ADDR;
    *pRCC |=  0x00000008;

    // Set PD12 and PD14 as General purpose output mode
    // PD12 corresponds to MODER12[1:0] -> Bits 24-25
    // PD14 corresponds to MODER14[1:0] -> Bits 28-29
    uint32_t *pGPIOD_MODER = (uint32_t *)GPIOD_MODER_BASE_ADDR;
    *pGPIOD_MODER &= ~((0x3 << 24) | (0x3 << 28));  // Clear MODER12 and MODER14
    *pGPIOD_MODER |=  ((0x1 << 24) | (0x1 << 28));  // Set MODER12 and MODER14 as output

    uint32_t *pGPIOD_ODR = (uint32_t *)GPIOD_ODR_BASE_ADDR;

    while (1)
    {
        // Set PD12 and PD14 (Bits 12 and 14) to high
        *pGPIOD_ODR |= (1 << 12) | (1 << 14);
        delay();

        // Set PD12 and PD14 to low
        *pGPIOD_ODR &= ~((1 << 12) | (1 << 14));
        delay();
    }

    return 0;
}
