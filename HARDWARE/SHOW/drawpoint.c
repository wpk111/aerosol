#include "sys.h"
#include "lcd.h"


drawxy(u16 *x)
{


u16 i;
LCD_Fill(0,50,320,150,BLACK);

for(i=1;i<321;i++)
  {
		
   LCD_Fast_DrawPoint(i,150-x[6*i]/41,RED);
  }

}


