#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXINPUT 1024
#define VERSION "v1.2b"

/* l: are we in the main loop? */
bool l = true;

/* edit: a note editor interface, roughly akin to sam or ed */

void edit(char name)
{
	(void)0;
}

/* parse: parse a command, return 0 for success, 1 for parse failure */
int parse (char *cmd)
{
	if ((strcmp(cmd, "new")) == 0) {
		printf("not implemented\n");
		return 0;
	}

	else if ((strcmp(cmd, "put")) == 0) {
		printf("not implemented\n");
		return 0;
	}

	else if ((strcmp(cmd, "edit")) == 0) {
		printf("not implemented\n");
		return 0;
	}

	else if ((strcmp(cmd, "ls")) == 0) {
		printf("not implemented\n");
		return 0;
	}

	else if ((strcmp(cmd, "h")) == 0) {
		printf("commands:\nh - display help\nput - write to disk\n\nnew - create a new note\nedit - edit a note\nexit - exit without saving\nls - list notes\nfor more help, see manpage\n");
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
	printf("welcome to cnotes (%s)!\ntype h for help.\n", VERSION);
	repl();
	return 0;
}