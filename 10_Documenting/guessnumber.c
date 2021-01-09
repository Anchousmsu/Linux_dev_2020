/*! \file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

/*!
\def _(STRING)
\brief macros for translation texts
*/
#define _(STRING) gettext(STRING)

#define HELP _("\
Usage: ./guessnumber [OPTION]\n\
	\n\
	-r			enable roman numbers\n\
	\n\
EXECUTABLE should accept \'--help\' options and produce output on\n\
stdout:\n\
	\n\
	-h, --help		help option string\n\
	")

/*!
\struct RomanTable
\brief struct for for matching numbers
*/
typedef struct
{
	int number; /// arabic number
	char roman[10]; /// roman number
}RomanTable;

/// Table of matching numbers from 1 to 100
RomanTable roman_table[100];


/*!
\brief function for translation from roman number to arabic number
\param[in] roman roman numbers
\return arabic number
*/
int fromRoman(char *roman)
{
	for (int i = 0; i < 100; i++)
	{
		if (!strncmp(roman_table[i].roman, roman, strlen(roman)))
			return roman_table[i].number;
	}
	return -1;
}

/*!
\brief function for translation from arabic number to roman number
\param[in] number arabic numbers
\return roman number
*/
char* toRoman(int number)
{
	if (number > 0 && number <= 100)
		return roman_table[number - 1].roman;
	else
		return "";
}

/*!
\brief function for reading roman table from file
\param[in] name_file file name
*/
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

	if (argc >= 2 && !strncmp(argv[1], "-r", 2))
	{
		flag_roman = 1;
		readRomanTableFile("romantable.txt");
	}
	else if (argc >= 2 && (!strncmp(argv[1], "--help", 6) || !strncmp(argv[1], "-h", 2)))
	{
		return printf("%s\n", HELP);
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
