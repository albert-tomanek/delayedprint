/* Compile: gcc -o delayedprint delayedprint.c */
/* Public Domain */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int delay = 100; // ms
	
	if (argc < 2)
	{
		printf("Syntax:\n\t%s [FILENAME] {-d=delay}\n", argv[0]);
		return 1;
	}
	
	FILE *f = fopen(argv[1], "r");
	
	if (f == NULL)
	{
		fprintf(stderr, "Error opening '%s'.\n", argv[1]);
		return 1;
	}
	
	for (int i = 0; i < argc; i++)
	{
		if (! strncmp(argv[i], "-d=", 3))
		{
			char *c = strchr(argv[i], '=');
			
			if (c != NULL)
			{
				delay = atoi(++c);
			}
		}
	}
	
	for (int c; (c = fgetc(f)) != EOF;)
	{
		putchar((char) c);
		fflush(stdout);
		usleep(delay * 1000);
	}
	
	fclose(f);
	return 0;
}
