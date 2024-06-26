#pragma once

#include "stdint.h"

#define CEIL_DIV(a, b) (((a + b) - 1) / b)

void memset(void *dest, char val, uint32 count);
void outPortB(uint16 port, uint8 value);
char inPortB(uint16 port);

struct InterruptRegisters
{
    uint32 cr2;
    uint32 ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, csm, eflags, useresp, ss;
};
