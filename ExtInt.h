#ifndef EXT_INT_H
#define EXT_INT_H

#include <stdint.h>

extern volatile uint16_t knap_taeller;
extern volatile uint8_t opdater_knap_visninger;

void start_ext_int0(void);

#endif