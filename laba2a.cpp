// spisok.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

// вариант 1(с)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <fstream>
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

void List_Creation(List** u, int AmountNodes)
{
    srand(static_cast<unsigned int>(time(0)));
    //first node
    *u = new List;
    (*u)->circle.Ox = rand() % 10 + (double)rand() / RAND_MAX;
    (*u)->circle.Oy = rand() % 10 + (double)rand() / RAND_MAX;
    (*u)->circle.R = rand() % 10 + (double)rand() / RAND_MAX;
    (*u)->next = NULL;

    //second node
    List* x = *u;          //создаю вспомогательную перменную указатель (совп с началом)
                           //которяа хранит адрес полседнего элемента
    x->next = new List;    //выделяю место в памяти для след эл
    x = x->next;           //перенаправляю указатель на х на выделенную область
    x->circle.Ox = rand() % 10 + (double)rand() / RAND_MAX;
    x->circle.Oy = rand() % 10 + (double)rand() / RAND_MAX;
    x->circle.R = rand() % 10 + (double)rand() / RAND_MAX;        //определяю значние эл списка
    x->next = NULL;        //делаем чтоб указ на след эл был пуст

    //third node
    List* y = x;
    y->next = new List;
    y = y->next;
    y->circle.Ox = rand() % 10 + (double)rand() / RAND_MAX;
    y->circle.Oy = rand() % 10 + (double)rand() / RAND_MAX;
    y->circle.R = rand() % 10 + (double)rand() / RAND_MAX;
    y->next = NULL;
}

void Print(List* u)
{
    List* p = u;
    cout << "Spisok:" << endl;
    while (p)
    {
        cout << "X: " << p->circle.Ox << "\t";
        cout << "Y: " << p->circle.Oy << "\t";
        cout << "R: " << p->circle.R << "\n";
        p = p->next;
    }
}

void FillList(Circle circles_mas[], vector<Circle>& circles_vec, List** ptr, int AmountNodes)
{
    cout << "amount of nodes: " << AmountNodes << endl << endl;
    // fixed array
    cout << "array: " << endl;
    for (int i = 0; i < AmountNodes; i++)
    {
        circles_mas[i].Ox = rand() % 100 + (double)rand() / RAND_MAX;
        circles_mas[i].Oy = rand() % 100 + (double)rand() / RAND_MAX;
        circles_mas[i].R = rand() % 100 + (double)rand() / RAND_MAX;
        cout << circles_mas[i].Ox << " " << circles_mas[i].Oy << " " << circles_mas[i].R << endl;
        if (i > 48 && AmountNodes > i)
        {
            cout << "error. static memory limit." << endl;
            break;
        }
    }

    //vector
    cout << "vector: " << endl;
    circles_vec.resize(AmountNodes);
    for (int i = 0; i < AmountNodes; i++)
    {
        circles_vec[i].Ox = rand() % 100 + (double)rand() / RAND_MAX;
        circles_vec[i].Oy = rand() % 100 + (double)rand() / RAND_MAX;
        circles_vec[i].R = rand() % 100 + (double)rand() / RAND_MAX;
        cout << circles_vec[i].Ox << " " << circles_vec[i].Oy << " " << circles_vec[i].R << endl;
    }

    // list
    *ptr = NULL;
    List_Creation(ptr, AmountNodes);
    Print(*ptr);
}

