// laba2bnum8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGSф
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <time.h>
#include <array>
#include <random>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Circle {
    double Ox;
    double Oy;
    double R;
};

struct List {
    Circle circle;
    List* next;
};

void Print(List* head)
{
    List* p = head;
    cout << "Spisok:" << endl;
    int counter = 0;
    while (p)
    {
        cout << "num: " << counter << "\t";
        cout << "X: " << p->circle.Ox << "\t";
        cout << "Y: " << p->circle.Oy << "\t";
        cout << "R: " << p->circle.R << "\n";
        p = p->next;
        counter++;
    }
    cout << endl << endl;
}

void AddToTheEnd(List** u, Circle circleadditional)
{
    List* p = new List;
    p->circle = circleadditional;

    if (*u == 0) // исходный список пуст - вставка в начало
    {
        p->next = 0;
        *u = p;
        return;
    }

    List* t = *u;
    List* t1 = t->next;
    while (t1)
    {
        t = t1;
        t1 = t1->next;
    }
    t->next = p; // добавляем в конец списка
    p->next = 0;
}

List* interleave(List* values1, List* values2, int size1, int size2)
{
    List* res = nullptr;

    cout << "MIN" << min(size1, size2) << endl;

    for (int i = 0; i < 2 * min(size1, size2); i++)
    {
        cout << i << " " << res << endl;
        if (i % 2 == 0)
        {
            AddToTheEnd(&res, values1->circle);
            values1 = values1->next;
        }
        else
        {
            AddToTheEnd(&res, values2->circle);
            values2 = values2->next;
        }
    }
    if (size1 > size2)
    {
        while (values1)
        {
            AddToTheEnd(&res, values1->circle);
            values1 = values1->next;
        }
    }
    else if (size2 > size1)
    {
        while (values2)
        {
            AddToTheEnd(&res, values2->circle);
            values2 = values2->next;
        }
    }
    return res;
}

void Demo()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    List* values1 = nullptr;
    int size1 = 3;
    List* values2 = nullptr;
    int size2 = 5;

    Circle circle1;
    for (int i = 0; i < size1; i++)
    { 
        circle1.Ox = dist(gen);
        circle1.Oy = dist(gen);
        circle1.R = dist(gen);
        AddToTheEnd(&values1, circle1);
    }
    Print(values1);

    Circle circle2;
    for (int i = 0; i < size2; i++)
    {
        circle2.Ox = dist(gen);
        circle2.Oy = dist(gen);
        circle2.R = dist(gen);
        AddToTheEnd(&values2, circle2);
    }
    Print(values2);
    
    List* res = interleave(values1, values2, size1, size2);
    Print(res);

    delete values1;
    delete values2;
}

void Interactive()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    List* values1 = nullptr;
    int size1;
    cout << "enter 1 list size" << endl;
    cin >> size1;

    List* values2 = nullptr;
    int size2;
    cout << "enter 2 list size" << endl;
    cin >> size2;

    Circle circle1;
    for (int i = 0; i < size1; i++)
    {
        printf("1:\nenter X\n");
        cin >> circle1.Ox;
        printf("ener Y\n");
        cin >> circle1.Oy;
        printf("ener Y\n");
        cin >> circle1.R;
        AddToTheEnd(&values1, circle1);
    }
    Print(values1);

    Circle circle2;
    for (int i = 0; i < size2; i++)
    {
        printf("2:\nener X\n");
        cin >> circle2.Ox;
        printf("ener Y\n");
        cin >> circle2.Oy;
        printf("ener Y/n");
        cin >> circle2.R;
        AddToTheEnd(&values2, circle2);
    }
    Print(values2);

    List* res = interleave(values1, values2, size1, size2);
    Print(res);

    delete values1;
    delete values2;
}

int main()
{
    setlocale(LC_ALL, "rus");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int chose_menu;
    cout << "0.Exit" << endl;
    cout << "1.Demo" << endl;
    cout << "2.Interactive\n\n" << endl;
    cin >> chose_menu;

    switch (chose_menu)
    {
    case 0:
        break;
    case 1:
        Demo();
        break;
    case 2:
        Interactive();
        break;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
