#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <inttypes.h>
#include <string.h>
//#include <unistd.h>

#define MIN_Y  2
enum {LEFT = 1, UP, RIGHT, DOWN, STOP_GAME = KEY_F (10)};
enum {MAX_TAIL_SIZE = 20, START_TAIL_SIZE = 3};
enum {MAX_FOOD_SIZE = 20,FOOD_EXPIRE_SECONDS = 20, SEED_NUMBER = 10};


// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
}control_buttons;

struct control_buttons default_controls[3] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
                                              {     's',    'w',      'a',       'd'},
                                              {     'S',    'W',      'A',       'D'}};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons* controls;
} snake_t;


//Хвост это массив состоящий из координат x,y

typedef struct tail_t
{
    int x;
    int y;
} tail_t;

//добавили еду
struct food
{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

void initFood(struct food f[], size_t size)
{
    struct food init = {0,0,0,0,0};
    for(size_t i = 0; i < size; i++)
        f[i] = init;
}

// Обновить/разместить текущую еду на поле
void putFoodSeed(struct food *fp)
{
    int max_x=0, max_y=0;
    char spoint[2] = {0};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку
    fp->put_time = time(NULL);
    fp->point = 'f';
    fp->enable = 1;
    spoint[0] = fp->point;
    mvprintw(fp->y, fp->x, "%s", spoint);
}

// Размещение еды
void putFood(struct food f[], size_t number_seeds)
{
    for(size_t i = 0; i < number_seeds; i++)
    {
        putFoodSeed(&f[i]);
    }
}

//проверка еды
void refreshFood(struct food f[], int nfood)
{
    for(size_t i=0; i<nfood; i++)
    {
        if( f[i].put_time )
        {
            if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS )
            {
                putFoodSeed(&f[i]);
            }
        }
    }
}

// проверка еды
int haveEat(struct snake_t *head, struct food f[])
{
    for (size_t i = 0; i < MAX_FOOD_SIZE; ++i)
    {
        if ((head->y == f[i].y) && (head->x == f[i].x))
        {
            f[i].enable = 0;
            return 1;
        }
    }
    return 0;
}

//добавили хвост
void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t = {0, 0};
    for(size_t i = 0; i<size; i++)
    {
        t[i] = init_t;
    }
}

//увеличение хвоста
int addTail(struct snake_t *head)
{
    if (head->tsize == MAX_TAIL_SIZE)
        return 1;
    else
    {
        head->tsize++;
        return 0;
    }
}

//добавили голову
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = UP;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size+1;
    head->controls = default_controls;
}

// Движение головы с учетом текущего направления движения
 void go(struct snake_t *head)
{
    char ch = 'Z';
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction)
    {
        case LEFT:
            if(head->x <= 0)
                head->x = max_x;
            mvprintw(head->y, --(head->x), "%c", ch);
        break;
        case RIGHT:
            if(head->x >= max_x)
                head->x = 0;
            mvprintw(head->y, ++(head->x), "%c", ch);
        break;
        case UP:
            if(head->y <= 1)
                head->y = max_y;
            mvprintw(--(head->y), head->x, "%c", ch);
        break;
        case DOWN:
            if(head->y >= max_y)
                head->y = 0;
            mvprintw(++(head->y), head->x, "%c", ch);
        break;
        default:
        break;
    }
    refresh();
}

//проверка корректости перемещения
 int checkDirection(struct snake_t* snake, const int32_t key)
{
    for (int i = 0; i < 3; ++i)
    {
        if ((key == snake->controls[i].down) && (snake->direction != UP))
            return 1;
        else if ((key == snake->controls[i].up) && (snake->direction != DOWN))
            return 1;
        else if ((key == snake->controls[i].right) && (snake->direction != LEFT))
            return 1;
        else if ((key == snake->controls[i].left) && (snake->direction != RIGHT))
            return 1;
    }
    return 0;
}

// управление разными клавишами
void changeDirection(struct snake_t* snake, const int32_t key)
{
    if (checkDirection(snake, key))
    {
        for (int i = 0; i < 3; ++i)
        {
            if (key == snake->controls[i].down)
                   snake->direction = DOWN;
            else if (key == snake->controls[i].up)
                snake->direction = UP;
            else if (key == snake->controls[i].right)
                snake->direction = RIGHT;
            else if (key == snake->controls[i].left)
                snake->direction = LEFT;
        }
    }
}

// Движение хвоста с учетом движения головы
 void goTail(struct snake_t *head)
{
    char ch = '#';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--)
    {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

// Наезд на себя
int isCrush(struct snake_t *head)
{
    for (size_t i = 3; i <= head->tsize - 1; ++i)
    {
        if ((head->tail[i].y == head->y) && (head->tail[i].x == head->x))
            return 1;
    }
    return 0;
}

int main()
{
snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 15,15);
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Откдючаем line buffering
    noecho();             // Отключаем echo() режим при вызове getch
    curs_set(FALSE);      //Отключаем курсор
    mvprintw(0, 0, " Use the KEYS to control. Press 'F10' to EXIT");
    timeout(0);           //Отключаем таймаут после нажатия клавиши в цикле
    initFood(food, MAX_FOOD_SIZE);
    putFood(food, SEED_NUMBER);// Кладем зерна
    int key_pressed = 0;
    while(key_pressed != STOP_GAME)
    {
        key_pressed = getch(); // Считываем клавишу
        go(snake);
        goTail(snake);
        if (haveEat(snake, food))
        {
            if (addTail(snake))
            {
                mvprintw(3, 0, " You winner!");
                while(key_pressed != STOP_GAME)
                {
                    key_pressed = getch();
                }
                break;
            }
        }
        if (isCrush(snake))
        {
            mvprintw(3, 0, " Your Snake is DEAD!");
             while(key_pressed != STOP_GAME)
            {
                key_pressed = getch();
            }
            break;
        }
        timeout(100); // Задержка при отрисовке
        refreshFood(food, SEED_NUMBER);// Обновляем еду
        changeDirection(snake, key_pressed);
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
