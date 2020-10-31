#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

void siren()
{
  static long cyc = 4000;   /* 500Hz = 4000 cycles */
  static char state = 0;
  switch(state){            /* Switch with only 2 states */
  case 0:                   /* Going up with red led */
    buzzer_set_period(cyc); /* Set buzzer with current cycle value */
    cyc=cyc-20;            /* Decrement cycle by 180 = 1/20 steps towards 400(5000Hz) */
    if(cyc==580){           /* When limit is reached we set cycle to 400 and move to next state */
      cyc=600;
      state=1;
    }
    break;
  case 1:                   /* Going down with green led */
    buzzer_set_period(cyc);
    cyc=cyc+10;            /* In this state we increment cycle by 360 = 1/10 steps back to 4000 */
    if(cyc==4210){          /* When limit is reached reset cycle to 4000 and loop back to state 0*/
      cyc=4200;
      state=0;
    }
    break;
  }
}

void dim_rg_led()
{
  static char ledState=0;
  switch(ledState){
  case 0:         /* leds are both off from 0-2 */
    red_on=0;
    green_on=0;
    ledState++;
    break;
  case 5:         /* leds are on at 3 */
    red_on=1;
    green_on=1;
    ledState=0;
    break;
  default:
    ledState++;
  }
  led_changed=1;
  led_update();
  
}

void both_led_off(){
  red_on=0;
  green_on=0;
  led_changed=1;
  led_update();
}

void alternate_led(){
  static char ledState=0;
  switch(ledState){
  case 0:
    red_on=1;
    green_on=0;
    ledState++;
    break;
  case 20:
    red_on=0;
    green_on=1;
    ledState++;
    break;
  case 40:
    ledState=0;
    break;
  default:
    ledState++;
  }
  led_changed=1;
  led_update();
}

void no_dim(){
  red_on=1;
  green_on=1;
  led_changed=1;
  led_update();
}

void state_advance()		
{
  static char sirenCount=0;
  if(bState==0){
    dim_rg_led();
  }
  else if(bState==1){
    both_led_off();
  }
  else if(bState==2){
    sirenCount++;
    if(sirenCount==2){
      siren();
      sirenCount=0;
    }
    alternate_led();
  }
  else if(bState==3){
    no_dim();
  }
}
