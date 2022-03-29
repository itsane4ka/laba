// laba3b.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

vector<string> names { "Alex", "Boris", "Charles", "Christopher", "David",
        "Robert", "Thomas", "Mark", "Kevin", "Jack" };

struct DateOfCreation {
    int day; // 0<=day<=31
    int month; // 0<=month<=12
    int year; // 0<=year<=2300
};

struct TimeOfCreation {
    int hour; // 0<=hour<=24
    int minute; // 0<=min<=59
    int second; // 0<=sec<=59
};

struct MonstersData {
    string monster_name;             // 1
    unsigned int health_amount;      // 2 - radix sort
    short int attacks_amount;        // 3
    double attack_probability;       // 4
    int special_attack_type;         // 5 - counting sort
    DateOfCreation apperance_data;   // 6
};

void PrintMonsterInfo(MonstersData monster)
{
    cout << "Name: " << monster.monster_name << "\n";
    cout << "Health amount: " << monster.health_amount << "\n";
    cout << "Attacks amount: " << monster.attacks_amount << "\n";
    cout << "Attack probability: " << monster.attack_probability << "\n"; // 0<=attack.probability<=1
    cout << "Special attack type: " << monster.special_attack_type << "\n";  // 1 - увеличить урон 2 - повторить атаку 3 - вылечить себя 4 - парализовать соперника
    cout << "Appereance data: " << monster.apperance_data.day << "." << monster.apperance_data.month << "." << monster.apperance_data.year << "\n";

    cout << endl << endl << endl;
}

void PrintMonsterInfoArr(MonstersData monster_arr)
{
    cout << "Name: " << monster_arr.monster_name << "\n";
    cout << "Health amount: " << monster_arr.health_amount << "\n";
    cout << "Attacks amount: " << monster_arr.attacks_amount << "\n";
    cout << "Attack probability: " << monster_arr.attack_probability << "\n"; // 0<=attack.probability<=1
    cout << "Special attack type: " << monster_arr.special_attack_type << "\n";  // 1 - увеличить урон 2 - повторить атаку 3 - вылечить себя 4 - парализовать соперника
    cout << "Appereance data: " << monster_arr.apperance_data.day << "." << monster_arr.apperance_data.month << "." << monster_arr.apperance_data.year << "\n";

    cout << endl << endl;
}

void GetVec(int size, vector <MonstersData> &monster)
{
    srand(static_cast<unsigned int>(time(0)));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> name(0, 9);
    uniform_int_distribution<> health(1, 50000);
    uniform_int_distribution<> attacks(1, 2000);
    uniform_int_distribution<> type(1, 4);
    uniform_int_distribution<> day(1, 31);
    uniform_int_distribution<> month(1, 12);
    uniform_int_distribution<> year(2000, 2022);


    for (int i = 0; i < size; i++)
    {
        monster[i].monster_name = names[name(gen)];
        monster[i].health_amount = health(gen);
        monster[i].attacks_amount = attacks(gen);
        monster[i].attack_probability = (float)rand() / RAND_MAX;
        monster[i].special_attack_type = type(gen);
        monster[i].apperance_data.day = day(gen);
        monster[i].apperance_data.month = month(gen);
        monster[i].apperance_data.year = year(gen);

        cout << "MONSTER VEC " << i << ": \n";
        PrintMonsterInfo(monster[i]);
    }
}

void SortByName(int size, vector <MonstersData> &monster)
{
    for (int startIndex = 0; startIndex < size - 1; startIndex++)
    {
        int smallestIndex = startIndex;
        for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
        {
            if (monster[currentIndex].monster_name < monster[smallestIndex].monster_name)
                smallestIndex = currentIndex;
        }
        swap(monster[startIndex], monster[smallestIndex]);
    }
}

int getMax(MonstersData array[], int n) 
{
    int max = array[0].health_amount;
    for (int i = 1; i < n; i++)
        if (array[i].health_amount > max)
            max = array[i].health_amount;
    return max;
}

void CountingSort(MonstersData* monster, int size, int place, int max)
{
    //cout << "DON" << endl;

    int* count = new int[max];
    MonstersData* output = new MonstersData[size];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // store the count of each element
    for (int i = 0; i < size; i++) {
        count[(monster[i].health_amount / place) % 10]++;
    }

    // store the cummulative count of each array
    for (int i = 1; i < max; i++) {
        //cout << count[i] << endl;
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(monster[i].health_amount / place ) % 10] - 1] = monster[i];
        count[(monster[i].health_amount / place) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        monster[i] = output[i];
    }
}

void SortByHealth(MonstersData* monster, int size)
{
    int max = getMax(monster, size);

    for (int place = 10000; max / place > 0; place *= 10)
        CountingSort(monster, size, place, max+1);
}

