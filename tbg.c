#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PAUSE 50000
#define BLOCK '#'



void draw(WINDOW *win);

int test_border(WINDOW *win, int x1, int y1);

int main(int argc, char *argv[])
{
    int x = 1, y = 18;
    int max_y = 0, max_x = 0;
    int input, score = 0, timer = 0;
    time_t t;
    t = time(NULL);

    initscr();
    cbreak();
    noecho();
    clear();
    curs_set(FALSE);

    //main box
    WINDOW *win = newwin(21, 40, 0, 0);
    refresh();
    box(win, 0, 0);
    draw(win);
    mvwhline(win, 19, 1, '-', 38);
    //wrefresh(win);

    //for keyborad inputs
    keypad(win, true);

    do
    {
        mvwprintw(win, 20, 3, "SCORE: %d", score);
        mvwprintw(win, 20, 28, "TIMER: %d", timer);

        //color support
        start_color();

        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvwprintw(win, y, x, "0");
        attroff(COLOR_PAIR(1));
        refresh();
        wrefresh(win);

        input = wgetch(win);

        switch (input)
        {
        case KEY_UP:
            if ((y > 0) && test_border(win, y - 1, x))
            {
                mvwaddch(win, y, x, ' ');
                y--;
            }
            break;
        case KEY_DOWN:
            if ((y < 18) && test_border(win, y + 1, x))
            {
                mvwaddch(win, y, x, ' ');
                y++;
            }
            break;
        case KEY_RIGHT:
            if ((x < 39) && test_border(win, y, x + 1))
            {
                mvwaddch(win, y, x, ' ');
                x++;
                score++;
            }
            break;
        case KEY_LEFT:
            if ((x > 0) && test_border(win, y, x - 1))
            {
                mvwaddch(win, y, x, ' ');
                x--;
            }
            break;
        }
    } while (input != 'q');

    endwin();
    return 0;
}

//to avoid border and objects
int test_border(WINDOW *win, int y, int x)
{
    int check;
    check = mvwinch(win, y, x);
    return (check == ' ');
}

//drawing
void draw(WINDOW *win)
{
    int x, y;
    for (x = 1; x < 40; x += 5)
    {
        for (y = 2; y < 17; y++)
        {
            mvwhline(win, y, x, BLOCK, 3);
        }
    }

    mvwhline(win, 5, 4, BLOCK, 5);
    mvwhline(win, 10, 12, BLOCK, 5);
    mvwhline(win, 13, 4, BLOCK, 2);
    mvwhline(win, 2, 20, BLOCK, 5);
}