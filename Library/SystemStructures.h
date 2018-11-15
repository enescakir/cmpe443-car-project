#ifndef SYSTEM_STRUCTURES_H
#define SYSTEM_STRUCTURES_H

//0x00000000 is a dummy value, write the correct address
#define PCONP_ADDRESS	0x400FC0C4
#define PCONP	*((volatile uint32_t*)(PCONP_ADDRESS))

#define PERIPHERAL_CLOCK_FREQUENCY 60000000

#endif
