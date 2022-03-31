/*
 * cnotes is (c) Lilly Cham and contributors, 2022, under the terms of the BSD
 * 2-clause license. You should have recieved a copy of the BSD 2-clause license
 * with this program. If not, a copy is in the Git repository.
 */

/*** includes ***/
#include "config.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif
#include <termios.h>
#include <unistd.h>

/*** defines ***/
#define CTRL_KEY(k) ((k)&0x1f)
#define MAXINPUT 255 /* maximum input size */
#define VERSION "v1.9a"

/*** prototypes ***/
bool startsWith(const char *a, const char *b);
char file[PATH_MAX];
struct termios orig_termios;
int cat(char name[]);
int ls(void);
int printHelp(void);
int parse(char *cmd);
void die(const char *s);
void disableRawMode(void);
void edit(char *name);
void enableRawMode(void);
void repl(void);

/* main function */
int main()
{
	/* set to location of home directory */
	strcat(strcpy(file, getenv("HOME")), "/.cnotes/");
	mkdir(file, 0777);	 /* make .cnotes folder if not present */
	printf("welcome to cnotes (%s)!\ntype h for help.\n", VERSION);
	repl(); /* initialise the repl */
	return 0;
}

/* repl: the main loop of the UI. */
void repl(void)
{
	char input[MAXINPUT];
	for (;;) {
		fputs("notes> ", stdout);
		fgets(input, MAXINPUT, stdin);
		if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')) {
			input[strlen(input) - 1] = '\0';
		}
		parse(input);
	}
}

/* exit displaying error code */
void die(const char *s)
{
	perror(s);
	exit(1);
}

/* cat - read out a file */
int cat(char name[])
{
	FILE *fp;
	char c, path[PATH_MAX];
	strcpy(path, file);
	strcat(path, name);
	/* Open file */
	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("\nCannot open file\n");
		return (1);
	}

	/* Read contents from file */
	c = fgetc(fp);
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(fp);
	}

	fclose(fp);
	return 0;
}

/* ls - list files in dir */
int ls(void)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(file);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return (0);
}

/*
 * edit: a note editor interface
 * calls ed (or whatever other editor ig) to edit the note
 */

void edit(char *name)
{
	char command[PATH_MAX] = EDITOR;
	char path[PATH_MAX];
	strcpy(path, file);
	strcat(path, name);
	FILE *fp;
	fp = fopen(path, "rb+");
	if (fp == NULL) { // if the file does not exist, create it
		fp = fopen(path, "wb");
	}
	fclose(fp);
	strcat(command, path);
	system(command);
}

/* parse: parse a command, return 0 for success, 1 for parse failure */
int parse(char *cmd)
{
	/* basically a switch case */
	if (strcmp(cmd, "new") == 0) {
		char filename[MAXINPUT];
		scanf("%s", filename);
		edit(filename);
		return 0;
	}

	else if (strcmp(cmd, "put") == 0) {
		printf("not implemented\n");
		return 0;
	}

	else if (strcmp(cmd, "edit") == 0) {
		char filename[MAXINPUT];
		scanf("%s", filename);
		edit(filename);
		return 0;
	}

	else if (strcmp(cmd, "open") == 0) {
		printf("not implemented");
		return 0;
	}

	else if (strcmp(cmd, "cat") == 0) {
		char filename[MAXINPUT];
		scanf("%s", filename);
		cat(filename);
		return 0;
	}

	else if (strcmp(cmd, "ls") == 0) {
		ls();
		return 0;
	}

	else if (strcmp(cmd, "h") == 0 || strcmp(cmd, "help") == 0) {
		printf("commands:\
		\nh - display help\
		\nput - write to disk\
		\nnew - create a new note\
		\nedit - edit a note\
		\nexit - exit without saving\
		\nls - list notes\
		\n! - runs the shell command following\
		\nfor more help, see manpage\n");
		return 0;
	}

	else if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "q") == 0 ||
					 strcmp(cmd, "quit") == 0) {
		exit(0);
		return 0;
	}

	else if (startsWith(cmd, "!")) {
		char *chopped = cmd + 1;
		system(chopped);
		return (0);
	}

	else {
		printf("invalid command, type h for help\n");
		return 1;
	}
}

/* enableRawMode switches us into terminal "raw mode" */
void enableRawMode(void)
{
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

/* disableRawMode - turn off raw mode */
void disableRawMode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
		die("tcsetattr");
	}
}

/* startsWith = Check if string starts with b */
bool startsWith(const char *a, const char *b)
{
	if (strncmp(a, b, strlen(b)) == 0) {
		return 1;
	}
	return 0;
}

int printHelp(void)
{
	printf("commands:\
		\nh - display help\
		\nput - write to disk\
		\nnew - create a new note\
		\nedit - edit a note\
		\nexit - exit without saving\
		\nls - list notes\
		\n! - runs the shell command following\
		\nfor more help, see manpage\
		\nproject URL:\
		\nhttps://github.com/lillycat332/cnotes\
		\n");

	return 0;
}
