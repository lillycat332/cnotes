#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXINPUT 1024

/* l: are we in the main loop? */
bool l = true;

/* parse: parse a command, return 0 for success, 1 for parse failure */
int parse (char *cmd)
{
	if ((strcmp(cmd, "h")) == 0) {
		printf("commands:\nh - display help\nput - write to disk\nexit - exit without saving\nfor more help, see manpage\n");
		return 0;
	}

	else if ((strcmp(cmd, "exit")) == 0) {
			l = false;
			return 0;
	}

	else {
		printf("invalid command, type h for help\n");
		return 1;
	}

}

/* repl: the main loop of the UI. */
void repl (void)
{
	char input[MAXINPUT];
	while (l) {
		fputs("notes> ", stdout);
		scanf("%s", input);
		parse(input);
	}
}

int main (void)
{
	printf("welcome to cnotes! type h for help\n\n");
	repl();
	return 0;
}