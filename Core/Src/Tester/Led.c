#include "Tester/Led.h"
#include "main.h"

static GPIO_TypeDef * const LedPorts[] = {
  GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,
  GPIOB, GPIOB, GPIOB
};

static const uint16_t LedPins[] = {
  Gelb_Pin, ROT_Pin, HS1_Pin, LS1_Pin, HS2_Pin, LS2_Pin, LS3_Pin, LS4_Pin,
  RGB_R_Pin, RGB_G_Pin, RGB_B_Pin
};

static void Led_Write(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state)
{
  HAL_GPIO_WritePin(port, pin, state);
}

static void Led_SetAll(GPIO_PinState state)
{
  for (size_t i = 0; i < sizeof(LedPins) / sizeof(LedPins[0]); ++i)
  {
    Led_Write(LedPorts[i], LedPins[i], state);
  }
}

static void Led_RgbSequence(void)
{
  const uint16_t rgbPins[] = { RGB_R_Pin, RGB_G_Pin, RGB_B_Pin };
  GPIO_TypeDef * const rgbPorts[] = { RGB_R_GPIO_Port, RGB_G_GPIO_Port, RGB_B_GPIO_Port };

  for (size_t i = 0; i < sizeof(rgbPins) / sizeof(rgbPins[0]); ++i)
  {
    Led_Write(rgbPorts[i], rgbPins[i], GPIO_PIN_SET);
    HAL_Delay(120);
    Led_Write(rgbPorts[i], rgbPins[i], GPIO_PIN_RESET);
    HAL_Delay(60);
  }

  Led_SetAll(GPIO_PIN_SET);
  HAL_Delay(140);
  Led_SetAll(GPIO_PIN_RESET);
  HAL_Delay(120);
}

static void Led_GpioSequence(void)
{
  for (size_t i = 0; i < 8; ++i)
  {
    Led_Write(LedPorts[i], LedPins[i], GPIO_PIN_SET);
    HAL_Delay(80);
    Led_Write(LedPorts[i], LedPins[i], GPIO_PIN_RESET);
    HAL_Delay(40);
  }
}

static void Led_GradualOn(void)
{
  for (size_t i = 0; i < sizeof(LedPins) / sizeof(LedPins[0]); ++i)
  {
    Led_Write(LedPorts[i], LedPins[i], GPIO_PIN_SET);
    HAL_Delay(60);
  }
  HAL_Delay(180);
}

void Led_Init(void)
{
  Led_SetAll(GPIO_PIN_RESET);
}

void Led_AllOff(void)
{
  Led_SetAll(GPIO_PIN_RESET);
}

void Led_RunTestPattern(void)
{
  Led_RgbSequence();
  Led_GpioSequence();
  Led_GradualOn();
  Led_AllOff();
  HAL_Delay(160);
}
