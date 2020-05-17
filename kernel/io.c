// IO functions.

#include <sys/io.h>

void outb(unsigned short port, unsigned char value)
{
  asm volatile("outb %0,%1"::"a"(value), "Nd" (port));
}

unsigned char inb(unsigned short port)
{
  unsigned char ret=0;
  asm volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
  return ret;
}
