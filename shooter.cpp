// gametest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <math.h>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <ctime>

#define KEY_UP 1
#define KEY_DOWN -1
#define KEY_LEFT 1
#define KEY_RIGHT -1

using namespace std;

bool gameover = false;
bool shoot = false;

const int width = 24;
const int height = 12;

int x, y, fruitX, fruitY, ghost1X, ghost1Y, ghost2X, ghost2Y, ghost3X, ghost3Y, kflag;
int ghost4X, ghost4Y, ghost5X, ghost5Y, ghost6X, ghost6Y, score = 0;
int StartTiming = 0;
bool ghost1live, ghost2live, ghost3live, ghost4live, ghost5live, ghost6live;

int BulletX, BulletY;
int WayLength = 0;
int ShotsAmount = 0;
int count1 = 0;

bool lastcounter = false;
bool gameover2;

int LabirintArray[26][46] = {};

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN, ULTRA };
eDirection dir;
eDirection BulletDir;
eDirection flag;

int sec = 0;

int mas[26][46] = {};

void SetUp() {
    gameover = 0;
    dir = STOP;
    x = 1;
    y = 1;

    string str;

    srand(static_cast<unsigned int>(time(0)));

    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;

    BulletX = 0;
    BulletY = 0;

    ghost1X = width / 2 + 8;
    ghost1Y = height / 2 + 8;
    ghost1live = true;

    ghost2X = 0;
    ghost2Y = 0;
    ghost2live = true;

    ghost3X = 0;
    ghost3Y = 0;
    ghost3live = true;

    ghost4X = 0;
    ghost4Y = 0;
    ghost4live = true;

    ghost5X = 0;
    ghost5Y = 0;
    ghost5live = true;

    ghost6X = 0;
    ghost6Y = 0;
    ghost6live = true;

    score = 0;

    shoot = false;
    gameover2 = false;
}

void Draw() {
    system("cls");

    char map[26][46] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    };

    if (score == 2)
    {
        ghost2X = width - 3;
        ghost2Y = height - 3;
    }

    if (score == 4)
    {
        ghost3X = width - 2;
        ghost3Y = 23;
    }

    if (score == 4)
    {
        ghost4X = 4;
        ghost4Y = 7;
    }

    if (score == 6)
    {
    spawn1:
        ghost5X = rand() % (width - 2) + 1;
        ghost5Y = rand() % (height - 2) + 1;
        if (map[x][ghost5X] == '#' || mas[ghost5Y][y] == '#') goto spawn1;
    }

    if (score == 8)
    {
    spawn2:
        ghost6X = rand() % (width - 2) + 1;
        ghost6Y = rand() % (height - 2) + 1;
        if (map[x][ghost5X] == '#' || map[ghost5Y][y] == '#') goto spawn2;
    }

    shoot = false;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);

    cout << endl << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << "\t";
        for (int j = 0; j < 46; j++)
        {
            if (i == x && j == y && map[i][j] != '#')
                map[i][j] = '0';
            else if (i == fruitY && j == fruitX && map[i][j] != '#')
                map[i][j] = '$';
            else if (i == BulletX && j == BulletY && map[i][j] != '#')
                map[i][j] = 'o';
            else if (i == ghost1Y && j == ghost1X && map[i][j] != '#' && ghost1live == true)
                map[i][j] = '1';
            else if (i == ghost2Y && j == ghost2X && score > 2 && map[i][j] != '#' && ghost2live == true)
                map[i][j] = '1';
            else if (i == ghost3Y && j == ghost3X && score > 4 && map[i][j] != '#' && ghost3live == true)
                map[i][j] = '1';
            else if (i == ghost4Y && j == ghost4X && score > 4 && map[i][j] != '#' && ghost4live == true)
                map[i][j] = '1';
            else if (i == ghost5Y && j == ghost5X && score > 6 && map[i][j] != '#' && ghost5live == true)
                map[i][j] = '1';
            else if (i == ghost6Y && j == ghost6X && score > 8 && map[i][j] != '#' && ghost6live == true)
            {
                map[i][j] = '1';
                map[i][j + 1] = '1';
                map[i + 1][j] = '1';
                map[i + 1][j + 1] = '1';
            }

            if (map[i][j] == '$')
                SetConsoleTextAttribute(hConsole, 10);
            if (map[i][j] == '#')
                SetConsoleTextAttribute(hConsole, 17);
            if (map[i][j] == '1')
                SetConsoleTextAttribute(hConsole, 12);
            cout << map[i][j];
            SetConsoleTextAttribute(hConsole, 15);
        }
        if (i == 0)
            cout << "\t yout timing " << clock() / 1000;
        if (i == 10)
            cout << "\tyour score is " << score;
        if (i == 11)
            cout << "\tshots amount: " << ShotsAmount;
        cout << endl;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 46; j++)
        {
            if (map[i][j] == '#')
                mas[i][j] = -3;
            else if (map[i][j] == '0')
                mas[i][j] = -1;
            else if (map[i][i] == '1')
                mas[i][j] = -2;
            else
                mas[i][j] = 0;
        }
    }

    /* or (int t = 1; t < 45; t++)
    {
        for (int i = 1; i < 25; i++)
        {
            for (int j = 1; j < 45; j++)
            {
                if (mas[i][j] == 0)
                {
                    if (mas[i - 1][j] == t)
                        mas[i][j] = t + 1;
                    if (mas[i + 1][j] == t)
                        mas[i][j] = t + 1;
                    if (mas[i][j - 1] == t)
                        mas[i][j] = t + 1;
                    if (mas[i][j + 1] == t)
                        mas[i][j] = t + 1;
                }
            }
        }
    }
    WayLength = mas[x][y]; */
}

