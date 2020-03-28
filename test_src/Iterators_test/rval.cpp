#include <stdlib.h>
#include <stdio.h>
#include <iostream>



int main() {
	int && x = 1;
	int && y = x - 0;

	++x;

	printf("x: %d\ty: %d",x,y);

	return 0;
}
