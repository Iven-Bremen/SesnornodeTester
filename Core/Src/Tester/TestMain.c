#include "Tester/TestMain.h"
#include "Tester/Led.h"
#include "Tester/UI.h"

void TestMain_Run(void)
{
  UI_Init();
  Led_Init();

  uint8_t testEnabled = 1;

  while (1)
  {
    if (UI_ButtonPressed())
    {
      testEnabled = !testEnabled;
    }

    if (testEnabled)
    {
      Led_RunTestPattern();
    }
    else
    {
      Led_AllOff();
      HAL_Delay(100);
    }
  }
}
