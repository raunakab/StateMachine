#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main() {
	int && foo(1);
	int * x = &foo;

	return 0;
}