void Input()
{
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case ' ':
            dir = ULTRA;
            break;
        case 'o':
            if (ShotsAmount > 0)
            {
                shoot = true;
                ShotsAmount--;
                kflag = 1;
                break;
            }
            else break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void Logic()
{
    if (kflag == 1)
    {
        BulletX = x;
        BulletY = y;
    }
    switch (dir)
    {
    case LEFT:
        if (kflag == 1) BulletDir = RIGHT;
        flag = dir;
        y--;
        break;
    case RIGHT:
        if (kflag == 1) BulletDir = LEFT;
        flag = dir;
        y++;
        break;
    case UP:
        if (kflag == 1) BulletDir = DOWN;
        flag = dir;
        x--;
        break;
    case DOWN:
        if (kflag == 1) BulletDir = UP;
        flag = dir;
        x++;
        break;
    case ULTRA:
        switch (flag)
        {
        case LEFT:
            if (kflag == 1) BulletDir = RIGHT;
            y = y - 2;
            break;
        case RIGHT:
            if (kflag == 1) BulletDir = LEFT;
            y = y + 2;
            break;
        case UP:
            if (kflag == 1) BulletDir = DOWN;
            x = x - 2;
            break;
        case DOWN:
            if (kflag == 1) BulletDir = UP;
            x = x + 2;
            break;
        }
        break;
    }

    switch (BulletDir)
    {
    case LEFT:
        BulletY--;
        break;
    case RIGHT:
        BulletY++;
        break;
    case UP:
        BulletX--;
        break;
    case DOWN:
        BulletX++;
        break;
    }

    kflag = 0;


    if (x > 24 || x < 1 || y > 44 || y < 1)
        gameover = true;

    if (y == fruitX && x == fruitY && dir != ULTRA)
    {
        score++;
        ShotsAmount++;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
    }
    else if (y == fruitX && x == fruitY && y + 1 == fruitX && y - 1 == fruitX && x + 1 == fruitY && x - 1 == fruitY && dir == ULTRA)
    {
        score++;
        ShotsAmount;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
    }

    if (BulletX == ghost1Y && BulletY == ghost1X)
    {
        ghost1live = false;
        ghost1X = 0;
        ghost1Y = 0;
    }

    if (BulletX == ghost2Y && BulletY == ghost2X && score > 2)
    {
        ghost2live = false;
        ghost2X = 0;
        ghost2Y = 0;
    }

    if (BulletX == ghost3Y && BulletY == ghost3X && score > 4)
    {
        ghost3live = false;
        ghost3X = 0;
        ghost3Y = 0;
    }

    if (BulletX == ghost4Y && BulletY == ghost4X && score > 4)
    {
        ghost4live = false;
        ghost4X = 0;
        ghost4Y = 0;
    }

    if (BulletX == ghost5Y && BulletY == ghost5X && score > 6)
    {
        ghost5live = false;
        ghost5X = 0;
        ghost5Y = 0;
    }

    if (BulletX == ghost6Y && BulletY == ghost6X && score > 8)
    {
        count1++;
    }
    if (count1 >= 3)
    {
        ghost6live = false;
        ghost6X = 0;
        ghost6Y = 0;
    }

    // first ghost
    if (sec % 3 == 0 && ghost1live == true)
    {
        if (y == ghost1X && x == ghost1Y)
        {
            gameover = true;
        }
        else
        {
            if (y > ghost1X && mas[x][ghost1X + 1] != -3)
            {
                ghost1X++;
                if (mas[x][ghost1X] == -3)
                {
                    ghost1X = ghost1X - 2;
                }
            }
            else if (y == ghost1X)
                ghost1X = ghost1X;
            else if (mas[x][ghost1X - 1] != -3)
            {
                ghost1X--;
                if (mas[x][ghost1X] == -3)
                {
                    ghost1X = ghost1X + 2;
                }
            }

            if (x > ghost1Y && mas[ghost1Y + 1][y] != -3)
            {
                ghost1Y++;
                if (mas[ghost1Y][y] == -3)
                {
                    ghost1Y = ghost1Y - 2;
                }
            }
            else if (x == ghost1Y)
                ghost1Y = ghost1Y;
            else if (mas[ghost1Y - 1][y] != -3)
            {
                ghost1Y--;
                if (mas[ghost1Y][y] == -3)
                {
                    ghost1Y = ghost1Y + 2;
                }
            }
        }
    }
    else
    {
        if (y == ghost1X && x == ghost1Y)
        {
            gameover = true;
        }
    }


    //second ghost
    if (sec % 3 == 0 && score > 2 && ghost2live == true)
    {
        if (y == ghost2X && x == ghost2Y)
        {
            gameover = true;
        }
        else
        {
            if (y > ghost2X)
                ghost2X++;
            else if (y == ghost2X)
                ghost2X = ghost2X;
            else
                ghost2X--;
            if (x > ghost2Y)
                ghost2Y++;
            else if (x == ghost2Y)
                ghost2Y = ghost2Y;
            else
                ghost2Y--;
        }
    }
    else
    {
        if (y == ghost2X && x == ghost2Y)
        {
            gameover = true;
        }
    }


    //third ghost
    if (sec % 3 == 0 && score > 4 && ghost3live == true)
    {
        if (y == ghost3X && x == ghost3Y)
        {
            gameover = true;
        }
        else
        {
            if (y > ghost3X)
                ghost3X++;
            else if (y == ghost3X)
                ghost3X = ghost3X;
            else
                ghost3X--;
            if (x > ghost3Y)
                ghost3Y++;
            else if (x == ghost3Y)
                ghost3Y = ghost3Y;
            else
                ghost3Y--;
        }
    }
    else
    {
        if (y == ghost3X && x == ghost3Y)
        {
            gameover = true;
        }
    }


    //fourth ghost
    if (sec % 3 == 0 && score > 4 && ghost4live == true)
    {
        if (y == ghost4X && x == ghost4Y)
        {
            gameover = true;
        }
        else
        {
            if (y > ghost4X)
                ghost4X++;
            else if (y == ghost4X)
                ghost4X = ghost4X;
            else
                ghost4X--;
            if (x > ghost4Y)
                ghost4Y++;
            else if (x == ghost4Y)
                ghost4Y = ghost4Y;
            else
                ghost4Y--;
        }
    }
    else
    {
        if (y == ghost4X && x == ghost4Y)
        {
            gameover = true;
        }
    }


    //fifth ghost
    if (sec % 2 == 0 && score > 6 && ghost5live == true)
    {
        if (y == ghost5X && x == ghost5Y)
        {
            gameover = true;
        }
        else
        {
            if (y > ghost5X)
                ghost5X++;
            else if (y == ghost5X)
                ghost5X = ghost5X;
            else
                ghost5X--;
            if (x > ghost5Y)
                ghost5Y++;
            else if (x == ghost5Y)
                ghost5Y = ghost5Y;
            else
                ghost5Y--;
        }
    }
    else
    {
        if (y == ghost5X && x == ghost5Y)
        {
            gameover = true;
        }
    }


    //sixth ghost
    if (sec % 2 == 0 && score > 8 && ghost6live == true)
    {
        if (y == ghost6X && x == ghost6Y)
        {
            gameover = true;
        }
        else if (y + 1 == ghost6X && x == ghost6Y) gameover = true;
        else if (y == ghost6X && x + 1 == ghost6Y) gameover = true;
        else if (y + 1 == ghost6X && x + 1 == ghost6Y) gameover = true;
        else
        {
            if (y > ghost6X)
                ghost6X++;
            else if (y == ghost6X)
                ghost6X = ghost6X;
            else
                ghost6X--;
            if (x > ghost6Y)
                ghost6Y++;
            else if (x == ghost6Y)
                ghost6Y = ghost6Y;
            else
                ghost6Y--;
        }
    }
    else
    {
        if (y == ghost6X && x == ghost6Y)
        {
            gameover = true;
        }
    }
    sec++;
    if (sec == 6) sec = 0;
}

void ending()
{
    string input2level;
    if (ghost1live == false && ghost2live == false && ghost3live == false && ghost4live == false && ghost5live == false && ghost6live == false)
    {
        system("cls");

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);

        gameover = true;
        cout << endl << endl << endl << "\t\t\t\tGOOD WORK!!!" << endl;
        cout << "\t\t\t\tyou won<3" << endl << endl;
        Sleep(1200);
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\t\t\t\tbut you won a battle, but NOT the war.." << endl << endl;
        SetConsoleTextAttribute(hConsole, 12);
        cout << "press F to move to the next level ";
        SetConsoleTextAttribute(hConsole, 7);
        
        while (input2level != "f")
            cin >> input2level;

        lastcounter = true;
    }
}


