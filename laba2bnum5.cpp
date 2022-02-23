// laba2bnum10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

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

void circleRndomising(array <Circle, 10>& circlepush)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 9);

    for (int i = 0; i < circlepush.size(); i++)
    {
        circlepush[i].Ox = dist(gen);
        circlepush[i].Oy = circlepush[i].Ox;
        circlepush[i].R = circlepush[i].Ox;
    }
}

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

void deleteNode(List** head, List* value)
{
    if (*head == 0) // исходный список пуст 
    {
        return;
    }

    List* t = *head;
    if (t->circle.Ox == value->circle.Ox) // исходный список не пуст 
    {
        *head = t->next;
        delete t;
        return;
    }

    List* t1 = t->next;

    while (t1)
    {
        if (t1->circle.Ox == value->circle.Ox)
        {
            t->next = t1->next;
            delete t1;
            return;
        }
        t = t1;
        t1 = t1->next;
    }
}

void remove_multi_values(List **valuehead, List** listhead)
{
    List* ptr = new List;
    ptr = *listhead;
    List* head = ptr;

    List* valueptr = new List;
    valueptr = *valuehead;

    int counter = 0;
    bool deleting = false;
    while (ptr)
    {
        deleting = false;
        while (valueptr)
        {
            //cout << ptr->circle.Ox << " " << valueptr->circle.Ox << endl;
            deleteNode(&head, valueptr);
            valueptr = valueptr->next;
        }
        valueptr = *valuehead;
        ptr = ptr->next;
        counter++;
    } 
    Print(head);
}

void Demo()
{
    array <Circle, 10> circlepush;
    circleRndomising(circlepush);

    List* ptrhead = new List;
    ptrhead->circle.Ox = circlepush[0].Ox;
    ptrhead->circle.Oy = circlepush[0].Oy;
    ptrhead->circle.R = circlepush[0].R;
    ptrhead->next = NULL;

    for (int i = 1; i < 10; i++)
    {
        AddToTheEnd(&ptrhead, circlepush[i]);
    }
    Print(ptrhead);

    List* values = nullptr;

    AddToTheEnd(&values, {3, 3, 3});
    AddToTheEnd(&values, {7, 7, 7});
    AddToTheEnd(&values, {8, 8, 8});

    Print(values);
    remove_multi_values(&values, &ptrhead);

    delete ptrhead;
    delete values;
}

void Interactive()
{
    array <Circle, 10> circlepush;
    circleRndomising(circlepush);

    List* ptrhead = new List;
    ptrhead->circle.Ox = circlepush[0].Ox;
    ptrhead->circle.Oy = circlepush[0].Oy;
    ptrhead->circle.R = circlepush[0].R;
    ptrhead->next = NULL;

    for (int i = 1; i < 10; i++)
    {
        AddToTheEnd(&ptrhead, circlepush[i]);
    }
    Print(ptrhead);

    List* values = nullptr;
    int AmountValues;
    cin >> AmountValues;
    Circle circleadditional;
    for (int i = 0; i < AmountValues; i++)
    {
        cin >> circleadditional.Ox >> circleadditional.Oy >> circleadditional.R;
        AddToTheEnd(&values, circleadditional);
    }

    Print(values);
    remove_multi_values(&values, &ptrhead);

    delete ptrhead;
    delete values;
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
