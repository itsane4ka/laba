// spisok.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

// вариант 1.4

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
#include <chrono>
#include <windows.h>
#include <time.h>

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

    //forth node
    List* z = y;
    z->next = new List;
    z = z->next;
    z->circle.Ox = rand() % 10 + (double)rand() / RAND_MAX;
    z->circle.Oy = rand() % 10 + (double)rand() / RAND_MAX;
    z->circle.R = rand() % 10 + (double)rand() / RAND_MAX;
    z->next = NULL;

    //fifth node
    List* w = z;
    w->next = new List;
    w = w->next;
    w->circle.Ox = rand() % 10 + (double)rand() / RAND_MAX;
    w->circle.Oy = rand() % 10 + (double)rand() / RAND_MAX;
    w->circle.R = rand() % 10 + (double)rand() / RAND_MAX;
    w->next = NULL;
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
    //cout << "MAKING NEW SPISOK......" << endl;
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
    cout << "Spisok by index:" << endl;
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
    Circle circles_mas_additional[5] = {};
    for (int i = 0; i < el_counter + 1; i++)
    {
        if (i == index)
        {
            circles_mas_additional[i] = circleinsert;
            for (int j = i + 1; j < el_counter + 1; j++)
            {
                circles_mas_additional[j] = circles_mas[j - 1];
            }
            for (int t = 0; t < el_counter + 1; t++)
            {
                circles_mas[t] = circles_mas_additional[t];
            }
            return;
        }
        else
            circles_mas_additional[i] = circles_mas[i];
    }
}

