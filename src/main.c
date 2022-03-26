/*
* cnotes is (c) Lilly Cham, 2022.
* You should have recieved a copy of the BSD 2-clause license with this program. If not, a copy is in the Git repository.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)
#define MAXINPUT 1024
#define PATH_MAX 1024
#define VERSION "v1.2a"
#define EDITOR = /bin/ed

struct termios orig_termios;
char file[PATH_MAX];

/* exit displaying error code */
void die(const char *s) {
	perror(s);
	exit(1);
}

/* turn off raw mode */
void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
		die("tcsetattr");
	}
}


/* enableRawMode switches us into terminal "raw mode" */
void enableRawMode (void) {
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
		die("tcgetattr");
	}

	atexit(disableRawMode);
	struct termios raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
		die("tcsetattr");
	}
}

/*
* edit: a note editor interface, roughly akin to sam or ed
* todo: make this work?
*/

void edit(char name[])
{
	char *command[PATH_MAX];
	sprintf(*command, "%s%s", file, name);
	printf("%s",*command);
	system(*command);
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

/* main function */
int main (void)
{
	strcat(strcpy(file, getenv("HOME")), "/.cnotes");		/* set to location of home directory */
	mkdir(file, 0777);										/* make .cnotes folder if not present */
	printf("welcome to cnotes (%s)!\ntype h for help.\n", VERSION);
	repl();
	return 0;
}
