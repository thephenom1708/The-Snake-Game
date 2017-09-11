#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <time.h>

#define h 20
#define w 20
#define area 400
using namespace std;

void display();
void init();
void move(int x1, int y1);
void update();
void control(char key);
void getfruit();
char posvalue(int value);

int a[area];
int sx;
int sy;
int dir=0;
int fruit=2;
bool gameon;

void init()
{
    sx = w / 2;
    sy = h / 2;
    a[sx + sy * w] = 1;

    for (int x = 0; x < w; x++)
    {
        a[x] = -1;
        a[x + (h - 1) * w] = -1;
    }

    for (int y = 0; y < h; y++)
    {
        a[0 + y * w] = -1;
        a[(w - 1) + y * w] = -1;
    }
    getfruit();
}

void control(char key)
{
    switch (key)
    {
    case 'w':
        if (dir != 2)
            dir = 0;
        break;
    case 'd':
        if (dir != 3)
            dir = 1;
        break;
    case 's':
        if (dir != 4)
             dir = 2;
        break;
    case 'a':
        if (dir != 5)
            dir = 3;
        break;
    }
}

void update()
{
    switch (dir)
    {
        case 0: move(-1, 0);
                break;
        case 1: move(0, 1);
                break;
        case 2: move(1, 0);
                break;
        case 3: move(0, -1);
                break;
    }
    for (int i = 0; i < area; i++)
    {
        if (a[i] > 0)
            a[i]--;
    }
}

void move(int x1, int y1)
 {
    int newx = sx + x1;
    int newy = sy + y1;
    if(a[newx + newy * w] == -2)
    {
        fruit++;
        getfruit();
    }
    else if(a[newx + newy * w] != 0)
    {
        gameon = false;
    }
    sx = newx;
    sy = newy;
    a[sx + sy * w] = fruit + 1;
}

void getfruit()
{
    srand(time(0));
    int x = 0;
    int y = 0;
    do
    {
        x = rand() % (w - 2) + 1;
        y = rand() % (h - 2) + 1;
    } while (a[x + y * w] != 0);

    a[x + y * w] = -2;
}

void display()
{
    for (int x = 0; x < w; x++)
    {
        cout<<"\t\t\t\t  ";
        for (int y = 0; y < h; y++)
        {
            cout << posvalue(a[x + y * w]);
        }
        cout<<endl;
    }
    cout<<"score: "<<fruit;
}

char posvalue(int val)
{

    if (val > 0)
        return '@';

    switch (val)
    {
    case -1: return 'X';
    case -2: return '*';
    }
}

int main()
{
    init();
    gameon = true;
    int x=400;
    int prevfruit;
    while(gameon==true)
    {
        prevfruit=fruit;
        if(_kbhit())
        {
            control(getch());
        }
        update();
        system("cls");
        display();
        if(fruit!=prevfruit && x>=60)
            x=x-20;
        _sleep(x);
    }
    cout <<endl<< "\t\t\t!!!GAMEOVER!!!" << endl << "\t\t\t FINAL SCORE: " << fruit<<endl;
    return 0;
}
