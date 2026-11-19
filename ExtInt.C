#include "ProjectDefines.h"
#include "ExtInt.h"

volatile uint16_t knap_taeller = 0;
volatile uint8_t opdater_knap_visninger = 0;
static uint8_t venter_paa_ned = 1; // 1 = venter på tryk, 0 = venter på slip

void start_ext_int0(void) {
    // 1. Sæt PD2 som input og slå intern pull-up modstand til (5V når knap er sluppet)
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    // 2. Sæt INT0 til nedadgående flanke (ISC01 = 1, ISC00 = 0)
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // 3. Tænd for External Interrupt 0 i EIMSK
    EIMSK |= (1 << INT0);
}

// Kører når der trykkes eller slippes på knappen på PD2
ISR(INT0_vect) {
    if (venter_paa_ned == 1) {
        // Vi fik et gyldigt tryk (nedadgående flanke)!
        knap_taeller++;
        opdater_knap_visninger = 1;
        venter_paa_ned = 0;

        // Skift næste interrupt til opadgående flanke (ISC01 = 1, ISC00 = 1)
        EICRA |= (1 << ISC01) | (1 << ISC00);
    } else {
        // Knappen blev sluppet (opadgående flanke) - tæl IKKE med
        venter_paa_ned = 1;

        // Skift tilbage til nedadgående flanke (ISC01 = 1, ISC00 = 0)
        EICRA |= (1 << ISC01);
        EICRA &= ~(1 << ISC00);
    }
}