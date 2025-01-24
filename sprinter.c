#include <stdio.h>
#include <stdlib.h>

// TODO: refactor to have main at the bottom of the file.
int main(int argc, char* argv[]) {
	const int default_duration = 15;
	int duration = (argc > 1) ? atoi(argv[1]) : default_duration;
	(duration > 0) ? printf("Sprinting for %d minutes.\n", duration) : printf("Sprint duration must be greater than 0 minutes.\n");
	
	int starting_words = get_starting_words();
	get_final_words(starting_words, duration);

	return 0;
}

int get_starting_words() {
	int starting_words;
	printf("Enter starting wordcount:\n");
	scanf("%d", &starting_words);
	return starting_words;
}

void get_final_words(int starting_words, int duration) {
	int final_words;
	printf("Enter final wordcount:\n");
	scanf("%d", &final_words);
	int added_words = final_words - starting_words;
	printf("Added %d words (%d wpm).\n", added_words, int_division_rounded(added_words, duration));
}

int int_division_rounded(int dividend, int divisor) {
	int remainder = dividend % divisor;
	int result = dividend / divisor;
	return (remainder > divisor / 2) ? result + 1 : result;
}

