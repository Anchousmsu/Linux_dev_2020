#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

typedef struct
{
	int number;
	char roman[10];
}RomanTable;

RomanTable roman_table[100];

int fromRoman(char *roman)
{
	for (int i = 0; i < 100; i++)
	{
		if (!strncmp(roman_table[i].roman, roman, strlen(roman)))
			return roman_table[i].number;
	}
	return -1;
}

char* toRoman(int number)
{
	if (number > 0 && number <= 100)
		return roman_table[number - 1].roman;
	else
		return "";
}

void readRomanTableFile(const char *name_file)
{
	FILE *fp;
	fp = fopen(name_file, "r");
	for (int i = 0; i < 100; i++)
	{
		char buff[25];
		fgets(buff, 25, fp);
		char *ptr = strtok(buff, " ");
		roman_table[i].number = atoi(ptr);
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, "\n");
		int len = strlen(ptr);
		strncpy(roman_table[i].roman, ptr, len);
		roman_table[i].roman[len] = '\0';
	}
	fclose(fp);
}


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	if (getenv("PO_LOCAL"))
		bindtextdomain("guessnumber", ".");
	else
		bindtextdomain("guessnumber", "/usr/share/licale");
	textdomain("guessnumber");

	int flag_roman = 0;

	if (argc == 2 && !strncmp(argv[1], "-r", 2))
	{
		flag_roman = 1;
		readRomanTableFile("romantable.txt");
	}

	if (flag_roman)
		printf(_("Think of a number from %s to %s\n"), toRoman(1), toRoman(100));
	else
		printf(_("Think of a number from 1 to 100\n"));
	int begin = 1, end = 100, middle = 50;
	char answer[10];
	while (begin != end)
	{
		if (flag_roman)
			printf(_("The number greater than %s?\n"), toRoman(middle));
		else
			printf(_("The number greater than %d?\n"), middle);
		scanf("%s", answer);
		if (!strncmp(answer, _("yes"), 2))
			begin = middle + 1;
		else
			end = middle;
		middle = begin + (end - begin) / 2;
	}
	if (flag_roman)
		printf(_("The answer: %s\n"), toRoman(begin));
	else
		printf(_("The answer: %d\n"), begin);
	return 0;
}
