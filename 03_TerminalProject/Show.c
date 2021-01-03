#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define DX 3
#define NUM_LEN 4
#define KILO 1024


int shift_num(int num)
{
    int len = 0;
    while (num > 0)
    {
        num /= 10;
        len++;
    }
    return NUM_LEN - len;
}


char *shift_line(int num)
{
    int len = shift_num(num);
    char *shift = malloc((len + 1) * sizeof(char));
    int i = 0;
    shift[i++] = ' ';
    while (len)
    {
        shift[i++] = ' ';
        len--;
    }
    return shift;
}


char *strtok_new(char * string, char const * delimiter)
{
    static char *source = NULL;
    char *p, *res = 0;
    if (string)
        source = string;
    if(!source)
        return NULL;
    if((p = strpbrk (source, delimiter)) != NULL)
    {
      *p  = 0;
      res = source;
      source = ++p;
    }
    return res;
}


void print_cur_lines(WINDOW *win, char **lines, int first, int last, int left, int right)
{
    for (int i = first; i <= last; i++)
    {
        int n_line = i + 1;
        wprintw(win, "%s%d: %s\n", shift_line(n_line), n_line, lines[i]);
    }
    box(win, 0, 0);
    wrefresh(win);
}


int main(int argc, char *argv[])
{
    FILE *infile;
    char *buffer, **lines;
    long size_memory;

    WINDOW *win;
    int c = 0;
    int first, last, left, right;

    if (argc < 2)
    {
        printf("No file\n");
        return 1;
    }

    // чтение файла
    infile = fopen(argv[1], "r");
    if(!infile)
        return 1;
    fseek(infile, 0L, SEEK_END);
    size_memory = (ftell(infile));

    fseek(infile, 0L, SEEK_SET);

    buffer = malloc(size_memory * sizeof(char));
    if(!buffer)
        return 1;

    fread(buffer, sizeof(char), size_memory, infile);
    fclose(infile);

    // подготовка ncurses
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    printw("File: %s, %0.3f Kb", argv[1], (double)size_memory / KILO);
    refresh();

    int num_lines = LINES-2*DX, num_cols = COLS-2*DX;
    win = newwin(num_lines, num_cols, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    // заполнение массива строк и вывод первых в окно
    first = left = 0;
    last = num_lines - 3;
    right = num_cols - 3;
    char *split = strtok_new(buffer,"\n");
    int size_lines = 2, n_lines = 0;
    wprintw(win, "\n");
    lines = malloc(size_lines * sizeof(char*));
    for (; split; n_lines++)
    {
        if (n_lines >= size_lines)
        {
            size_lines *= 2;
            lines = realloc(lines, size_lines * sizeof(char*));
        }
        lines[n_lines] = split;
        split = strtok_new(NULL,"\n");
        if (n_lines < num_lines - 2)
        {
            int n_line = n_lines + 1;
            wprintw(win, "%s%d: %s\n", shift_line(n_line), n_line, lines[n_lines]);
        }
    }
    n_lines--;
    box(win, 0, 0);
    wrefresh(win);

    // обработка нажатия на клавиши
    while ((c = wgetch(win)) != 27)
    {
        switch(c)
        {
            case KEY_DOWN:
                if (last < n_lines)
                {
                    last++;
                    first++;
                    int n_line = last + 1;
                    wprintw(win, "%s%d: %s\n", shift_line(n_line), n_line, lines[last]);
                    box(win, 0, 0);
                    wrefresh(win);
                }
                break;
            case KEY_UP:
                if (first > 0)
                {
                    first--;
                    last--;
                    print_cur_lines(win, lines, first, last, left, right);
                }
                break;
            default:
                break;
        }
    }

    endwin();

    free(buffer);
    free(lines);

    return 0;
}
