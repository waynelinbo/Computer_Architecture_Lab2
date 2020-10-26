#include "printer.h"
#include <stdarg.h>

volatile char *tx = (volatile char*) 0x40002000;

////// return floor(a / b) //////
int div(int a, int b){
	int counter = 0;
	while(a>=0){
		a = a-b;
		counter++;
	}
	return counter-1;
}

////// return (a % b) //////
int mod(int a, int b){
	int t = 0;
	while(a>=0){
		t = a;
		a = a-b;
	}
	return t;
}


int self_printf(const char* str, ...){
	va_list ap;
	va_start(ap, str);

	int status = 0;

	char pr[32];
	int index = 0;

	while(*str != '\0'){
		char t = *str;
		if(status == 1){
			switch(t){
				case 's':{
					char *s = va_arg(ap, char*);
					while(*s!='\0')
						*tx = *s++;
					break;
				}
				case 'c':{
					char c = (char)va_arg(ap, int);
					*tx = c;
					break;
				}
				case 'b':{
					int b = va_arg(ap, int);
					while(b!=0){
						pr[index++] = (b&0x1) + '0';
						b = b>>1;
					}
					if(index == 0){
						*tx = '0';
						break;
					}
					while(index > 0)
						*tx = pr[--index];
					break;
				}
				case 'o':{
					int o = va_arg(ap, int);
					while(o!=0){
						pr[index++] = (o&0x7) + '0';
						o = o>>3;
					}
					if(index == 0){
						*tx = '0';
						break;
					}
					while(index > 0)
						*tx = pr[--index];
					break;
				}
				case 'x':{
					int x = va_arg(ap, int);
					int xx = 0;
					while(x!=0){
						xx = (x&0xf);
						if(xx > 9)
							pr[index++] = xx + 87;
						else
							pr[index++] = xx + '0';
						x = x>>4;
					}
					if(index == 0){
						*tx = '0';
						break;
					}
					while(index > 0)
						*tx = pr[--index];
					break;
				}
				case 'X':{
					int X = va_arg(ap, int);
					int XX = 0;
					while(X!=0){
						XX = (X&0xf);
						if(XX > 9)
							pr[index++] = XX + 55;
						else
							pr[index++] = XX + '0';
						X = X>>4;
					}
					if(index == 0){
						*tx = '0';
						break;
					}
					while(index > 0)
						*tx = pr[--index];
					break;
				}
				case 'd':{
					int d = va_arg(ap, int);
					if((d>>31) != 0){
						*tx = '-';
						d = ~(d-1);
					}
					while(d != 0){
						int dd = mod(d, 10);
						d = div(d, 10);
						pr[index++] = dd + '0';
					}
					if(index == 0){
						*tx = '0';
						break;
					}
					while(index>0)
						*tx = pr[--index];
					break;
				}
				default:
					*tx = t;
			}
			status = 0;
			index = 0;
		}
		else{
			if(t != '%')
				*tx = t;
			else
				status = 1;
		}
		str++;
	}
	va_end(ap);

	return 1;
}


