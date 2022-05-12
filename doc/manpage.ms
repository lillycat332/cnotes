.\"Modified from man(1) of FreeBSD, the NetBSD mdoc.template, and mdoc.samples.
.\"See Also:
.\"man mdoc.samples for a complete listing of options
.\"man mdoc for the short list of editing options
.\"/usr/share/misc/mdoc.template
.Dd 30/3/22               \" DATE
.Dt cnotes 1      \" Program name and manual section number
.Sh NAME                 \" Section Header - required - don't modify
.Nm cnotes

.Nd Simple Note Editor

.Sh DESCRIPTION          \" Section Header - required - don't modify
.Nm
is a simple note taking program. It is 'bring your own text editor' meaning it 
uses a text editor of your choice specified at compile time.
In line with "Unix Philosophy", it provides very few functions of it's own.
It leaves many things up to the user - for example, the text editor. It also gives you 
the ability to use external shell commands.
It 
.Sh COMMANDS
.Nm
has a simple command language. The following describes the command set
available for use in the main "REPL" interface.
.Bl -tag -width -indent  \" Begins a tagged list
.It h
Display help
.It put
Write to disk
.It new 
Create a new note
.It edit
Edit a note
.It exit 
Exit the program
.It ls
List notes
.It ! 
Runs the shell command following. For example, !man cnotes would run man cnotes
.El                      \" Ends the list
.Pp
.\" .Sh ENVIRONMENT      \" May not be needed
.\" .Bl -tag -width "ENV_VAR_1" -indent \" ENV_VAR_1 is width of the string ENV_VAR_1
.\" .It Ev ENV_VAR_1
.\" Description of ENV_VAR_1
.\" .It Ev ENV_VAR_2
.\" Description of ENV_VAR_2
.\" .El
.Sh FILES                \" File used or created by the topic of the man page
.Bl -tag -width "/Users/joeuser/Library/really_long_file_name" -compact
.It Pa $HOME/.cnotes
Contains all notes.
.It Pa $SRC/src/config.h
Config file for compile time options.
.El                      \" Ends the list
.\" .Sh DIAGNOSTICS       \" May not be needed
.\" .Bl -diag
.\" .It Diagnostic Tag
.\" Diagnostic informtion here.
.\" .It Diagnostic Tag
.\" Diagnostic informtion here.
.\" .El
.Sh SEE ALSO
.\" List links in ascending order by section, alphabetically within a section.
.\" Please do not reference files that do not exist without filing a bug report
.Xr ed 1 ,
.Xr vi 1 ,
.Xr acme 1 ,
whatever other text editor you use.
.\" .Sh BUGS              \" Document known, unremedied bugs
.\" .Sh HISTORY           \" Document history if command behaves in a unique manner
