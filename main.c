#include <avr/io.h>
#include <avr/interrupt.h>
//Permet de choisir entre MM:SS ou HH:MM
#define CHRONO
#ifndef CHRONO
    #define HH_MM
#endif
// ---- Paramètres du Timer 0 ----
#define F_CPU 16000000UL
// Timer0 prescaler = 64
#define PSCL0 64UL
// Multiplexing frequency
#define F_mux 1000UL
#define MAX_COUNT_T0 ((uint8_t)(((F_CPU / PSCL0) / F_mux) - 1))
#define F_ticks F_mux
// ---- Prototypes de fonctions ----
void setupTimer0(void);
void setupGPIO(void);
void calculAffichage(uint8_t* tableau, uint32_t chrono, uint32_t freq);
// ---- Variables globales ----
uint8_t affichage[4] = {13,14,10,13};
uint32_t ticks = 0;
// Digit actuellement affiché
volatile uint8_t digitCourant = 0;
int main(void)
{
    uint32_t heure;
    setupGPIO();
    setupTimer0();
    sei();
    while(1)
    {
        cli();
        heure = ticks;
        sei();
        // calculAffichage(affichage, heure, F_ticks);
    }
}
void setupTimer0(void)
{
    // Mode CTC
    TCCR0A = (1 << WGM01);
    TCCR0B = 0;
    OCR0A = MAX_COUNT_T0;
    // Interruption Compare Match A
    TIMSK0 |= (1 << OCIE0A);
    // Prescaler = 64
    TCCR0B |= (1 << CS01) | (1 << CS00);
}
void setupGPIO(void)
{
    // Tous les bits de B et C en sortie
    DDRB = 0xFF;
    DDRC = 0xFF;
    PORTB = 0x00;
    PORTC = 0x00;
}
ISR(TIMER0_COMPA_vect)
{
    ticks++;
    // Éteindre tous les digits
    PORTB = 0x00;
    // Envoyer la valeur du digit courant
    PORTC = affichage[digitCourant];
    // Activer le digit correspondant
    switch(digitCourant)
    {
        case 0:
            PORTB = (1 << PB0);
            break;
        case 1:
            PORTB = (1 << PB1);
            break;
        case 2:
            PORTB = (1 << PB2);
            break;
        case 3:
            PORTB = (1 << PB3);
            break;
    }
    digitCourant++;
    if(digitCourant >= 4)
        digitCourant = 0;
}
