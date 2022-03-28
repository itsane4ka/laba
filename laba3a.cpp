// laba3a.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// вариант 11
// доп задания

#define _CRT_SECURE_NO_WARNINGS
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

using namespace std;

struct Dot
{
    float x;
    float y;
    float z;
    float distance;
};

float dist_calc(float x, float y, float z)
{
    return sqrt(x * x + y * y + z * z);
}

void VecOutput(vector <Dot>& vec)
{
    cout << "\nO U T P U T: \n\n";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << "dot " << i << endl;
        cout << "x: " << vec[i].x << "\t";
        cout << "y: " << vec[i].y << "\t";
        cout << "z: " << vec[i].z << "\t";
        cout << "dist: " << vec[i].distance << endl << endl;
    }
}

void ArrOutput(Dot *arr, int size)
{
    cout << "\nO U T P U T: \n\n";
    for (int i = 0; i < size; i++)
    {
        cout << "dot " << i << endl;
        cout << "x: " << arr[i].x << "\t";
        cout << "y: " << arr[i].y << "\t";
        cout << "z: " << arr[i].z << "\t";
        cout << "dist: " << arr[i].distance << endl << endl;
    }
}

void GetVecToArr(Dot* arr, vector <Dot>& vec)
{
    for (int i = 0; i < vec.size(); i++)
        arr[i] = vec[i];
}

void GenerateVector(vector <Dot> &vec)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> big_n(1, 100);
    uniform_int_distribution<> small_n(1, 7);

    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].x = (float)big_n(gen) / small_n(gen);
        vec[i].y = (float)big_n(gen) / small_n(gen);
        vec[i].z = (float)big_n(gen) / small_n(gen);
        vec[i].distance = dist_calc(vec[i].x, vec[i].y, vec[i].z);
    }
}

void BubbleSort(vector <Dot> vec, int size)
{
    for (int i = 0; i < size; i++) {
        bool flag = true;
        for (int j = 0; j < size - i - 1; j++) {
            if (vec[j].distance > vec[j + 1].distance) {
                flag = false;
                swap(vec[j], vec[j + 1]);
            }
        }
        if (flag)
            break;
    }
    // VecOutput(vec);
}

void SelectionSort(vector <Dot> vec, int size)
{
    Dot tmp = {0};
    int smallest_index = 0;
    for (int i = 0; i < size - 1; i++)
    {
        smallest_index = i;
        for (int j = i; j < size; j++)
        {
            if (vec[smallest_index].distance > vec[j].distance)
                smallest_index = j;
        }
        swap(vec[i], vec[smallest_index]);
    }
    // VecOutput(vec);
}

void SelectionSortArray(Dot* array, int size)
{
    for (int startIndex = 0; startIndex < size - 1; ++startIndex)
    {
        int smallestIndex = startIndex;
        for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
        {
            if (array[currentIndex].distance < array[smallestIndex].distance)
                smallestIndex = currentIndex;
        }
        swap(array[startIndex], array[smallestIndex]);
    }
}

void InsertionSort(vector <Dot> vec, int size)
{
    float i = 0;
    Dot key = {0, 0, 0, 0};
    for (int j = 1; j < size; j++)
    {
        key = vec[j];
        i = j - 1;
        while (i >= 0 && vec[i].distance > key.distance)
        {
            vec[i + 1] = vec[i];
            i = i - 1;
            vec[i + 1] = key;
        }
    }
    // VecOutput(vec);
}

void QuickSort(Dot *arr, int size) {
    int i = 0;
    int j = size - 1;
    float mid = arr[size / 2].distance;

    do {
        while (arr[i].distance < mid) {
            i++;
        }
        while (arr[j].distance > mid) {
            j--;
        }

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        QuickSort(arr, j + 1);
    }
    if (i < size) {
        QuickSort(&arr[i], size - i);
    }
}

void merge(Dot merged[], int lenD, Dot L[], int lenL, Dot R[], int lenR)
{
    int i = 0;
    int j = 0;
    while (i < lenL || j < lenR)
    {
        if (i < lenL && j < lenR)
        {
            if (L[i].distance <= R[j].distance)
            {
                merged[i + j] = L[i];
                i++;
            }
            else {
                merged[i + j] = R[j];
                j++;
            }
        }
        else if (i < lenL)
        {
            merged[i + j] = L[i];
            i++;
        }
        else if (j < lenR)
        {
            merged[i + j] = R[j];
            j++;
        }
    }
}

void MergeSort(Dot arr[], int size)
{
    if (size > 1)
    {
        int middle = size / 2;
        int rem = size - middle;
        Dot* L = new Dot[middle];
        Dot* R = new Dot[rem];
        for (int i = 0; i < size; i++)
        {
            if (i < middle)
            {
                L[i] = arr[i];
            }
            else
            {
                R[i - middle] = arr[i];
            }
        }
        MergeSort(L, middle);
        MergeSort(R, rem);
        merge(arr, size, L, middle, R, rem);
    }
}

