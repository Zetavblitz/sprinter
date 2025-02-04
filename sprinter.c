#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <ctype.h>


int int_division_rounded();
int is_digits();


typedef struct timer timer;


const int BUFFER_SIZE = 1024; // byte length of default stdin buffer
const int DEFAULT_DURATION = 15; // sprint duration in minutes


struct timer {
	int duration;
	int start_time;
	int extra_time; // this is needed because we can pause the timer.
	int paused; // bool
};


// returns 1 if and only if a string contains only digits 0-9
int is_digits(char* s) {
	int result = 1;
	for (int i = 0; i < ((int) strlen(s) - 1); i++) {
		if (!isdigit(s[i])) {
			result = 0;
			break;
		}
	}
	return result;
}


void set_timer(timer* t, int minutes) {
	(*t).duration = minutes * 60;
	(*t).extra_time = 0;
}


void start_timer(timer* t) {
	(*t).start_time = time(NULL);
	(*t).paused = 0;
}


void pause_timer(timer* t) {
	(*t).paused = 1;
	int current_time = time(NULL);
	(*t).extra_time += difftime(current_time, (*t).start_time); // this is necessary to preserve runtime for when we resume it
}


void resume_timer(timer* t) {
	if ((*t).paused) {
		(*t).paused = 0;
		(*t).start_time = time(NULL); // this works because we keep track of previous runtime with the extra_time value
	}
}


// big ternary isn't so scary: paused timer means runtime = extra_time, otherwise we just calc the difference and include that extra_time we saved.
int get_runtime(timer* t) {
	return ((*t).paused) ? (*t).extra_time : (*t).extra_time + difftime(time(NULL), (*t).start_time);
}


// this is for the "time" command the user can use to see how long is left
int get_remaining(timer* t) {
	return int_division_rounded((*t).duration - get_runtime(t), 60);
}


int get_starting_words() {
	int starting_words;
	char buf[BUFFER_SIZE];

	printf("Enter starting wordcount: ");
	
	if (!fgets(buf, BUFFER_SIZE, stdin)) {
		exit(1);
	}

	// make sure to sanitize input
	if (!is_digits(buf)) {
		printf("Not a number.\n");
		exit(1);
	}

	starting_words = atoi(buf);
	return starting_words;
}


// integer division but with weird rounding instead of truncation
int int_division_rounded(int dividend, int divisor) {
	int remainder = dividend % divisor;
	int result = dividend / divisor;
	return (remainder > divisor / 2) ? result + 1 : result;
}


void get_final_words(int starting_words, int duration) {
	int final_words;
	char buf[BUFFER_SIZE];

	printf("Time is up!\nEnter final wordcount: ");

	if (!fgets(buf, BUFFER_SIZE, stdin)) {
		exit(1);
	}
	
	// make sure to sanitize input
	if (!is_digits(buf)) {
		printf("Not a number,\n");
		exit(1);
	}

	final_words = atoi(buf);
	int added_words = final_words - starting_words;
	int wpm = int_division_rounded(added_words, duration);

	printf("Added %d words (%d wpm).\n", added_words, wpm);
}


// main event loop abomination for the majority of program execution
void listen(timer* t) {
	// set up scary async io here
	struct pollfd fds[1];
	int ret;
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	// just available commands
	char* cancel = "cancel";
	char* pause = "pause";
	char* resume = "resume";
	char* stop = "stop";
	char* time = "time";
	char command[BUFFER_SIZE];

	// we need asynchronous io to stop fgets() from blocking the timer timeout, basically
	while (1) {
		ret = poll(fds, 1, 500); // timeout for 1/2 second

		if (ret == -1) {
			perror("poll()");
			exit(EXIT_FAILURE);
		} else if (ret == 0) {
			if (get_runtime(t) >= (*t).duration) {
				break;
			}
		} else { // this is the case where we actually detect stidn input
			if (fds[0].revents & POLLIN) {	
				if (fgets(command, BUFFER_SIZE, stdin)) {
					command[strcspn(command, "\n")] = 0;
					if (strcmp(cancel, command) == 0) {
						exit(0);
					} else if (strcmp(pause, command) == 0) {
						pause_timer(t);
						printf("Sprint paused.\n");
					} else if (strcmp(resume, command) == 0) {
						resume_timer(t);
						printf("Resuming sprint!\n");
					} else if (strcmp(stop, command) == 0) {
						printf("Stopping sprint!\n");
						exit(0);
					} else if (strcmp(time, command) == 0) {
						printf("%d minutes remaining.\n", get_remaining(t));
					} else {
						printf("Command not recognized.\n");
					}
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {
	int duration = DEFAULT_DURATION;

	// optional first argument sets custom sprint duration
	if (argc > 1) {
		if (!is_digits(argv[1])) {
			printf("Not a number.\n");
			exit(1);
		} else {
			duration = atoi(argv[1]);
		}
	}

	// this is obvious and also not checking will cause a funny floating point exception 500ms later.
	if (duration <= 0) {
		printf("Cannot sprint for zero minutes.\n");
		exit(1);
	}
	
	printf("Sprinting for %d minutes.\n", duration);
	timer sprint_timer;
	set_timer(&sprint_timer, duration);

	int starting_words = get_starting_words();
	start_timer(&sprint_timer);

	listen(&sprint_timer); // event loop
	get_final_words(starting_words, duration);

	return 0;
}

