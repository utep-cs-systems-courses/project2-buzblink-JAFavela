#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

void chona()
{
  static int songState=0;

  switch(songState){
  case 242:
    songState=0;
  default:
    buzzer_set_period(cSong[songState]);
    led_switch(cSong[songState]);
    songState++;
  }  
}

void siren()
{
  static int cyc = 4000;   /* 500Hz = 4000 cycles */
  static char state = 0;
  switch(state){            /* Switch with only 2 states */
  case 0:                   /* Going up with red led */
    buzzer_set_period(cyc); /* Set buzzer with current cycle value */
    cyc=cyc-20;            /* Decrement cycle by 180 = 1/20 steps towards 400(5000Hz) */
    if(cyc==580){           /* When limit is reached we set cycle to 400 and move to next state */
      cyc=600;
      state++;
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

void led_switch(int note){
  if(note==0){
    red_on=0;
    green_on=0;
  }
  else if(note % 2==0){
    red_on=0;
    green_on=1;
  }
  else if(note % 2==1){
    red_on=1;
    green_on=0;
  }
  led_changed=1;
  led_update();
}

void led_off()
{
  red_on=0;
  green_on=0;
  buzzer_set_period(0);
}

void state_advance()		
{
  static char cState=0;
  static char sState=0;
  if(bState==0){
    dim_rg_led();
  }
  else if(bState==1){
    if(cState==25){
      chona();
      cState=0;
    }
    cState++;
  }
  else if(bState==2){
    if(sState==10){
      siren();
      sState=0;
    }
    sState++;
    alternate_led();
  }
  else if(bState==3){
    led_off();
  }
}
