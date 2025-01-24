#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int duration = (argc > 1) ? atoi(argv[1]) : 15;
	(duration > 0) ? printf("Sprinting for %d minutes.\n", duration) : printf("Sprint duration must be greater than 0 minutes.\n");
	return 0;
}

