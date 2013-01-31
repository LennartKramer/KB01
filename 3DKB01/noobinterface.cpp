
#include "Kernel.h"


//*** Fields ***


void cleanup();

int main() {

	Kernel kernel = Kernel(false);
	kernel.initialize("level1.llf");
	return 0;
}
