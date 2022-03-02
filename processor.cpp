// processor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <windows.h>

using namespace std;

void vecInput(vector <long>& my_vec)
{
    random_device rd;
    mt19937 elemenent(rd());
    uniform_int_distribution<> distrib(1000, 9999);

    for (long i = 1; i <= 10000000; i++)   // 20 millions 
    {
        my_vec.push_back(distrib(elemenent));
    }
}

void DifferenceNotice()
{
    cout << "takts per sec (fact): " << CLOCKS_PER_SEC << endl << endl;
    cout << "waiting..." << endl;

    vector <long> my_vec1;
    auto start1 = std::chrono::high_resolution_clock::now();
    unsigned int t1_start = clock();

    vecInput(my_vec1);

    unsigned int t1_end = clock();
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    unsigned int t1_diff = t1_end - t1_start;
    cout << "rand 1: " << diff1.count() << " sec" << endl;
    cout << "rand 1: " << t1_diff << " takts" << endl;
    cout << "period: " << diff1.count() / t1_diff << endl;
    cout << "frequency: " << t1_diff / diff1.count() << endl;
    cout << "randomising(1) sucessful" << endl;
    using fps_24 = std::chrono::duration<double, std::ratio<1, 24>>;
    cout << fps_24(1s).count() << " frames at 24fps\n";
    cout << endl << endl << endl;

    vector <long> my_vec2;
    auto start2 = std::chrono::high_resolution_clock::now();
    unsigned int t2_start = clock();

    vecInput(my_vec2);

    unsigned int t2_end = clock();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    unsigned int t2_diff = t2_end - t2_start;
    cout << "rand 2: " << diff2.count() << " sec" << endl;
    cout << "rand 2: " << t2_diff << " takts" << endl;
    cout << "period: " << diff2.count() / t2_diff << endl;
    cout << "frequency: " << t2_diff / diff2.count() << endl;
    cout << "randomising(2) sucessful" << endl;
    using fps_24 = std::chrono::duration<double, std::ratio<1, 24>>;
    cout << fps_24(1s).count() << " frames at 24fps\n";

    cout << "\n\ndifference: " << (t1_diff - t2_diff)/1000.0 << " sec" << endl;
}


void FromStack()
{
    cout << "my sizeof char: " << sizeof(char) << endl;

    int size;
    cout << "enter the size of arrat to create:\n";
    cin >> size;

    char arr[size];

    cout << "arrat successfully created" << endl;
} 

void FromQueue()
{

    int size;
    cout << "enter the size of arrat to create:\n";
    cin >> size;

    char* arr = (char*)malloc(size);
    if (arr == nullptr)
    {
        cout << "cant get mamory" << endl;
        return;
    }
    for (long long i = 0; i < size; i++)
        arr[i] = 'z';

    cout << "arrat successfully created" << endl;
}

void GetMemory()
{
    cout << "stack: " << endl;
    FromStack();
    cout << "queue" << endl;
    FromQueue();
}

int main() 
{
    setlocale(LC_ALL, "rus");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int chose_menu;
    cout << "0.Exit" << endl;
    cout << "1.Time difference" << endl;
    cout << "2.Memory segregation\n\n" << endl;
    cin >> chose_menu;

    switch (chose_menu)
    {
    case 0:
        break;
    case 1:
        DifferenceNotice();
        break;
    case 2:
        GetMemory();
        break;
    }
    return 0;
}
