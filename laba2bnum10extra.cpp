// laba2bnum10extra.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
    List* prev;
    List* next;
};

int getSize(List* head)
{
    int counter = 0;
    while (head)
    {
        head = head->next;
        counter++;
    }
    return counter;
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

void PrintBack(List *head, List* end)
{
    int listSize = getSize(head);

    List* p = end;
    cout << "Spisok backwards:" << endl;
    int counter = 0;
    while (p)
    {
        cout << "num: " << listSize - counter - 1 << "\t";
        cout << "X: " << p->circle.Ox << "\t";
        cout << "Y: " << p->circle.Oy << "\t";
        cout << "R: " << p->circle.R << "\n";
        p = p->prev;
        counter++;
    }
    cout << endl << endl;
}

void AddToTheEnd(List** Begin, List** End, Circle circleadditional)
{
    if (*Begin == nullptr && *End == nullptr) {
        List* t = new List;
        t->circle = circleadditional;
        t->prev = NULL;
        t->next = NULL;
        *Begin = t;
        *End = t;
    }
    else {
        (*End)->next = new List;
        (*End)->next->prev = (*End);
        (*End) = (*End)->next;
        (*End)->circle = circleadditional;
        (*End)->next = NULL;
    }
}

List* reverse(List** Begin, List** End, int index1, int index2)
{
    int counter = 0;
    cout << "index1: " << index1 << endl;
    cout << "idnex2: " << index2 << endl << endl << endl;
    List* flag = *Begin;

    bool corrected = false;
    List* BeginNew = NULL;
    List* EndNew = NULL;
    int IndexDifference = 0;
    while (flag)
    {
        corrected = false;
        IndexDifference = 0;
        cout << "index: " << counter << "\t" << flag->circle.Ox << "\n";
        if (counter < index1 || counter > index2)
        {
            AddToTheEnd(&BeginNew, &EndNew, flag->circle);
            cout << "the same: " << flag->circle.Ox << " " << flag->circle.Oy << " " << flag->circle.R << endl;
        }
        else
        {
            corrected = true;
            cout << "not the same" << endl;
            while (IndexDifference < abs(index2 - index1))
            {
                flag = flag->next;
                IndexDifference++;
            }
            IndexDifference = -1;
            while (IndexDifference < abs(index2 - index1))
            {
                AddToTheEnd(&BeginNew, &EndNew, flag->circle);
                flag = flag->prev;
                IndexDifference++;
            }
            flag = flag->next;
            IndexDifference = 0;
            while (IndexDifference < abs(index2 - index1))
            {
                flag = flag->next;
                IndexDifference++;
                counter++;

                cout << "index: " << counter << "\t" << flag->circle.Ox << "\n";
                cout << "not the same" << endl;
            }
        }
        flag = flag->next;
        counter++;
    }
    return BeginNew;
}

void Demo()
{
    List* Begin = NULL;
    List* End = NULL;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    Circle circle;
    int size = 10;
    for (int i = 0; i < size; i++)
    {
        circle.Ox = dist(gen);
        circle.Oy = dist(gen);
        circle.R = dist(gen);
        AddToTheEnd(&Begin, &End, circle);
    }

    Print(Begin);
    cout << endl << endl;
    PrintBack(Begin, End);

    int index1 = 3, index2 = 7;
    List *NewBegin = reverse(&Begin, &End, index1, index2);
    Print(NewBegin);
}

void Interactive()
{
    List* Begin = NULL;
    List* End = NULL;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    Circle circle;
    int size;
    printf("enter the size\n");
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        circle.Ox = dist(gen);
        circle.Oy = dist(gen);
        circle.R = dist(gen);
        AddToTheEnd(&Begin, &End, circle);
    }

    Print(Begin);
    cout << endl << endl;
    PrintBack(Begin, End);

    int index1;
    printf("enter the 1 index\n");
    cin >> index1;
    int index2;
    printf("enter the 2 index\n");
    cin >> index2;
    List* NewBegin = reverse(&Begin, &End, index1, index2);
    Print(NewBegin);
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