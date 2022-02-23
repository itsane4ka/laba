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
    double lower_bound = 0;
    double upper_bound = 10;
    default_random_engine gen;
    uniform_real_distribution<double> dist(lower_bound, upper_bound);

    for (int i = 0; i < circlepush.size(); i++)
    {
        circlepush[i].Ox = dist(gen);
        circlepush[i].Oy = dist(gen);
        circlepush[i].R = dist(gen);
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

List* getEnd(List* head)
{
    List* p = head;
    while (p)
    {
        p = p->next;
        if (p->next->next == nullptr)
            return p->next;
    }
}

void AddGenerated(List** head, Circle circleadditional)
{
    List* p = new List;
    p = *head;
    while (p->next)
    {   
        p = p->next;
    }
    List* y = p;
    y->next = new List;
    y = y->next;
    y->circle.Ox = circleadditional.Ox;
    y->circle.Oy = circleadditional.Oy;
    y->circle.R = circleadditional.R;
    y->next = NULL;
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

void reverse(int index1, int index2, List** head)
{
    List* ptr1 = new List;
    ptr1 = *head;

    List* flag = nullptr;
    List* flag2 = ptr1;

    List* ptr2 = new List;  // создаю второй список
    ptr2->circle.Ox = ptr1->circle.Ox;
    ptr2->circle.Oy = ptr1->circle.Oy;
    ptr2->circle.R = ptr1->circle.R;
    ptr2->next = NULL;

    List* end2 = ptr2;

    int i = 0;
    int j = 0;
    int counter = 0;
    int SecondCounter = 0;
    int ThirdCounter = 0;
    while (ptr1)
    {
        cout << "index: " << counter << "\t" << ptr1->circle.Ox << "\t";
        
        if (counter > 0 && (counter < index1 || counter > index2))
            AddToTheEnd(&ptr2, ptr1->circle);
        else if (counter >= index1 && counter <= index2)
        {
            if (SecondCounter < abs(index2 - index1) / 2 + 1)
            {
                i = abs(index2 - index1) - SecondCounter * 2;
                flag = ptr1;
                while (i > 0)
                {
                    ptr1 = ptr1->next;
                    i--;
                }
                AddToTheEnd(&ptr2, ptr1->circle);
                ptr1 = flag;
                SecondCounter++;
            }
            else
            {
                flag2 = ptr1;
                ptr1 = *head;
                j = index1 + abs(index2 - index1) / 2 - ThirdCounter - 1;
                while (j > 0)
                {
                    ptr1 = ptr1->next;
                    j--;
                }
                AddToTheEnd(&ptr2, ptr1->circle);
                ptr1 = flag2;
                ThirdCounter++;
            }
        }
        cout << ptr2->circle.Ox << endl;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        counter++;
    }
    delete flag;
    delete ptr2;
    delete end2;
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
        AddGenerated(&ptrhead, circlepush[i]);
    }
    Print(ptrhead);
    List* end = getEnd(ptrhead);
    //cout << end->circle.Ox << " is th end";

    int index1 = 3, index2 = 7;
    reverse(index1, index2, &ptrhead);
    delete ptrhead;
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
        AddGenerated(&ptrhead, circlepush[i]);
    }
    Print(ptrhead);
    List* end = getEnd(ptrhead);
    //cout << end->circle.Ox << " is th end";

    int index1, index2;
    cin >> index1 >> index2;
    reverse(index1, index2, &ptrhead);
    delete ptrhead;
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
