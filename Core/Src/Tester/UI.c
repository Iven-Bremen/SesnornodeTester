#include "Tester/UI.h"
#include "main.h"

static uint8_t buttonPressed = 0;
static uint32_t debounceTick = 0;

void UI_Init(void)
{
  buttonPressed = 0;
  debounceTick = HAL_GetTick();
}

uint8_t UI_ButtonPressed(void)
{
  GPIO_PinState state = HAL_GPIO_ReadPin(BTN_U_GPIO_Port, BTN_U_Pin);

  if (state == GPIO_PIN_RESET)
  {
    if (buttonPressed == 0 && (HAL_GetTick() - debounceTick) > 50)
    {
      buttonPressed = 1;
      return 1;
    }
  }
  else
  {
    buttonPressed = 0;
    debounceTick = HAL_GetTick();
  }

  return 0;
}
