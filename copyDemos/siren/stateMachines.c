#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

void state_advance()		
{
  static long cyc = 4000;   /* 500Hz = 4000 cycles */
  static char state = 0;
  char changed = 0;

  switch(state){            /* Switch with only 2 states */
  case 0:                   /* Going up with red led */
    if(!red_on){
      green_on = 0;
      red_on = 1;
      changed=1;
    }
    buzzer_set_period(cyc); /* Set buzzer with current cycle value */
    cyc=cyc-180;            /* Decrement cycle by 180 = 1/20 steps towards 400(5000Hz) */
    if(cyc==220){           /* When limit is reached we set cycle to 400 and move to next state */
      cyc=400;
      state=1;
    }
    break;
  case 1:                   /* Going down with green led */
    if(red_on){
      red_on = 0;
      green_on = 1;
      changed=1;
    }
    buzzer_set_period(cyc); 
    cyc=cyc+360;            /* In this state we increment cycle by 360 = 1/10 steps back to 4000 */
    if(cyc==4360){          /* When limit is reached reset cycle to 4000 and loop back to state 0*/
      cyc=4000;
      state=0;
    }
    break;
  }
  led_changed = changed;
  led_update();
}
