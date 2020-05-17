
#ifndef IDT_H
#define IDT_H

#include <types.h>

void loadexceptions();
void loadidt();
void addint(int number, void (*handler)(), dword dpl);

#endif
