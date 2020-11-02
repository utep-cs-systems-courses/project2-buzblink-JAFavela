#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char switch_state_down, switch_state_changed; /* effectively boolean */
char bState;
static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  //led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  if ((p2val & SW1) == 0) /* button1 pressed */
    bState = 0;
  else if ((p2val & SW2) == 0) /* button2 pressed */
    bState = 1;
  else if ((p2val & SW3) == 0) /* button3 pressed */
    bState = 2;
  else if ((p2val & SW4) == 0) /* button4 pressed */
    bState = 3;
  
}
