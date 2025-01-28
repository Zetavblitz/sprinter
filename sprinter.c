#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct timer {
	double duration;
	double start_time;
	double extra_time;
	int paused;
};


void set_timer(struct timer* t, int minutes) {
	(*t).duration = 60.0 * (double) minutes;
}


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


// TODO: Make these commands fully functional (necessitates implementation of a timer)
void listen(int duration) {
	char* cancel = "cancel";
	char* pause = "pause";
	char* start = "start";
	char* stop = "stop";
	char* time = "time";
	char command[24];
	if (fgets(command, 24, stdin)) {
		command[strcspn(command, "\n")] = 0;
		if (strcmp(cancel, command) == 0) {
			exit(0);
		} else if (strcmp(pause, command) == 0) {
			printf("Haven't done time yet, so it's always paused I guess...\n");
		} else if (strcmp(start, command) == 0) {
			printf("Starting sprint for %d minutes now!\n", duration);
		} else if (strcmp(stop, command) == 0) {
			printf("Stopping sprint!\n");
			exit(0);
		} else if (strcmp(time, command) == 0) {
			printf("Yeah we haven't implemented time yet...\n");
		} else {
			printf("Command not recognized.\n");
		}
	}
}

int main(int argc, char* argv[]) {
	const int default_duration = 15;
	int duration = (argc > 1) ? atoi(argv[1]) : default_duration;
	(duration > 0) ? printf("Sprinting for %d minutes.\n", duration) : printf("Sprint duration must be greater than 0 minutes.\n");

	struct timer sprint_timer;
	set_timer(&sprint_timer, duration);

	int starting_words = get_starting_words();
	
	listen(duration);

	get_final_words(starting_words, duration);
	return 0;
}

