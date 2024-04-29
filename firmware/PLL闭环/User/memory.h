#ifndef __MEMORY_H
#define __MEMORY_H
#include "userMain.h"

#define START_ADDRESS 0x00

#define MEMORIZE_BYTE(ADDR, DATA)

#define RECALL_BYTE(ADDR)

// cms
#define MEMORIZE_BYTE(ADDR, DATA)

#define RECALL_BYTE(ADDR)

void memorize(unsigned int add, char *p, unsigned char length);
void recall(Memory *memory);

#endif