void CombinedSort(Dot arr[], int size)
{
    if (size > pow(10, 3))
    {
        QuickSort(arr, size);
    }
    else
    {
        SelectionSortArray(arr, size);
    }
    // ArrOutput(arr, size);
}

void Demo()
{
    // getting info
    int size;
    cout << "enter array size" << endl;
    cin >> size;
    vector <Dot> vec(size, {0, 0, 0, 0});
    GenerateVector(vec);
    VecOutput(vec);

    // vec->arr
    Dot* arr = new Dot[size];
    GetVecToArr(arr, vec);

    // 1
    cout << "Bubble sort \n";
    BubbleSort(vec, size);

    // 1
    cout << "Selection sort: \n";
    SelectionSort(vec, size);

    // 1
    cout << "Insertion sort: \n";
    InsertionSort(vec, size);

    // 2
    cout << "Quick sort: \n";
    QuickSort(arr, size);
    ArrOutput(arr, size);
    // getting arr elements back rand
    GetVecToArr(arr, vec);

    //3 
    cout << "Merge sort: \n";
    MergeSort(arr, size);
    ArrOutput(arr, size);
    // getting arr elements back rand
    GetVecToArr(arr, vec);

    // 4
    cout << "Combined sort: \n";
    CombinedSort(arr, size);
    // getting arr elements back rand
    GetVecToArr(arr, vec);

    // 5
    vector<float>vec_dist(size);
    for (int i = 0; i < size; i++)
        vec_dist[i] = vec[i].distance;
    cout << "Library sort: \n";
    sort(vec_dist.begin(), vec_dist.end());
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (vec[i].distance == vec_dist[j])
            {
                swap(vec[i], vec[j]);
            }
        }
    }
    VecOutput(vec);
}

void Benchmark(int size)
{
    // getting info
    vector <Dot> vec(size, { 0, 0, 0, 0 });
    GenerateVector(vec);
    // VecOutput(vec);

    Dot* arr = new Dot[size];
    GetVecToArr(arr, vec);

    // 1.1
    auto begin1vec = std::chrono::high_resolution_clock::now();
    BubbleSort(vec, size);
    auto end1vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms1vec = end1vec - begin1vec;
    cout << "The time of bubble sort: " << (float)elapsed_ms1vec.count() * 1000 << " ms\n\n";

    // 1.2
    auto begin2vec = std::chrono::high_resolution_clock::now();
    SelectionSort(vec, size);
    auto end2vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms2vec = end2vec - begin2vec;
    cout << "The time of selection sort: " << (float)elapsed_ms2vec.count() * 1000 << " ms\n\n";

    // 1.3
    auto begin3vec = std::chrono::high_resolution_clock::now();
    InsertionSort(vec, size);
    auto end3vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms3vec = end3vec - begin3vec;
    cout << "The time of insertion sort: " << (float)elapsed_ms3vec.count() * 1000 << " ms\n\n";

    // 2
    auto begin4vec = std::chrono::high_resolution_clock::now();
    QuickSort(arr, size);
    auto end4vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms4vec = end4vec - begin4vec;
    cout << "The time of quick sort: " << (float)elapsed_ms4vec.count() * 1000 << " ms\n\n";
    // getting arr elements back rand
    GetVecToArr(arr, vec);

    //3 
    auto begin5vec = std::chrono::high_resolution_clock::now();
    MergeSort(arr, size);
    auto end5vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms5vec = end5vec - begin5vec;
    cout << "The time of merge sort: " << (float)elapsed_ms5vec.count() * 1000 << " ms\n\n";
    // getting arr elements back rand
    GetVecToArr(arr, vec);

    // 4
    auto begin6vec = std::chrono::high_resolution_clock::now();
    CombinedSort(arr, size);
    auto end6vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms6vec = end6vec - begin6vec;
    cout << "The time of combined sort: " << (float)elapsed_ms6vec.count() * 1000 << " ms\n\n";
    // getting arr elements back rand
    GetVecToArr(arr, vec);

    // 5
    vector<float>vec_dist(size);
    for (int i = 0; i < size; i++)
        vec_dist[i] = vec[i].distance;
    auto begin7vec = std::chrono::high_resolution_clock::now();
    sort(vec_dist.begin(), vec_dist.end());
    auto end7vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms7vec = end7vec - begin7vec;
    cout << "The time of library sort: " << (float)elapsed_ms7vec.count() * 1000 << " ms\n\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (vec[i].distance == vec_dist[j])
            {
                swap(vec[i], vec[j]);
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    int chose_menu;
    cout << "0.Exit" << endl;
    cout << "1.Demo" << endl;
    cout << "2.Benchmark\n\n" << endl;
    cin >> chose_menu;

    switch (chose_menu)
    {
    case 0:
        break;
    case 1:
        Demo();
        break;
    case 2:
        int size = 10;
        while (size < pow(10, 4)*2)
        {
            cout << "S I Z E: " << size << endl << endl;
            Benchmark(size);
            size = size * 2;
        }      
        break;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
