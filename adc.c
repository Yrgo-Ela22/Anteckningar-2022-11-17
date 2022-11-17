/********************************************************************************
* adc.h: Inneh�ller funktionalitet f�r AD-omvandling och PWM-generering.
********************************************************************************/
#include "header.h"

/********************************************************************************
* adc_read: L�ser av insignalen p� angiven analog pin och returnerar motsvarande
*           digitala v�rde mellan 0 - 1023.
* 
*           1. Vi v�ljer att anv�nda intern matningssp�nning p� 5 V. Vi v�ljer
*              ocks� vilken analog pin som ska kopplas till AD-omvandlaren.
*
*           2. Vi aktiverar AD-omvandlaren (ADEN = ADC Enable). Sedan startar
*              vi en ny AD-omvandling (ADSC = ADC Start Conversion). Vi anv�nder
*              l�gsta m�jliga frekvens (16M / 128 = 125 kHz) f�r att
*              AD-omvandlaren ska kunna g�ra s� ackurat omvandling som m�jligt,
*              allts� b�sta m�jliga resultat (ADPS[2:0] s�tter denna frekvens).
*
*           3. Vi v�ntar in att AD-omvandlingen blir f�rdig. Detta indikeras
*              via biten ADIF (ADC Interrupt Flag), som d� blir ettst�lld.
*              D�rmed v�ntar vi via en loop tills ADIF blir ettst�lld.
*              Vi v�ntar via en while-sats, som k�r s� l�nge ADIF �r lika med 0.
*              Semikolonet betyder "g�r ingenting" varje varv i while-satsen.
*              Vi hade kunnat anv�nda m�svingar.
*
*           4. Vi �terst�ller ADIF inf�r n�sta omvandling genom att skriva
*              en etta till denna. ADIF nollst�lls d� av h�rdvaran och kommer
*              kunna anv�ndas vid n�sta AD-omvandling.
*
*           5. Resultatet ligger nu i register ADC. Egentligen �r det tv�
*              8-bitars register ADCH och ADCL (ADC High och ADC Low), men
*              detta beh�ver ni bara t�nka p� i assembler, h�r f�r ni alla
*              bitar genom att skriva ADC. Vi returnerar d�rmed inneh�llet
*              fr�n register ADC, vilket �r ett osignerat heltal mellan
*              0 - 1023.
*
*           - pin: Den analoga pin som ska l�sas av.
********************************************************************************/
uint16_t adc_read(const uint8_t pin)
{
   ADMUX = (1 << REFS0) | pin;
   ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
   while ((ADCSRA & (1 << ADIF)) == 0); 
   ADCSRA = (1 << ADIF);
   return ADC;
}

/********************************************************************************
* adc_get_pwm_values: L�ser av angiven analog pin och ber�knar sedan on- och
*                     off-tid f�r PWM-generering via angiven periodtid.
*                     Ber�knade v�rden sparas p� angivna adresser och indikerar
*                     tiden som lysdioden ska vara t�nd respektive sl�ckt.
*
*                     1. Vi ber�knar duty cycle, (hur stor andel av periodtiden 
*                        som lysdioden ska vara t�nd) som ett tal mellan 0 - 1 
*                        genom att dividera avl�st v�rde fr�n potentiometern med 
*                        h�gsta m�jliga v�rde 1023. Vi ber�knar d� hur mycket av 
*                        max som potentiometern har vridits mellan 0 - 100 %,
*                        fast h�r i st�llet som ett tal mellan 0 - 1.
*
*                     2. Vi ber�knar on-tiden, allts� tiden som lysdioden ska
*                        vara t�nd under aktuell PWM-period, som periodtiden 
*                        multiplicerat med ber�knad duty cycle. Som exempel, 
*                        f�r en duty cycle p� 60 % ska on-tiden s�ttas till 
*                        60 % av periodtiden, allts� periodtiden * 0.6.
*
*                     3. Vi ber�knar off-tiden, allts� tiden lysdioden ska vara
*                        sl�ckt under aktuell PWM-period, genom att ber�kna
*                        resterande periodtid, dvs. periodtiden minus on-tiden.
*
*                     - pin          : Den analoga pin A0 - A5 som ska l�sas av.
*                     - pwm_period_us: Periodtid f�r PWM i mikrosekunder.
*                     - pwm_on_us    : Pekare till variabel d�r on-tiden ska
*                                      lagras i mikrosekunder.
*                     - pwm_off_us   : Pekare till variabel d�r off-tiden ska
*                                      lagras i mikrosekunder.
********************************************************************************/
void adc_get_pwm_values(const uint8_t pin,
                        const uint16_t pwm_period_us,
                        uint16_t* pwm_on_us,
                        uint16_t* pwm_off_us)
{
   const double duty_cycle = adc_read(pin) / 1023.0;
   *pwm_on_us = (uint16_t)(pwm_period_us * duty_cycle + 0.5);
   *pwm_off_us = pwm_period_us - *pwm_on_us;
   return;
}

/********************************************************************************
* delay_us: Genererar f�rdr�jning m�tt i mikrosekunder. Detta sker genom
*           uppr�kning till angiven f�rdr�jningstid, d�r 1 us f�rdr�jning
*           genereras varje varv via anrop av funktionen _delay_us fr�n
*           biblioteket util/delay.h
*
*           - delay_time_us: Pekare till f�rdr�jningstiden i mikrosekunder.
********************************************************************************/
void delay_us(const volatile uint16_t* delay_time_us)
{
   for (uint16_t i = 0; i < *delay_time_us; ++i)
   {
      _delay_us(1);
   }

   return;
}
