/********************************************************************************
* interrupts.c: Innehåller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* ISR(PCINT0_vect): Avbrottsrutin som aktiveras vid logisk förändring på 
*                   tryckknappens pin 13 (PORTB5). Vid nedtryckning så togglas
*                   aktivering av lysdioden via toggling av den globala 
*                   variabeln led1_enabled.
********************************************************************************/
ISR(PCINT0_vect)
{
   if (BUTTON1_IS_PRESSED)
   {
      led1_enabled = !led1_enabled;
   }
   return;
}

