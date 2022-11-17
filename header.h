/********************************************************************************
* header.h: Inneh�ller diverse definitioner och deklarationer f�r implementering
*           av det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens (beh�vs f�r f�rdr�jningsrutiner): */
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>        /* Inneh�ller information om I/O-register s�som PORTB. */
#include <avr/interrupt.h> /* Inneh�ller information om avbrottsvektorer s�som PCINT0_vect. */
#include <util/delay.h>    /* Inneh�ller f�rdr�jningsrutiner s�som _delay_ms. */

/* Makrodefinitioner: */
#define LED1 PORTB0    /* Lysdiod 1 ansluten till pin 8 (PORTB0). */
#define POT1 PORTC0    /* Potentiometer ansluten till analog pin A0 (PORTC0). */
#define BUTTON1 PORTB5 /* Tryckknapp ansluten till pin 13 (PORTB5). */

#define LED1_ON set(PORTB, LED1)  /* T�nder lysdiod 1. */
#define LED1_OFF clr(PORTB, LED1) /* Sl�cker lysdiod 1. */

#define BUTTON1_IS_PRESSED read(PINB, BUTTON1) /* Indikerar nedtryckning av tryckknapp 1. */

/********************************************************************************
* set: Ettst�ller bit i angivet register.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten som ska ettst�llas.
********************************************************************************/
#define set(reg, bit) reg |= (1 << bit)

/********************************************************************************
* clr: Nollst�ller bit i angivet register.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten som ska nollst�llas.
********************************************************************************/
#define clr(reg, bit) reg &= ~(1 << bit)

/********************************************************************************
* read: L�ser av angiven pin och returnerar ifall denna �r h�g eller l�g.
*
*       - reg: Registret som ska l�sas av.
*       - bit: Den bit som ska kontrolleras.
********************************************************************************/
#define read(reg, bit) (reg & (1 << bit))

/* Enumerationer: */
typedef enum { false, true } bool; /* Realiserar datatypen bool, false = 0, true = 1. */

/* Deklarationer av globala variabler: */
extern volatile bool led1_enabled; /* Indikerar ifall lysdioden �r aktiverad eller inte. */

/********************************************************************************
* setup: Initierar mikrodatorns I/O-portar, PCI-avbrott samt AD-omvandlare.
********************************************************************************/
void setup(void);

/********************************************************************************
* adc_read: L�ser av insignalen p� angiven analog pin och returnerar motsvarande 
*           digitala v�rde mellan 0 - 1023.
*
*           - pin: Den analoga pin som ska l�sas av.
********************************************************************************/
uint16_t adc_read(const uint8_t pin);

/********************************************************************************
* adc_get_pwm_values: L�ser av angiven analog pin och ber�knar sedan on- och
*                     off-tid f�r PWM-generering via angiven periodtid.
*                     Ber�knade v�rden sparas p� angivna adresser och indikerar
*                     tiden som lysdioden ska vara t�nd respektive sl�ckt.
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
                        uint16_t* pwm_off_us);

/********************************************************************************
* delay_us: Genererar f�rdr�jning m�tt i mikrosekunder.
*
*           - delay_time_us: Pekare till f�rdr�jningstiden i mikrosekunder.
********************************************************************************/
void delay_us(const volatile uint16_t* delay_time_us);

#endif /* HEADER_H_ */