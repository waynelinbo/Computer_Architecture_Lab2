#ifndef _PRINTER_
#define _PRINTER_

extern volatile char *tx;

int div(int a, int b);
int mod(int a, int b);
int self_printf(const char* str, ...);

#endif
