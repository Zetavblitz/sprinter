#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_starting_words() {
	int starting_words;
	char buf[1024];

	printf("Enter starting wordcount: ");
	
	if (!fgets(buf, 1024, stdin)) {
		exit(1);
	}

	starting_words = atoi(buf);
	return starting_words;
}


int int_division_rounded(int dividend, int divisor) {
	int remainder = dividend % divisor;
	int result = dividend / divisor;
	return (remainder > divisor / 2) ? result + 1 : result;
}

void get_final_words(int starting_words, int duration) {
	int final_words;
	char buf[1024];

	printf("Enter final wordcount: ");

	if (!fgets(buf, 1024, stdin)) {
		exit(1);
	}

	final_words = atoi(buf);
	int added_words = final_words - starting_words;
	int wpm = int_division_rounded(added_words, duration);

	printf("Added %d words (%d wpm).\n", added_words, wpm);
}


void listen() {
	char* cancel = "cancel";

	char command[24];
	if (fgets(command, 24, stdin)) {
		command[strcspn(command, "\n")] = 0;
		if (strcmp(cancel, command) == 0) {
			exit(0);
		}
	}
}

int main(int argc, char* argv[]) {
	const int default_duration = 15;
	int duration = (argc > 1) ? atoi(argv[1]) : default_duration;
	(duration > 0) ? printf("Sprinting for %d minutes.\n", duration) : printf("Sprint duration must be greater than 0 minutes.\n");
	
	int starting_words = get_starting_words();
	// listen();
	get_final_words(starting_words, duration);
	return 0;
}

