# Anteckningar 2022-11-17
Implementering av AD-omvandling och interrupts för PWM-generering på mikrodator ATmega328.
I detta fall styrs ljusstyrkan på en lysdiod via en potentiometer. 
En tryckknapp används för att toggla lysdioden mellan att styras via potentiometern samt vara släckt.

Filen "header.h" innehåller diverse definitioner och deklarationer för implementering av det inbyggda systemet.

Filen "setup.c" innehåller initieringsrutiner för konfiguration av I/O-portar, PCI-avbrott samt AD-omvandlaren.

Filen "adc.c" innehåller funktioner för AD-omvandling och fördröjning samt beräkning av värden för PWM-generering.

Filen "interrupts.c" innehåller en avbrottsrutin för att toggla aktivering av lysdioden.

I filen "main.c" initieras det inbyggda systemet vid start. 
Sedan styrs lysdioden via PWM-generering när denna är aktiverad.

Filen "Ela22 adc2.cproj" utgörs av ovanstående filer sammansatt till ett körbart projekt, som kan öppnas
och köras i Microchip Studio.