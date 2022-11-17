/********************************************************************************
* header.h: Innehåller diverse definitioner och deklarationer för implementering
*           av det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens (behövs för fördröjningsrutiner): */
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>        /* Innehåller information om I/O-register såsom PORTB. */
#include <avr/interrupt.h> /* Innehåller information om avbrottsvektorer såsom PCINT0_vect. */
#include <util/delay.h>    /* Innehåller fördröjningsrutiner såsom _delay_ms. */

/* Makrodefinitioner: */
#define LED1 PORTB0    /* Lysdiod 1 ansluten till pin 8 (PORTB0). */
#define POT1 PORTC0    /* Potentiometer ansluten till analog pin A0 (PORTC0). */
#define BUTTON1 PORTB5 /* Tryckknapp ansluten till pin 13 (PORTB5). */

#define LED1_ON set(PORTB, LED1)  /* Tänder lysdiod 1. */
#define LED1_OFF clr(PORTB, LED1) /* Släcker lysdiod 1. */

#define BUTTON1_IS_PRESSED read(PINB, BUTTON1) /* Indikerar nedtryckning av tryckknapp 1. */

/********************************************************************************
* set: Ettställer bit i angivet register.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten som ska ettställas.
********************************************************************************/
#define set(reg, bit) reg |= (1 << bit)

/********************************************************************************
* clr: Nollställer bit i angivet register.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten som ska nollställas.
********************************************************************************/
#define clr(reg, bit) reg &= ~(1 << bit)

/********************************************************************************
* read: Läser av angiven pin och returnerar ifall denna är hög eller låg.
*
*       - reg: Registret som ska läsas av.
*       - bit: Den bit som ska kontrolleras.
********************************************************************************/
#define read(reg, bit) (reg & (1 << bit))

/* Enumerationer: */
typedef enum { false, true } bool; /* Realiserar datatypen bool, false = 0, true = 1. */

/* Deklarationer av globala variabler: */
extern volatile bool led1_enabled; /* Indikerar ifall lysdioden är aktiverad eller inte. */

/********************************************************************************
* setup: Initierar mikrodatorns I/O-portar, PCI-avbrott samt AD-omvandlare.
********************************************************************************/
void setup(void);

/********************************************************************************
* adc_read: Läser av insignalen på angiven analog pin och returnerar motsvarande 
*           digitala värde mellan 0 - 1023.
*
*           - pin: Den analoga pin som ska läsas av.
********************************************************************************/
uint16_t adc_read(const uint8_t pin);

/********************************************************************************
* adc_get_pwm_values: Läser av angiven analog pin och beräknar sedan on- och
*                     off-tid för PWM-generering via angiven periodtid.
*                     Beräknade värden sparas på angivna adresser och indikerar
*                     tiden som lysdioden ska vara tänd respektive släckt.
*
*                     - pin          : Den analoga pin A0 - A5 som ska läsas av.
*                     - pwm_period_us: Periodtid för PWM i mikrosekunder.
*                     - pwm_on_us    : Pekare till variabel där on-tiden ska 
*                                      lagras i mikrosekunder.
*                     - pwm_off_us   : Pekare till variabel där off-tiden ska
*                                      lagras i mikrosekunder.
********************************************************************************/
void adc_get_pwm_values(const uint8_t pin, 
                        const uint16_t pwm_period_us, 
                        uint16_t* pwm_on_us, 
                        uint16_t* pwm_off_us);

/********************************************************************************
* delay_us: Genererar fördröjning mätt i mikrosekunder.
*
*           - delay_time_us: Pekare till fördröjningstiden i mikrosekunder.
********************************************************************************/
void delay_us(const volatile uint16_t* delay_time_us);

#endif /* HEADER_H_ */