/*
* cnotes is (c) Lilly Cham, 2022.
* You should have recieved a copy of the BSD 2-clause license with this program. If not, a copy is in the Git repository.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXINPUT 1024
#define MAXDIR 1024
#define VERSION "v1.2a"
#define EDITOR = /bin/ed

char filedir[MAXDIR];
/*
* edit: a note editor interface, roughly akin to sam or ed
* todo: make this work?
*/

void edit(char name[])
{
	char *command;
	sprintf(command, "%s%s", filedir, name);
	printf("%s",command);
	system(command);
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
		printf("enter filename: ");
		char filename[MAXINPUT];
		scanf("%s", filename);
		edit(filename);
		return 0;
	}

	else if ((strcmp(cmd, "ls")) == 0) {
		printf("not implemented\n");
		return 0;
	}

	else if ((strcmp(cmd, "h")) == 0) {
		printf("commands:\nh - display help\nput - write to disk\nnew - create a new note\nedit - edit a note\nexit - exit without saving\nls - list notes\nfor more help, see manpage\n");
		return 0;
	}

	else if ((strcmp(cmd, "exit")) == 0) {
		exit(0);
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
	for (;;) {
		fputs("notes> ", stdout);
		scanf("%s", input);
		parse(input);
	}
}

int main (void)
{
	char df[8] = "/.cnotes";
	strcpy(filedir, getenv("HOME"));
	strcat(filedir, df);
	printf("welcome to cnotes (%s)!\ntype h for help.\n", VERSION);
	repl();
	return 0;
}