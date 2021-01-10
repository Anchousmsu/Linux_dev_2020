#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	bindtextdomain("guessnumber", LOCALEDIR);
	textdomain("guessnumber");

	printf(_("Think of a number from 1 to 100\n"));
	int begin = 1, end = 100, middle = 50;
	char answer[10];
	while (begin != end)
	{
		printf(_("The number greater than %d?\n"), middle);
		scanf("%s", answer);
		if (!strncmp(answer, _("yes"), 2))
			begin = middle + 1;
		else
			end = middle;
		middle = begin + (end - begin) / 2;
	}
	printf(_("The answer: %d\n"), begin);
	return 0;
}
