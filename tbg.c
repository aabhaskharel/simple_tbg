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
void points(WINDOW *win);

int score = 0;
int main(int argc, char *argv[])
{
    int x = 1, y = 18;
    int max_y = 0, max_x = 0;
    int input, steps = 0, check = 0;
    time_t t;
    t = time(NULL);

    initscr();
    cbreak();
    noecho();
    clear();
    curs_set(FALSE);

    //main box
    WINDOW *win = newwin(21, 40, 20,80);
    refresh();
    box(win, 0, 0);
    draw(win);
    mvwhline(win, 19, 1, '-', 38);

    //for keyborad inputs
    keypad(win, true);

    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);

    do
    {   
        wattron(win, A_BOLD);
        mvwprintw(win, 20, 3, "SCORE: %d", score);
        mvwprintw(win, 20, 28, "STEPS: %d", steps);
        
        wattron(win,COLOR_PAIR(1));
        mvwprintw(win, y, x, "0"); //player
        wattroff(win,COLOR_PAIR(1));

        wattron(win,COLOR_PAIR(2));
        points(win); //add points
        wattroff(win,COLOR_PAIR(2));
        wattroff(win, A_BOLD);
        wrefresh(win);

        input = wgetch(win);

        switch (input)
        {
        case KEY_UP:
            if ((y > 1) && test_border(win, y - 1, x))
            {
                mvwaddch(win, y, x, ' ');
                y--;
                steps++;
            }
            break;
        case KEY_DOWN:
            if ((y < 18) && test_border(win, y + 1, x))
            {
                mvwaddch(win, y, x, ' ');
                y++;
                steps++;
            }
            break;
        case KEY_RIGHT:
            if ((x < 38) && test_border(win, y, x + 1))
            {
                mvwaddch(win, y, x, ' ');
                x++;
                steps++;
            }
            break;
        case KEY_LEFT:
            if ((x > 1) && test_border(win, y, x - 1))
            {
                mvwaddch(win, y, x, ' ');
                x--;
                steps++;
            }
            break;
        }
    } while (input != 'q');

    endwin();
    return 0;
}

//to avoid border and check points
int test_border(WINDOW *win, int y, int x)
{
    int look;
    look = mvwinch(win, y, x);
    while(look!='#')
    {
        if (look == ' ')
            return 1;
        else
        {
            score++;
            return 1;
        }
    }
    return 0;
}

//to draw outline
void draw(WINDOW *win)
{
    int x, y;
    for (x = 1; x < 40; x += 5)
    {
        for (y = 2; y < 18; y++)
        {
            mvwhline(win, y, x, BLOCK, 3);
        }
    }

    mvwhline(win, 5, 4, BLOCK, 5);
    mvwhline(win, 10, 12, BLOCK, 5);
    mvwhline(win, 13, 4, BLOCK, 2);
    mvwhline(win, 2, 20, BLOCK, 5);
    mvwhline(win, 9, 6, ' ', 3);
    mvwhline(win, 4, 11, ' ', 3);
    mvwhline(win, 16, 34, BLOCK,2);
    mvwhline(win, 2, 9, BLOCK, 2);
    mvwhline(win, 11, 16, ' ', 3);
}

//to insert points
void points(WINDOW *win)
{
    //if (check == 1)
    //{
        int y = 0, x = 0;
       // do
        //{
            srand(time(NULL));
            y = (rand() % 15) + 1;
            x = (rand() % 37) + 1;
            if (mvwinch(win, y, x) == ' ')
                mvwaddch(win, y, x, '*');
        //} while (mvwinch(win, y, x) != '*');
    //}
}