void SortByAttacksAmount(MonstersData* monster, int size)
{
    int i = 0;
    int j = size - 1;
    float mid = monster[size / 2].attacks_amount;

    do {
        while (monster[i].attacks_amount < mid) {
            i++;
        }
        while (monster[j].attacks_amount > mid) {
            j--;
        }

        if (i <= j) {
            swap(monster[i], monster[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        SortByAttacksAmount(monster, j + 1);
    }
    if (i < size) {
        SortByAttacksAmount(&monster[i], size - i);
    }
}

void SortByAttackProbability(MonstersData* monster, int size)
{
    int i = 0;
    int j = size - 1;
    float mid = monster[size / 2].attack_probability;

    do {
        while (monster[i].attack_probability < mid) {
            i++;
        }
        while (monster[j].attack_probability > mid) {
            j--;
        }

        if (i <= j) {
            swap(monster[i], monster[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        SortByAttackProbability(monster, j + 1);
    }
    if (i < size) {
        SortByAttackProbability(&monster[i], size - i);
    }
}

void SortByAttackType(MonstersData *monster, int size)
{
    int max = monster[0].special_attack_type;

    // find the largest element of the array
    for (int i = 1; i < size; i++) 
    {
        if (monster[i].special_attack_type > max)
            max = monster[i].special_attack_type;
    }

    int* count = new int[max+1];
    MonstersData* output = new MonstersData[size];

    for (int i = 0; i <= max; ++i)
    {
        count[i] = 0;
    }

    // store the count of each element
    for (int i = 0; i < size; i++) {
        count[monster[i].special_attack_type]++;
    }

    // store the cummulative count of each array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[monster[i].special_attack_type] - 1] = monster[i];
        count[monster[i].special_attack_type]--;
    }

    for (int i = 0; i < size; i++) {
        monster[i] = output[i];
    }
}

bool LessThanMid(DateOfCreation appearance, DateOfCreation mid)
{
    if (appearance.year < mid.year)
        return true;
    else if (appearance.year == mid.year)
    {
        if (appearance.month < mid.month)
            return true;
        else if (appearance.month == mid.month)
        {
            if (appearance.day < mid.day)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool EqualData(DateOfCreation appearance, DateOfCreation mid)
{
    if (appearance.day == mid.day && appearance.month == mid.month && appearance.year == mid.year)
        return true;
    else
        return false;
}

void SortByCreationDate(MonstersData* monster, int size)
{
    int i = 0;
    int j = size - 1;
    DateOfCreation mid = monster[size / 2].apperance_data;

    do {
        while (LessThanMid(monster[i].apperance_data, mid)) {
            i++;
        }
        while (!LessThanMid(monster[j].apperance_data, mid) && !EqualData(monster[j].apperance_data, mid)) {
            j--;
        }

        if (i <= j) {
            swap(monster[i], monster[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        SortByCreationDate(monster, j + 1);
    }
    if (i < size) {
        SortByCreationDate(&monster[i], size - i);
    }
}

void SortVec(int size, vector <MonstersData> monster)
{
    MonstersData* monster_arr = new MonstersData[size];
    for (int i = 0; i < size; i++)
    {
        monster_arr[i] = monster[i];
        cout << "MONSTER ARR " << i << ": \n";
        PrintMonsterInfoArr(monster_arr[i]);
    }

    cout << "Sort by name: " << endl << endl;
    auto begin1vec = std::chrono::high_resolution_clock::now();
    SortByName(size, monster);
    auto end1vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms1vec = end1vec - begin1vec;
    for (int i = 0; i < size; i++)
    {
        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster[i]);
    }
    cout << "The time of name sort: " << (float)elapsed_ms1vec.count() * 1000 << " ms\n\n\n";

    cout << "Sort by health amount: " << endl << endl;
    auto begin6vec = std::chrono::high_resolution_clock::now();
    SortByHealth(monster_arr, size);
    auto end6vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms6vec = end6vec - begin6vec;
    for (int i = 0; i < size; i++)
    {
        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster[i]);
    }
    cout << "The time of health amount sort: " << (float)elapsed_ms6vec.count() * 1000 << " ms\n\n\n";

    cout << "Sort by attacaks amount:" << endl << endl;
    auto begin2vec = std::chrono::high_resolution_clock::now();
    SortByAttacksAmount(monster_arr, size);
    auto end2vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms2vec = end2vec - begin2vec;
    for (int i = 0; i < size; i++)
    {
        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster_arr[i]);
    }
    cout << "The time of attacaks amount sort: " << (float)elapsed_ms2vec.count() * 1000 << " ms\n\n\n";

    cout << "Sort by attacak probability:" << endl << endl;
    auto begin3vec = std::chrono::high_resolution_clock::now();
    SortByAttackProbability(monster_arr, size);
    auto end3vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms3vec = end3vec - begin3vec;
    for (int i = 0; i < size; i++)
    {
        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster_arr[i]);
    }
    cout << "The time of attacaks amount sort: " << (float)elapsed_ms3vec.count() * 1000 << " ms\n\n\n";

    cout << "Sort by super attacak type:" << endl << endl;
    auto begin4vec = std::chrono::high_resolution_clock::now();
    SortByAttackType(monster_arr, size);
    auto end4vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms4vec = end4vec - begin4vec;
    for (int i = 0; i < size; i++)
    {
        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster_arr[i]);
    }
    cout << "The time of super attacak type sort: " << (float)elapsed_ms3vec.count() * 1000 << " ms\n\n\n";

    cout << "Sort by creation date:" << endl << endl;
    auto begin5vec = std::chrono::high_resolution_clock::now();
    SortByCreationDate(monster_arr, size);
    auto end5vec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_ms5vec = end5vec - begin5vec;
    for (int i = 0; i < size; i++)
    {
        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster_arr[i]);
    }
    cout << "The time of creation date sort: " << (float)elapsed_ms3vec.count() * 1000 << " ms\n\n\n";
}

int main()
{
    // getting the vec
    int size = 6;
    vector <MonstersData> monster(size);
    GetVec(size, monster);

    // sorting the elements
    SortVec(size, monster);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