void AddToTheEnd(List** u, Circle circleadditional)
{
    cout << "MAKING NEW SPISOK......" << endl;
    List* p = new List;
    p = *u;
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

void InsertList(List** u, int index, Circle circleadditional)
{
    List* t = *u;
    List* p = new List;
    p->circle.Ox = circleadditional.Ox;
    p->circle.Oy = circleadditional.Oy;
    p->circle.R = circleadditional.R;
    if (index == 0)
    {
        p->next = *u;
        *u = p;
        return;
    }
    int counter = 0;
    List* t1 = t->next;
    while (t1)
    {
        counter++;
        if (counter == index)
        {
            t->next = p;
            p->next = t1;
            return;
        }
        t = t1;
        t1 = t1->next;
    }
    cout << endl;
}

void DeleteElementArray(Circle circles_mas[], int index, int AmountNodes)
{
    for (int i = 0; i < AmountNodes; i++)
    {
        if (i == index)
        {
            for (int j = i; j < AmountNodes - 1; j++)
            {
                circles_mas[j] = circles_mas[j + 1];
            }
            circles_mas[AmountNodes] = { 0, 0, 0 };
            break;
        }
    }
}

void DeleteEl(List** u, int index)
{
    if (*u == nullptr)
        return;
    List* t = *u;
    if (index == 0)
    {
        *u = t->next;
        delete t;
        return;
    }
    List* t1 = t->next;

    int counter = 0;
    while (t1)
    {
        if (counter == index)
        {
            t->next = t1->next;
            delete t1;
            return;
        }
        t = t1;
        t1 = t1->next;
        counter++;
    }
}

void GetListElement(List* head, int index2)
{
    List* p = head;
    int counter = 0;
    cout << "Spisok:" << endl;
    while (p)
    {
        if (counter == index2)
        {
            cout << "X: " << p->circle.Ox << "\t";
            cout << "Y: " << p->circle.Oy << "\t";
            cout << "R: " << p->circle.R << "\n";
            break;
        }
        counter++;
        p = p->next;
    }
}

void AddToArray(Circle *circles_mas, int index, Circle circleinsert, int el_counter)
{
    for (int i = 0; i < el_counter + 1; i++)
    {
        if (i == index)
        {
            circles_mas[i] = circleinsert;
            for (int j = i+1; j < el_counter - 1; j++)
            {
                circles_mas[j] = circles_mas[j + 1];
            }
            return;
        }
    }
}

void vecOutput(vector<Circle>& circles_vec)
{
    cout << "vec: " << endl;
    for (int i = 0; i < circles_vec.size(); i++)
    {
        cout << circles_vec[i].Ox << " " << circles_vec[i].Oy << " " << circles_vec[i].R << endl;
    }
}

void arrOutput(Circle circle[], int length)
{
    cout << "arr:" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << circle[i].Ox << " " << circle[i].Oy << " " << circle[i].R << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(static_cast<unsigned int>(time(0)));

    int FirstAction = 10;
    int el_counter = 0;
    bool creation = false;

    Circle circles_mas[50] = {};
    vector<Circle> circles_vec;
    List* ptr = NULL;

    while (FirstAction != 0)
    {
        cout << "1 - interactive dialog mode\n2 - demonstraion\n3 - banchmark\n4 - exit(push 0)" << endl << endl;
        cin >> FirstAction;

        cout << "elements: " << el_counter << endl;
        if (FirstAction == 1)
        {
            // interactive mode

            cout << "choose the option (1-5)\n";
            cout << "1 - create empty list\n";
            cout << "2 - push elelement to the end\n";
            cout << "3 - insert before index\n";
            cout << "4 - delete element by index\n";
            cout << "5 - set and get element by index\n";
            cout << "6 - print list length\n";
            cout << endl << endl << endl;

            int SecondAction;
            cin >> SecondAction;

            if (SecondAction == 1)
            {
                // 1 - create empty
                if (creation)
                    cout << "list already created" << endl;
                else
                {
                    cout << "option 1: create empty list" << endl;
                    creation = true;
                    cout << "empty list created (arr, vec, list)" << endl << endl << endl;
                }
            }
            else if (SecondAction == 2)
            {
                if (creation)
                {
                    // 2 - pushing element to the end
                    cout << "option 2: push element to the end" << endl;
                    Circle circlepush;

                    cout << "enter the circle's X" << endl;
                    cin >> circlepush.Ox;
                    cout << "enter the circle's Y" << endl;
                    cin >> circlepush.Oy;
                    cout << "enter the circle's Z" << endl;
                    cin >> circlepush.R;
                    cout << endl << endl << endl;

                    //arr
                    if (el_counter == 50)
                        cout << "memory limit. cant add elelments" << endl;
                    else
                        circles_mas[el_counter] = circlepush;
                    arrOutput(circles_mas, el_counter + 1);
                    // vec
                    circles_vec.push_back(circlepush);
                    vecOutput(circles_vec);

                    //cout << el_counter << endl;
                    if (el_counter == 0)
                    {
                        ptr = new List;
                        ptr->circle.Ox = circlepush.Ox;
                        ptr->circle.Oy = circlepush.Oy;
                        ptr->circle.R = circlepush.R;
                        ptr->next = NULL;
                        el_counter++;
                    }
                    else
                    {
                        AddToTheEnd(&ptr, circlepush);
                        el_counter++;
                    }
                    Print(ptr);
                    cout << endl << endl << endl;
                }
                else
                    cout << "you need to create the list first\n\n";
            }
            else if (SecondAction == 3)
            {
                // 3 - insert before index
                if (creation)
                {
                    if (el_counter == 0)
                    {
                        cout << "first push some elements" << endl;
                    }
                    else
                    {
                        unsigned int index_insert;
                        cout << "option 3: insert before index" << endl;
                        cin >> index_insert;

                        Circle circleinsert;
                        cout << "enter the circle's X" << endl;
                        cin >> circleinsert.Ox;
                        cout << "enter the circle's Y" << endl;
                        cin >> circleinsert.Oy;
                        cout << "enter the circle's Z" << endl;
                        cin >> circleinsert.R;
                        cout << endl << endl << endl;

                        //arr
                        if (el_counter == 50)
                            cout << "memory limit. error" << endl;
                        else
                        {
                            AddToArray(circles_mas, index_insert - 1, circleinsert, el_counter);
                            arrOutput(circles_mas, el_counter + 1);
                        }

                        //vec
                        vector <Circle>::iterator it;
                        it = circles_vec.begin() + index_insert - 1;
                        circles_vec.insert(it, circleinsert);
                        vecOutput(circles_vec);

                        //list

                        cout << "lets see how we can insert element into list" << endl;
                        InsertList(&ptr, index_insert - 1, circleinsert);
                        Print(ptr);
                        cout << endl << endl << endl;

                        el_counter++;
                    }
                }
            }
            else if (SecondAction == 4)
            {
                cout << "option 4: delete el with index. " << endl;
                int index_insert;
                cout << "enter the index" << endl;
                cin >> index_insert;
                // arr
                //cout << "pre-last element (was last)" << endl;
                //cout << circles_mas[AmountNodes - 1].Ox << " " << circles_mas[AmountNodes - 1].Oy << " " << circles_mas_demo[AmountNodes - 1].R << endl;
                //cout << "last element" << endl;
                //cout << circles_mas[AmountNodes].Ox << " " << circles_mas[AmountNodes].Oy << " " << circles_mas_demo[AmountNodes].R << endl;
                // vec
                cout << "this was 4 el:" << endl;
                cout << circles_vec[index_insert].Ox << " " << circles_vec[index_insert].Oy << " " << circles_vec[index_insert].R << endl;
                cout << "4-th element now:" << endl;
                circles_vec.erase(circles_vec.begin() + index_insert);
                cout << circles_vec[index_insert].Ox << " " << circles_vec[index_insert].Oy << " " << circles_vec[index_insert].R << endl;
                // list
                DeleteEl(&ptr, index_insert - 2);
                Print(ptr);
                cout << endl << endl << endl;
            }
            else if (SecondAction == 5)
            {

            }
            else if (SecondAction == 6)
            {
                cout << "option 6 - list length" << endl;
                cout << "arr: " << 50 << endl;
                cout << "vec: " << circles_vec.size() << endl;
                List* p = ptr;
                int counter = 0;
                while (p)
                {
                    p = p->next;
                    counter++;
                }
                cout << "list: " << counter << endl;
                cout << endl << endl << endl;
            }
            else
                cout << "wrong number!" << endl;
        }
        else if (FirstAction == 2)
        {
            // demonstrational mode

            // 1 - create empty
            cout << "option 1: create empty list" << endl;
            Circle circles_mas_demo[50] = {};
            vector<Circle> circles_vec_demo;
            List* ptrdemo = NULL;
            cout << "empty list created (arr, vec, list)" << endl << endl;

            // 1.5 fill it with rand shit
            cout << "// i want to make some random circles: (additional)" << endl;
            int AmountNodes = 0;
            while (AmountNodes < 20)   // amount of nodes
                AmountNodes = rand() % 50;
            cout << "lets have " << AmountNodes << " circles" << endl << endl;
            FillList(circles_mas_demo, circles_vec_demo, &ptrdemo, AmountNodes);
            Circle flag_circle;
            cout << endl << endl << endl;

            // 2 - pushing element to the end
            cout << "option 2: push element to the end" << endl;
            Circle circleadditional = { 4.5, 3.22, 8.0 };
            cout << "error. can not add elements to a fixed arr" << endl;
            circles_vec_demo.resize(AmountNodes);
            circles_vec_demo.push_back(circleadditional);
            cout << "last vec element" << endl;
            cout << circles_vec_demo[AmountNodes - 1].Ox << " " << circles_vec_demo[AmountNodes - 1].Oy << " " << circles_vec_demo[AmountNodes - 1].R << endl;
            cout << "added element: " << endl;
            cout << circles_vec_demo[AmountNodes].Ox << " " << circles_vec_demo[AmountNodes].Oy << " " << circles_vec_demo[AmountNodes].R << endl;
            AddToTheEnd(&ptrdemo, circleadditional);
            Print(ptrdemo);
            cout << endl << endl << endl;

            // 3 - insert before index
            cout << "option 3: insert before index" << endl;
            cout << "can not add element to a fixed array. memory limit" << endl;
            int index = 3; // index >= 1
            vector <Circle>::iterator it;
            it = circles_vec_demo.begin() + index;
            cout << "lets see how we can insert element into vec" << endl;
            cout << circles_vec_demo[index].Ox << " " << circles_vec_demo[index].Oy << " " << circles_vec_demo[index].R << endl;
            circles_vec_demo.insert(it, circleadditional);
            cout << circles_vec_demo[index].Ox << " " << circles_vec_demo[index].Oy << " " << circles_vec_demo[index].R << endl;
            cout << "lets see how we can insert element into list" << endl;
            InsertList(&ptrdemo, index - 1, circleadditional);
            Print(ptrdemo);
            cout << endl << endl << endl;

            // 4 - delete el with index
            cout << "option 4: delete el with index. " << endl;
            DeleteElementArray(circles_mas_demo, index, AmountNodes);
            cout << "pre-last element (was last)" << endl;
            cout << circles_mas_demo[AmountNodes - 1].Ox << " " << circles_mas_demo[AmountNodes - 1].Oy << " " << circles_mas_demo[AmountNodes - 1].R << endl;
            cout << "last element" << endl;
            cout << circles_mas_demo[AmountNodes].Ox << " " << circles_mas_demo[AmountNodes].Oy << " " << circles_mas_demo[AmountNodes].R << endl;
            // delete sym from vec
            cout << "this was 4 el:" << endl;
            cout << circles_vec_demo[index].Ox << " " << circles_vec_demo[index].Oy << " " << circles_vec_demo[index].R << endl;
            cout << "4-th element now:" << endl;
            circles_vec_demo.erase(circles_vec_demo.begin() + index);
            cout << circles_vec_demo[index].Ox << " " << circles_vec_demo[index].Oy << " " << circles_vec_demo[index].R << endl;
            //delete list el
            DeleteEl(&ptr, index - 2);
            Print(ptrdemo);
            cout << endl << endl << endl;

            // 5 - set and get
            int index2 = 3;
            cout << "index " << index2 << endl;
            cout << "lets get the element from array: " << endl;
            cout << circles_mas_demo[index2 - 1].Ox << " " << circles_mas_demo[index2 - 1].Oy << " " << circles_mas_demo[index2 - 1].R << endl;
            cout << "lets get the element from array: " << endl;
            cout << circles_vec_demo[index2 - 1].Ox << " " << circles_vec_demo[index2 - 1].Oy << " " << circles_vec_demo[index2 - 1].R << endl;
            // list index
            GetListElement(ptrdemo, index2 - 1);
            cout << endl << endl << endl;

            // 6 - list length
            cout << "option 6 - list length" << endl;
            cout << "arr: " << 50 << endl;
            cout << "vec: " << circles_vec_demo.size() << endl;
            List* p = ptrdemo;
            int counter = 0;
            while (p)
            {
                p = p->next;
                counter++;
            }
            cout << "list: " << counter << endl;
            cout << endl << endl << endl;
        }
        else if (FirstAction == 3)
        {
            // benchmark mode
        }
        else if (FirstAction == 0)
        {
            cout << "EXIT" << endl << endl;
        }
        else
        {
            cout << "error. you enetered a wrong number" << endl;
        }
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

