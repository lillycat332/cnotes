# General guideline for code styling in this repo:
* functions should be laid out as follows:
```c
name (args)
{
	...
}
```
* Any further braces within a function should be on the same line as the statement:
```c
while (condition) {
	...
}

if (condition) {
	...
}
```
* Try not to use external libraries and such (especially not GNU ones). cnotes aims for portability across platforms.
* Avoid using statements without braces:
```c
/* Do not: */
if (condition)
	doStuff();
if (other_condition)
	doOtherStuff();
/* Do: */
if (condition) {
	doStuff();
}
```
* Avoid using single-line comments:
```c
//don't do this
/* do this instead */
```
* Use Camel Casing, not snake casing
* Use a space between names and parentheses:
```c
/* like this: */
int main ()
/* not: */
int main()
```