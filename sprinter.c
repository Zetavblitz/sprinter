#include <stdio.h>
#include <stdlib.h>

// TODO: refactor to have main at the bottom of the file.
int main(int argc, char* argv[]) {
	const int default_duration = 15;
	int duration = (argc > 1) ? atoi(argv[1]) : default_duration;
	(duration > 0) ? printf("Sprinting for %d minutes.\n", duration) : printf("Sprint duration must be greater than 0 minutes.\n");
	
	int starting_words = get_starting_words();
	get_final_words(starting_words);

	return 0;
}

// TODO: dummy method, implement getting user input
int get_starting_words() {
	return 0;
}

// TODO: dummy method, implement getting user input
void get_final_words(int starting_words) {
	int final_words = 10; // TODO: remove dummy magic number
	int added_words = final_words - starting_words;
	printf("Added %d words (%d wpm).\n", added_words, -1); // TODO: remove dummy -1 magic number
}