void DrawLab()
{
    system("cls");

    char map[26][46] = {
   ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
   '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#',
   '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
   '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#',
   '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#',
   '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#',
   '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', '#', ' ', ' ', ' ', '#',
   '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#',
   '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#',
   '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#',
   '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#',
   '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
   '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#',
   '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#',
   '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#',
   '#', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#',
   '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#',
   '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#',
   '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
   '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#',
   '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
   '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#',
   '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#',
   '#', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#',
   '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ',
   '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ',
    };
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << "\t";
        for (int j = 0; j < 46; j++)
        {
            if (i == x && j == y && map[i][j] != '#')
            {
                SetConsoleTextAttribute(hConsole, 11);
                map[i][j] = '0';
            }
            cout << map[i][j];
            SetConsoleTextAttribute(hConsole, 15);
        }
        if (i == 0)
            cout << "\tyour timing " << (clock() / 1000) - StartTiming / 1000;
        if (i == 1)
            cout << "\tyou have 120 sec!!";
        cout << endl;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 46; j++)
        {
            if (map[i][j] == ' ')
                LabirintArray[i][j] = 0;
            else if (map[i][j] == '#')
                LabirintArray[i][j] = 1;
        }
    }
}

void Input2()
{
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void LogicLab()
{
    switch (dir)
    {
    case LEFT:
        y--;
        if (LabirintArray[x][y] == 1)
        {
            y++;
            dir = STOP;
        }
        break;
    case RIGHT:
        y++;
        if (LabirintArray[x][y] == 1)
        {
            y--;
            dir = STOP;
        }
        break;
    case UP:
        x--;
        if (LabirintArray[x][y] == 1)
        {
            x++;
            dir = STOP;
        }
        break;
    case DOWN:
        x++;
        if (LabirintArray[x][y] == 1)
        {
            x--;
            dir = STOP;
        }
        break;
    }
}

void happyending()
{
    system("cls");
    for (int i = 0; i < 4; i++)
        cout << endl;
    cout << "\t\t\tGONGRATULATIONS!" << endl;
    cout << "\t\t\tyou got out of the cave";
}

void Level2()
{
    StartTiming = clock();

    x = 1;
    y = 1;

    dir = STOP;

    while (!gameover2) {
        DrawLab();
        Input2();
        LogicLab();
        Sleep(250);
        if ((clock() / 1000) - StartTiming / 1000 > 120)
            gameover2 = true;
        if ((x == 26 && y == 46) || (x == 65 && y == 45) || (x == 26 && y == 44) || (x == 25 && y == 46))
        {
            happyending();
            gameover2 = true;
        }
    }
}




int main()
{
    cout << endl << "\tYou are locked up in ancient cave...." << endl;
    cout << "\tYou have to collect all $ in order to escape." << endl;
    cout << "\tMany different monsters live here, so be carefull, stranger." << endl;
    cout << "\tYou have to kill ALL OF THEM to stay alive." << endl;
    cout << endl << "\tAnd now..RUN!\tYour time starts NOW!" << "\t\t" << "00.00" << endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);

    string inputF;
    while (inputF != "f")
    {
        cout << endl << "Press F to start ";
        cin >> inputF;
    }

    system("cls");

    inputF = "0";
    SetConsoleTextAttribute(hConsole, 7);
    cout << endl << "\t\t\tINSTRUCTIONS" << endl << endl;
    cout << "\tpress W A S D to move" << endl;
    cout << "\tpress O to shoot" << endl;
    cout << "\tpress SPACE for ultra speed" << endl << endl;
    cout << "\tYou have 2 minutes!" << endl;
    cout << "\tunderstand ?" << endl;

    SetConsoleTextAttribute(hConsole, 12);
    while (inputF != "f")
    {
        cout << endl << "Press F to start ";
        cin >> inputF;
    }
    Sleep(300);
    system("cls");

    for (int i = 3; i > 0; i--)
    {
        cout << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t" << i;
        for (int j = i; j < 3; j++)
            cout << "!";
        Sleep(1000);
        system("cls");
    }
    cout << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t" << "START!!!";
    Sleep(1500);

    system("cls");

    SetConsoleTextAttribute(hConsole, 15);
    SetUp();
    while (!gameover) {
        Draw();
        Input();
        Logic();
        ending();
        Sleep(250);
        if (clock() / 1000 > 120)
            gameover = true;
        if (gameover == true)
        {
            Sleep(100);
        }
    }

    if (lastcounter == false)
    {
        system("cls");
        float timing, minutes;
        timing = clock() / 1000.0;
        minutes = timing / 60.0;

        char map[26][46] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        };

        cout << endl << endl;

        int TimeEnd = clock() % 1000;
        bool painting = true;
        int p = 0;
        while (painting == true)
        {
            system("cls");
            for (int i = 0; i < 26; i++)
            {
                cout << "\t";

                    SetConsoleTextAttribute(hConsole, 12);
                    for (int t = 0; t < p; t++)
                    {
                        for (int g = 0; g < 46; g++)
                            map[t][g] = '#';
                    }

                    // y
                    map[8][10] = ' ';
                    map[9][10] = ' ';
                    map[10][10] = ' ';
                    map[10][11] = ' ';
                    map[10][12] = ' ';
                    map[10][13] = ' ';
                    map[9][13] = ' ';
                    map[8][13] = ' ';
                    map[10][13] = ' ';
                    map[11][13] = ' ';
                    map[12][13] = ' ';
                    map[12][12] = ' ';
                    map[12][11] = ' ';
                    map[12][10] = ' ';

                    //o 
                    map[8][17] = ' ';
                    map[9][17] = ' ';
                    map[10][17] = ' ';
                    map[11][17] = ' ';
                    map[12][17] = ' ';

                    map[12][18] = ' ';
                    map[12][19] = ' ';
                    map[12][20] = ' ';

                    map[8][18] = ' ';
                    map[8][19] = ' ';
                    map[8][20] = ' ';

                    map[8][21] = ' ';
                    map[9][21] = ' ';
                    map[10][21] = ' ';
                    map[11][21] = ' ';
                    map[12][21] = ' ';

                    //u
                    map[8][25] = ' ';
                    map[9][25] = ' ';
                    map[10][25] = ' ';
                    map[11][25] = ' ';
                    map[12][25] = ' ';

                    map[12][26] = ' ';
                    map[12][27] = ' ';
                    map[12][28] = ' ';

                    map[8][29] = ' ';
                    map[9][29] = ' ';
                    map[10][29] = ' ';
                    map[11][29] = ' ';
                    map[12][29] = ' ';


                    //d
                    map[15][10] = ' ';
                    map[16][10] = ' ';
                    map[17][10] = ' ';
                    map[18][10] = ' ';
                    map[19][10] = ' ';

                    map[15][11] = ' ';
                    map[15][12] = ' ';
                    map[15][13] = ' ';
                    map[16][14] = ' ';
                    map[17][14] = ' ';
                    map[18][14] = ' ';
                    map[18][13] = ' ';
                    map[19][11] = ' ';
                    map[19][12] = ' ';
                    map[19][13] = ' ';

                    //i
                    map[15][17] = ' ';
                    map[17][17] = ' ';
                    map[18][17] = ' ';
                    map[19][17] = ' ';

                    //e
                    map[15][21] = ' ';
                    map[15][22] = ' ';
                    map[15][23] = ' ';
                    map[15][24] = ' ';

                    map[16][21] = ' ';

                    map[17][21] = ' ';
                    map[17][22] = ' ';
                    map[17][23] = ' ';
                    map[17][24] = ' ';

                    map[18][21] = ' ';

                    map[19][21] = ' ';
                    map[19][22] = ' ';
                    map[19][23] = ' ';
                    map[19][24] = ' ';

                    //d
                    map[15][28] = ' ';
                    map[16][28] = ' ';
                    map[17][28] = ' ';
                    map[18][28] = ' ';
                    map[19][28] = ' ';

                    map[15][29] = ' ';
                    map[15][30] = ' ';
                    map[15][31] = ' ';
                    map[16][32] = ' ';
                    map[17][32] = ' ';
                    map[18][32] = ' ';
                    map[18][31] = ' ';
                    map[19][29] = ' ';
                    map[19][30] = ' ';
                    map[19][31] = ' ';


                for (int j = 0; j < 46; j++)
                {
                    cout << map[i][j];
                }
                cout << endl;
            }
            Sleep(100);
            p++;
            if (p == 27) painting = false;
        }
        cout << endl << endl << endl;
    }
    else
    {
        Level2();
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

