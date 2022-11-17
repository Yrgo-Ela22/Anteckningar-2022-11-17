/********************************************************************************
* main.c: Implementering av ett system inneh�llande interrupts och AD-omvandling.
*         En lysdiod ansluten till pin 8 (PORTB0) styrs via PWM-generering, d�r
*         en potentiometer ansluten till analog pin A0 (PORTC0) l�ses av f�r
*         att justera ljusstyrkan. Detta sker d� lysdioden �r aktiverad, annars
*         h�lls lysdioden sl�ckt. 
* 
*         Toggling av lysdioden sker via nedtryckning av en tryckknapp ansluten 
*         till pin 13 (PORTB5). Ett PCI-avbrott anv�nds f�r att vid nedtryckning 
*         toggla aktivering av lysdioden via toggling av den globala variabeln 
*         led1_enabled.
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Initierar mikrodatorn vid start. Om lysdioden �r aktiverad styrs denna
*       med PWM-generering. D� l�ses potentiometern av, d�r PWM-v�rden, allts�
*       on- och off-tid f�r aktuell PWM-period, ber�knas. Dessa v�rden anv�nds
*       f�r att k�ra PWM-generering en period, allts� en blinkning med on- och
*       off-tiden som blinkhastighet.
********************************************************************************/
int main(void)
{
    uint16_t pwm_on_us;  
    uint16_t pwm_off_us; 

    setup();

    while (1)
    {
       if (led1_enabled)
       {
          adc_get_pwm_values(POT1, 1000, &pwm_on_us, &pwm_off_us);

          LED1_ON;
          delay_us(&pwm_on_us);
          LED1_OFF;
          delay_us(&pwm_off_us);
       }
    }

    return 0;
}

