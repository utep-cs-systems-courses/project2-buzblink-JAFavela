#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

void dim_rg_led()
{
  static char ledState=0;
  switch(ledState){
  case 0:         /* leds are both off from 0-2 */
    red_on=0;
    green_on=0;
    ledState++;
    break;
  case 3:         /* leds are on at 3 */
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
  case 10:
    red_on=0;
    green_on=1;
    ledState++;
    break;
  case 20:
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
  if(bState==0){
    dim_rg_led();
  }
  else if(bState==1){
    both_led_off();
  }
  else if(bState==2){
    alternate_led();
  }
  else if(bState==3){
    no_dim();
  }
}
