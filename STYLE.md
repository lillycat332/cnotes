# General guideline for code styling in this repo:
These are generally pretty liberal and I'll probably deviate from them often, they're just rough guidelines.
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
* Avoid using statements without braces (They can be difficult to follow, in my opinion.):
```c
/* Do not: */
if (condition)
	...
/* Do: */
if (condition) {
	...
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
Again, these are generally loose and I'm not too bothered about them.