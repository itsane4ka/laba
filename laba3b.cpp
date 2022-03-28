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
    unsigned int health_amount;      // 2
    short int attacks_amount;        // 3
    double attack_probability;       // 4
    int special_attack_type;         // 5
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

void MainSorting(int size, vector <MonstersData> &monster)
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

        cout << "MONSTER " << i << ": \n";
        PrintMonsterInfo(monster[i]);
    }
}

int main()
{
    int size = 6;
    vector <MonstersData> monster(size);

    MainSorting(size, monster);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"