void arrErase(Circle* circles_mas, int index, int el_counter)
{
    for (int i = 0; i < el_counter; i++)
    {
        if (index - 1 == i)
        {
            for (int j = i; j < el_counter - 1; j++)
            {
                circles_mas[j] = circles_mas[j + 1];
            }
            circles_mas[el_counter] = { 0, 0, 0 };
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

void SetListElement(List* ptr, int index, double x_set, double y_set, double R_set)
{
    List* p = ptr;
    int counter = 0;
    cout << "Spisok by index:" << endl;
    while (p)
    {
        if (counter == index)
        {
            p->circle.Ox = x_set;
            p->circle.Oy = y_set;
            p->circle.R = R_set;

            cout << "X: " << p->circle.Ox << "\t";
            cout << "Y: " << p->circle.Oy << "\t";
            cout << "R: " << p->circle.R << "\n";
            break;
        }
        counter++;
        p = p->next;
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

        //cout << "elements: " << el_counter << endl;
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
                int index_delete;
                cout << "enter the index" << endl;
                cin >> index_delete;
                // arr
                arrErase(circles_mas, index_delete, el_counter);
                arrOutput(circles_mas, el_counter - 1);
                
                // vec
                circles_vec.erase(circles_vec.begin() + index_delete -1);
                vecOutput(circles_vec);
                // list
                DeleteEl(&ptr, index_delete - 2);
                Print(ptr);
                cout << endl << endl << endl;
            }
            else if (SecondAction == 5)
            {
                int ThirdAction;
                cout << "enter 1 - get" << endl; 
                cout << "enter 2 - set" << endl;
                cin >> ThirdAction;

                if (ThirdAction == 1)
                {
                    int index_find;
                    cout << "enter the index" << endl;
                    cin >> index_find;
                    cout << "arr with index " << index_find << " is " << circles_mas[index_find - 1].Ox << " " << circles_mas[index_find - 1].Oy << " " << circles_mas[index_find - 1].R << endl;
                    cout << "vec with index " << index_find << " is " << circles_vec[index_find - 1].Ox << " " << circles_vec[index_find - 1].Oy << " " << circles_vec[index_find - 1].R << endl;
                    cout << "list with index " << index_find << " is:" << endl;
                    GetListElement(ptr, index_find - 1);
                }
                else
                {
                    int index_find;
                    cout << "enter the index" << endl;
                    cin >> index_find;
                    cout << "now enter the new element x\n";
                    double x_set;
                    cin >> x_set;
                    cout << "now enter the new element y\n";
                    double y_set;
                    cin >> y_set;
                    cout << "now enter the new element R\n";
                    double R_set;
                    cin >> R_set;

                    circles_mas[index_find - 1].Ox = x_set;
                    circles_mas[index_find - 1].Oy = y_set;
                    circles_mas[index_find - 1].R = R_set;

                    circles_vec[index_find - 1].Ox = x_set;
                    circles_vec[index_find - 1].Oy = y_set;
                    circles_vec[index_find - 1].R = R_set;
                    
                    cout << "arr with index " << index_find << " is " << circles_mas[index_find - 1].Ox << " " << circles_mas[index_find - 1].Oy << " " << circles_mas[index_find - 1].R << endl;
                    cout << "vec with index " << index_find << " is " << circles_vec[index_find - 1].Ox << " " << circles_vec[index_find - 1].Oy << " " << circles_vec[index_find - 1].R << endl;
                    cout << "list with index " << index_find << " is:" << endl;
                    GetListElement(ptr, index_find - 1);
                }

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
            DeleteEl(&ptrdemo, index - 2);
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
            cout << "lets get the element from list: " << endl;
            GetListElement(ptrdemo, index2 - 1);
            cout << endl << endl << endl;

            cout << "enter the index" << endl;
            index = 3;
            cout << "now enter the new element x\n";
            double x_set = 4;
            cout << "now enter the new element y\n";
            double y_set = 3;
            cout << "now enter the new element R\n";
            double R_set = 7;

            circles_mas_demo[index - 1].Ox = x_set;
            circles_mas_demo[index - 1].Oy = y_set;
            circles_mas_demo[index - 1].R = R_set;

            circles_vec_demo[index - 1].Ox = x_set;
            circles_vec_demo[index - 1].Oy = y_set;
            circles_vec_demo[index - 1].R = R_set;

            cout << "arr with index " << index << " is " << circles_mas_demo[index - 1].Ox << " " << circles_mas_demo[index - 1].Oy << " " << circles_mas_demo[index - 1].R << endl;
            cout << "vec with index " << index << " is " << circles_vec_demo[index - 1].Ox << " " << circles_vec_demo[index - 1].Oy << " " << circles_vec_demo[index - 1].R << endl;
            cout << "list with index " << index << " is:" << endl;
            SetListElement(ptrdemo, index - 1, x_set, y_set, R_set);
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

            int el_counter_demo = 0;

            //1
            cout << "1:" << endl;
            auto begin1 = std::chrono::high_resolution_clock::now();

            Circle circles_mas_demo[5] = {};
            vector<Circle> circles_vec_demo;
            List* ptrdemo = NULL;
            cout << "empty list created (arr, vec, list)" << endl << endl;

            auto end1 = std::chrono::high_resolution_clock::now();
            //auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
            std::chrono::duration<double> elapsed_ms1 = end1 - begin1;
            cout << "The common time of list creation: " << (float)elapsed_ms1.count() << " s\n\n\n\n";

            //2
            cout << "2:" << endl;
            auto begin2arr = std::chrono::high_resolution_clock::now();

            Circle circlepush = { 5.2, 6.8, 9.9 };
            //arr
            if (el_counter_demo == 50)
                cout << "memory limit. cant add elelments" << endl;
            else
                circles_mas_demo[el_counter_demo] = circlepush; 
            arrOutput(circles_mas_demo, el_counter_demo + 1);

            auto end2arr = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms2arr = end2arr - begin2arr;
            cout << "The common time of list creation: " << (float)elapsed_ms2arr.count()<< " s\n\n\n\n";

            // vec
            auto begin2vec = std::chrono::high_resolution_clock::now();

            circles_vec.push_back(circlepush);
            vecOutput(circles_vec);

            auto end2vec = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms2vec = end2vec - begin2vec;
            cout << "The common time of list creation: " << (float)elapsed_ms2vec.count() << " s\n\n\n\n";

            //cout << el_counter << endl;

            auto begin2list = std::chrono::high_resolution_clock::now();
            if (el_counter_demo == 0)
            {
                ptrdemo = new List;
                ptrdemo->circle.Ox = circlepush.Ox;
                ptrdemo->circle.Oy = circlepush.Oy;
                ptrdemo->circle.R = circlepush.R;
                ptrdemo->next = NULL;
                el_counter_demo++;
            }
            else
            {
                AddToTheEnd(&ptrdemo, circlepush);
                el_counter_demo++;
            }
            Print(ptrdemo);

            auto end2list = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms2list = end2list - begin2list;
            cout << "The common time of list creation: " << (float)elapsed_ms2list.count() << " s\n\n\n\n";

            el_counter_demo++;

            //2.5   
            cout << "2.5:\nput some random shit" << endl;
            auto begin25 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 2; i++)
            {
                circles_mas_demo[el_counter_demo-1] = circlepush;
                circles_vec_demo.push_back(circlepush);
                AddToTheEnd(&ptrdemo, circlepush);
                el_counter_demo++;
            }
            circles_vec_demo.push_back(circlepush);
            arrOutput(circles_mas_demo, el_counter_demo - 1);
            vecOutput(circles_vec_demo);
            Print(ptrdemo);
            cout << endl << endl << endl;

            auto end25 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms25 = end25 - begin2list;
            cout << "The common time of list making: " << (float)elapsed_ms25.count() << " s\n\n\n\n";

            // 3
            cout << "3:" << endl;
            int index = 3; 

            //arr
            auto begin3arr = std::chrono::high_resolution_clock::now();
            AddToArray(circles_mas_demo, index - 1, circlepush, el_counter_demo);
            arrOutput(circles_mas_demo, el_counter_demo);
            auto end3arr = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms3arr = end3arr - begin3arr;
            cout << "The time of element adding in arr: " << (float)elapsed_ms3arr.count() << " s\n\n";

            //vec
            auto begin3vec = std::chrono::high_resolution_clock::now();
            vector <Circle>::iterator it;
            it = circles_vec_demo.begin() + index;
            circles_vec_demo.insert(it, circlepush);
            vecOutput(circles_vec_demo);

            auto end3vec = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms3vec = end3vec - begin3vec;
            cout << "The time of element adding in arr: " << (float)elapsed_ms3vec.count() << " s\n\n";

            //list
            auto begin3list = std::chrono::high_resolution_clock::now();
            InsertList(&ptrdemo, index - 1, circlepush);
            Print(ptrdemo);

            auto end3list = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms3list = end3list - begin3list;
            cout << "The time of element adding in arr: " << (float)elapsed_ms3list.count() << " s\n\n";
            cout << endl << endl << endl;

            // 4

            cout << "4: " << endl;
            int index_delete = 3;
            // arr
            auto begin4arr = std::chrono::high_resolution_clock::now();
            arrErase(circles_mas_demo, index_delete, 5);
            arrOutput(circles_mas_demo, el_counter_demo - 1);
            auto end4arr = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms4arr = end4arr - begin4arr;
            cout << "The time of element deleting in arr: " << (float)elapsed_ms4arr.count() << " s\n\n";

            // vec
            auto begin4vec = std::chrono::high_resolution_clock::now();
            circles_vec_demo.erase(circles_vec_demo.begin() + index_delete - 1);
            vecOutput(circles_vec_demo);
            auto end4vec = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms4vec = end4vec - begin4vec;
            cout << "The time of element deleting in vec: " << (float)elapsed_ms4vec.count() << " s\n\n";
            // list
            auto begin4list = std::chrono::high_resolution_clock::now();
            DeleteEl(&ptrdemo, index_delete - 2);
            Print(ptrdemo);
            auto end4list = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms4list = end4list - begin4list;
            cout << "The time of element deleting in list: " << (float)elapsed_ms4list.count() << " s\n\n";
            cout << endl << endl << endl;

            // 5
            cout << "5:\n";

            int index2 = 3;
            //cout << "index " << index2 << endl;
            cout << "arr by index:\n";
            auto begin5arr = std::chrono::high_resolution_clock::now();
            cout << "X: " << circles_mas_demo[index2 - 1].Ox << " " << "Y:" << " " << circles_mas_demo[index2 - 1].Oy << " " << "Z:" << " " << circles_mas_demo[index2 - 1].R << endl;
            auto end5arr = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms5arr = end5arr - begin5arr;
            cout << "The time of element getting in arr: " << (float)elapsed_ms5arr.count() << " s\n\n";
            
            cout << "vec by index:\n";
            auto begin5vec = std::chrono::high_resolution_clock::now();
            cout << "X: " << circles_vec_demo[index2 - 1].Ox << " " << "Y:" << " " << circles_vec_demo[index2 - 1].Oy << " " << "Z:" << " " << circles_vec_demo[index2 - 1].R << endl;
            auto end5vec = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms5vec = end5vec - begin5vec;
            cout << "The time of element getting in vec: " << (float)elapsed_ms5vec.count() << " s\n\n";
            
            // list index
            auto begin5list = std::chrono::high_resolution_clock::now();
            GetListElement(ptrdemo, index2 - 1);
            auto end5lsit = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms5list = end5lsit - begin5list;
            cout << "The time of element getting in list: " << (float)elapsed_ms5list.count() << " s\n\n";
            cout << endl;

            cout << "set element:\n";
            index = 3;;
            double x_set = 4.5;
            double y_set = 3.3;
            double R_set = 7.9;
            auto begin6arr = std::chrono::high_resolution_clock::now();
            circles_mas_demo[index - 1].Ox = x_set;
            circles_mas_demo[index - 1].Oy = y_set;
            circles_mas_demo[index - 1].R = R_set;
            cout << "arr with index " << index << " is " << circles_mas_demo[index - 1].Ox << " " << circles_mas_demo[index - 1].Oy << " " << circles_mas_demo[index - 1].R << endl;
            auto end6arr = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms6arr = end6arr - begin6arr;
            cout << "The time of element setting in arr: " << (float)elapsed_ms6arr.count() << " s\n\n";

            auto begin6vec = std::chrono::high_resolution_clock::now();
            circles_vec_demo[index - 1].Ox = x_set;
            circles_vec_demo[index - 1].Oy = y_set;
            circles_vec_demo[index - 1].R = R_set;
            auto end6vec = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms6vec = end6vec - begin6vec;
            cout << "The time of element setting in vec: " << (float)elapsed_ms6vec.count() << " s\n\n";

            cout << "vec with index " << index << " is " << circles_vec_demo[index - 1].Ox << " " << circles_vec_demo[index - 1].Oy << " " << circles_vec_demo[index - 1].R << endl;
            //cout << "list with index " << index << " is:" << endl;

            auto begin6list = std::chrono::high_resolution_clock::now();
            SetListElement(ptrdemo, index - 1, x_set, y_set, R_set);
            cout << endl << endl << endl;
            auto end6list = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms6list = end6list - begin6list;
            cout << "The time of element setting in list: " << (float)elapsed_ms6list.count() << " s\n\n";

            // 6
            cout << "6:" << endl;
            auto begin6len = std::chrono::high_resolution_clock::now();
            cout << "arr: " << 5 << endl;
            auto end6len = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms6len= end6len - begin6len;
            cout << "The time of element setting in list: " << (float)elapsed_ms6len.count() << " s\n\n";

            auto begin6lenvec = std::chrono::high_resolution_clock::now();
            cout << "vec: " << circles_vec.size() << endl;
            auto end6lenvec = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms6lenvec = end6lenvec - begin6lenvec;
            cout << "The time of element setting in list: " << (float)elapsed_ms6lenvec.count() << " s\n\n";

            auto begin6lenlist = std::chrono::high_resolution_clock::now();
            List* p = ptr;
            int counter = 0;
            while (p)
            {
                p = p->next;
                counter++;
            }
            cout << "list: " << counter << endl;
            auto end6lenlist = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_ms6lenlist = end6lenlist - begin6lenlist;
            cout << "The time of element setting in list: " << (float)elapsed_ms6lenlist.count() << " s\n\n";

            cout << endl << endl << endl;
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

