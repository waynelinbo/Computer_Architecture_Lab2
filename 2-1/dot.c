#include <stdio.h>

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

int _start(){
	volatile char *tx = (volatile char*) 0x40002000;
	char *str1 = "The inner product of two vectors is ";

    int a[3] = {-1, -2, 3};
    int b[3] = {4, -5, -6};
	int length = 3;

	int t = 0;
    int sum = 0;
    for (int i = 0; i < length; i++){
        sum += a[i] * b[i];
    }

//------------    print    ------------//

////// print a[] //////
	*tx = 'a';
	*tx = ':';
	for(int i = 0; i<length ; i++){
		if((a[i]>>31) != 0){
			*tx = '-';
			t = ~(a[i]-1);
		}
		else
			t = a[i];
		*tx = t + '0';
		*tx = ' ';
	}
	*tx = '\n';

////// print b[] //////
	*tx = 'b';
	*tx = ':';
	for(int i = 0; i<length ; i++){
		if((b[i]>>31) != 0){
			*tx = '-';
			t = ~(b[i]-1);
		}
		else
			t = b[i];

		*tx = t + '0';
		*tx = ' ';
	}
	*tx = '\n';

////// print str1 //////
	while(*str1!='\0')
		*tx = *str1++;

////// print sum //////
	char ans[10];
	int index = 0; 
	int s = sum;
	
	if((s>>31) != 0){
	   *tx = '-';
	   s = ~(s-1);
	}

	while(s != 0){
		t = mod(s, 10);
		s = div(s, 10);
		ans[index++] = t + '0';
	}

	while(index>0)
		*tx = ans[--index];
		
	*tx = '\n';

    return 0;
}
