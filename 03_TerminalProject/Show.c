#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DX 3
#define KILO 1024

int main(int argc, char *argv[]) {
    FILE *infile;
    char *buffer, **lines;
    long size_memory;

    WINDOW *win;
    int c = 0;

    if (argc < 2)
    {
        printf("No file\n");
        return 1;
    }

    infile = fopen(argv[1], "r");
    if(!infile)
        return 1;
    fseek(infile, 0L, SEEK_END);
    size_memory = (ftell(infile));

    fseek(infile, 0L, SEEK_SET);

    buffer = malloc(size_memory*sizeof(char));
    if(!buffer)
        return 1;

    fread(buffer, sizeof(char), size_memory, infile);
    fclose(infile);

    initscr();
    noecho();
    cbreak();
    printw("File: %s, %0.3f Kb", argv[1], (double)size_memory / KILO);
    refresh();

    int num_lines = LINES-2*DX, num_cols = COLS-2*DX;
    win = newwin(num_lines, num_cols, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    int cur_start_file = 0;
    char *split = strtok(buffer,"\n");
    for (int i = 0; i < num_lines && split; i++)
    {
        wprintw(win, " %s\n", split);
        split = strtok(NULL,"\n");
    }
    box(win, 0, 0);
    wrefresh(win);
    while ((c = wgetch(win)) != 27)
    {
        switch(c)
        {
            case KEY_DOWN:
                if (split)
                {
                    wprintw(win, "%s\n", split);
                    box(win, 0, 0);
                    wrefresh(win);
                    split = strtok(NULL,"\n");
                }
                break;
            default:
                break;
        }
    }

    endwin();

    free(buffer);

    return 0;
}
