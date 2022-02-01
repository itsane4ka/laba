// list.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>

#define TRUE 1;
#define FALSE 0;

using namespace std;

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

struct Place {
    string place_name;
    int place_square;
    int max_amount_of_monsters;
};

struct MonstersData {
    string monster_name;
    unsigned int health_amount;
    short int attacks_amount;
    float attack_probability;
    int special_attack_type;
    DateOfCreation apperance_data;
    TimeOfCreation time_of_creation;
    Place Place;
    long long id;
};


void PrintMonsterInfo(MonstersData monster)
{
    cout << "Name: " << monster.monster_name << "\n";
    cout << "Health amount: " << monster.monster_name << "\n";
    cout << "Attacks amount: " << monster.health_amount << "\n";
    cout << "Attack probability: " << monster.attacks_amount << "\n"; // 0<=attack.probability<=1
    cout << "Special attack type: " << monster.attack_probability << "\n";  // 1 - увеличить урон 2 - повторить атаку 3 - вылечить себя 4 - парализовать соперника
    cout << "Appereance data: " << monster.apperance_data.day << "." << monster.apperance_data.month << "." << monster.apperance_data.year << "\n";
    cout << "Appereance timing: " << monster.time_of_creation.hour << ":" << monster.time_of_creation.minute << ":" << monster.time_of_creation.second << endl << endl;
}

MonstersData AddElements(MonstersData mon1, MonstersData mon2)
{
    //name
    MonstersData mon14;
    mon14.id = 1;
    mon14.monster_name = mon1.monster_name + mon2.monster_name;

    //health
    mon14.health_amount = mon1.health_amount + mon2.health_amount;

    //attacks_amounts
    mon14.attacks_amount = mon1.attacks_amount + mon2.attacks_amount;

    //attacks probability
    mon14.attack_probability = mon1.attack_probability + mon2.attack_probability;

    //date
    mon14.apperance_data = {0, 0, 0};

    mon14.apperance_data.day = mon1.apperance_data.day + mon2.apperance_data.day;
    if (mon14.apperance_data.day > 31)
    {
        mon14.apperance_data.month++;
        mon14.apperance_data.day = mon14.apperance_data.day % 31;
    }
    mon14.apperance_data.month = mon1.apperance_data.month + mon2.apperance_data.month;
    if (mon14.apperance_data.month > 12)
    {
        mon14.apperance_data.year++;
        mon14.apperance_data.month = mon14.apperance_data.month % 12;
    }
    mon14.apperance_data.year = mon1.apperance_data.year + mon2.apperance_data.year;

    //timing
    mon14.time_of_creation = {0, 0, 0};

    mon14.time_of_creation.second = mon1.time_of_creation.second + mon2.time_of_creation.second;
    if (mon14.time_of_creation.second >= 60)
    {
        mon14.time_of_creation.minute++;
        mon14.time_of_creation.second = mon14.time_of_creation.second % 60;
    }
    mon14.time_of_creation.minute = mon1.time_of_creation.minute + mon2.time_of_creation.minute;
    if (mon14.time_of_creation.minute >= 60)
    {
        mon14.time_of_creation.hour++;
        mon14.time_of_creation.minute = mon14.time_of_creation.minute % 60;
    }
    mon14.time_of_creation.hour = (mon1.time_of_creation.hour + mon2.time_of_creation.hour) % 24;

    return mon14;
}

void Search_Name_That_Contents_Text(string text, MonstersData monsters[], int AmountOfMonsters)
{
    int counter = 0;
    for (int i = 0; i < AmountOfMonsters; i++)
    {
        for (int j = 0; j < monsters[i].monster_name.length(); j++)
        {
            if (monsters[i].monster_name[j] == text[counter])
            {
                if (counter == text.length()-1)
                {
                    cout << "monster " << i+1 << " " << monsters[i].monster_name << " name contains your text" << endl;
                    break;
                }
                counter++;
            }
            else
            {
                counter = 0;
            }
        }
    }
}

void Search_Attack_Type_And_Amount_Of_Attacks_Range(int min, int max, int attacktype, MonstersData monsters[], int AmountOfMonsters)
{
    for (int i = 0; i < AmountOfMonsters; i++)
    {
        if (monsters[i].special_attack_type == attacktype && monsters[i].attacks_amount <= max && monsters[i].attacks_amount >= min)
        {
            cout << "monster " << i+1 << " has 3 type of super attack and his"
                << " attacks amount is " << monsters[i].attacks_amount << " from 500 to 1500" << endl << endl;
        }
    }
}

void Search_After_Timing(TimeOfCreation key, MonstersData monsters[], int AmountOfMonsters)
{
    for (int i = 0; i < AmountOfMonsters; i++)
    {
        if (monsters[i].time_of_creation.hour <= key.hour)
        {
            cout << "monster " << i + 1 << " appeared not after key timing" << endl;
            continue;
        }
        else if (monsters[i].time_of_creation.hour == key.hour)
        {
            if (monsters[i].time_of_creation.minute <= key.minute)
            {
                cout << "monster " << i + 1 << " appeared not after key timing" << endl;
                continue;
            }
            else if (monsters[i].time_of_creation.minute == key.minute)
            {
                if (monsters[i].time_of_creation.second <= key.second)
                {
                    cout << "monster " << i + 1 << " appeared not after key timing" << endl;
                    continue;
                }
            }
        }
    }
}

void Additional_Search(int S_min, int S_max, int specail_attack_type, int super_attack_chance, MonstersData monsters[], int AmountOfMonsters)
{
    for (int i = 0; i < AmountOfMonsters; i++)
    {
        if (monsters[i].Place.place_square <= S_max && monsters[i].Place.place_square >= S_min && monsters[i].special_attack_type == specail_attack_type && super_attack_chance >= super_attack_chance)
        {
            cout << "place " << monsters[i].Place.place_name << " satisfies the conditions" << endl;
        }
    }
}

void WiteIntoFile(ofstream& fout, MonstersData monsters[], int AmountOfMonsters)
{
    for (int i = 0; i < AmountOfMonsters; i++)
    {
        fout << "Name: " << monsters[i].monster_name << "\n";
        fout << "Health amount: " << monsters[i].health_amount << "\n";
        fout << "Attacks amount: " << monsters[i].attacks_amount << "\n";
        fout << "Attack probability: " << monsters[i].attack_probability << "\n"; // 0<=attack.probability<=1
        fout << "Special attack type: " << monsters[i].special_attack_type << "\n";  // 1 - увеличить урон 2 - повторить атаку 3 - вылечить себя 4 - парализовать соперника
        fout << "Appereance data: " << monsters[i].apperance_data.day << "." << monsters[i].apperance_data.month << "." << monsters[i].apperance_data.year << "\n";
        fout << "Appereance timing: " << monsters[i].time_of_creation.hour << ":" << monsters[i].time_of_creation.minute << ":" << monsters[i].time_of_creation.second << endl << endl;
    }
}

void CreateRandomMonsters(MonstersData &monsters_rand, int AmountOfMonsters)
{
    srand(time(0));
    int name_length = rand() % 10;
    for (int i = 0; i < name_length; i++)
    {
        monsters_rand.monster_name = monsters_rand.monster_name + (char)('A' + rand() % 26) ;
    }
    monsters_rand.health_amount = rand() % 50000;
    monsters_rand.attacks_amount = rand() % 2000;
    monsters_rand.attack_probability = rand() % RAND_MAX;
    monsters_rand.special_attack_type = rand() % 4;
    monsters_rand.apperance_data.year = rand() % 3000;
    monsters_rand.apperance_data.month = rand() % 12;
    monsters_rand.apperance_data.day = rand() % 31;
    monsters_rand.time_of_creation.hour = rand() % 24;
    monsters_rand.time_of_creation.minute = rand() % 60;
    monsters_rand.time_of_creation.second = rand() % 60;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "rus");

    //GAME START
    int FirstAction;
    cout << "1 - interactive dialog mode\n2 - demonstraion\n3 - banchmark" << endl << endl;
    cin >> FirstAction;
    cout << endl;

    // определяем монстров
    const int AmountOfMonsters = 4;
    MonstersData monsters[4];

    monsters[0] = { "Mike", 20000, 150, 0.6, 1, {31, 01, 2020}, {23, 04, 50}, {"desert", 500, 4}, 0 };
    monsters[1] = { "Tom", 35000, 2000, 0.3, 3, {24, 03, 2022} , {04, 30, 40}, {"lake", 560, 2}, 0 };
    monsters[2] = { "Alex", 10220, 1000, 0.1, 3, {15, 02, 2022}, {10, 00, 10}, {"ocaen", 240, 6}, 0 };
    monsters[3] = { "Looserik", 5500, 560, 0.4, 4, {23, 05, 2023}, {16, 17, 00}, {"space", 5000, 3}, 0 };

    if (FirstAction == 1)
    {
        //interactive dialog mode
        
        cout << "now choose the option you want to check" << endl;
        cout << "1 - add elements" << endl;
        cout << "2 - print info to the file" << endl;
        cout << "3 - get data from the file" << endl;
        cout << "4 - print info to the console" << endl;
        cout << "5 - search (4)" << endl << endl;

        int SecondOption;
        cin >> SecondOption;
        if (SecondOption == 1)
        {
            cout << "enter which monsters' info u wonna add (2 num)" << endl; // 1 <= index <= 4
            int index1, index2;
            cin >> index1 >> index2;
            MonstersData mon = AddElements(monsters[index1-1], monsters[index2-1]);
            PrintMonsterInfo(mon);
        }
        else if (SecondOption == 2)
        {
            cout << "enter the file name" << endl;
            string file_name1;
            cin >> file_name1; //file.txt

            ofstream fout(file_name1, ios_base::out, ios_base::trunc);
            WiteIntoFile(fout, monsters, AmountOfMonsters);
        }
        else if (SecondOption == 3)
        {
            string file_name2;
            cin >> file_name2; //inputfile.txt
            ifstream fin(file_name2);
            string buff;

            if (!fin.is_open())
                cout << "Файл не может быть открыт!\n\n";
            else
            {
                while (getline(fin, buff))
                {
                    cout << buff << endl;
                }
                fin.close(); // закрываем файл
                cout << buff << endl;
            }
        }
        else if (SecondOption == 4)
        {
            cout << "enter which monster's info you want" << endl;
            int index3;
            cin >> index3;
            PrintMonsterInfo(monsters[index3-1]);
        }
        else if (SecondOption == 5)
        {
            cout << "searching options:" << endl;
            cout << "1 - name that contains your entered text" << endl;
            cout << "2 - have your mentioned attack type and amount of attacks in your entered range" << endl;
            cout << "3 - monsters that appeared in the game after your entered timing" << endl << endl;

            int ThirdAction;
            cin >> ThirdAction; // 1 <= 3action <=3

            if (ThirdAction == 1)
            {
                cout << "enter which str you want to find" << endl;
                string keystr;
                cin >> keystr;
                Search_Name_That_Contents_Text(keystr, monsters, AmountOfMonsters);
                cout << endl;
            }
            else if (ThirdAction == 2)
            {
                cout << "enter the min amount of attacks" << endl;
                int minattacks;
                cin >> minattacks;
                
                cout << "enter the max amount of attacks" << endl;
                int maxattacks;
                cin >> maxattacks;

                cout << "enter the super attack type" << endl;
                int superattack;
                cin >> superattack;

                Search_Attack_Type_And_Amount_Of_Attacks_Range(minattacks, maxattacks, superattack, monsters, AmountOfMonsters);
            }
            else if (ThirdAction == 3)
            {
                cout << "lets find the monster that appeared after key time" << endl;
                TimeOfCreation key = { 0, 0, 0 };
                cout << "enter the key time (hours)" << endl;
                cin >> key.hour;
                cout << "enter the key time (mins)" << endl;
                cin >> key.minute;
                cout << "enter the key time (seconds)" << endl;
                cin >> key.second;
                Search_After_Timing(key, monsters, AmountOfMonsters);
            }
            else if (ThirdAction == 4)
            {
                cout << "\nadditional task:" << endl;
                cout << "\nlets find the monsters by location and other charactistics" << endl << endl;
                cout << "enter the min square" << endl;
                int minsquare;
                cin >> minsquare;
                cout << "enter the max square" << endl;
                int maxsquare;
                cin >> maxsquare;
                cout << "enter the super attack num" << endl;
                int superattack;
                cin >> superattack;
                cout << "enter the super attack probability" << endl;
                int superattackprobability;
                cin >> superattackprobability;
                Additional_Search(minsquare, maxsquare, superattack, superattackprobability, monsters, AmountOfMonsters);
            }
            else
                cout << "you choosed the wrong number" << endl;
        }
        else
            cout << "you choosed the wrong number" << endl;
    }
    else if (FirstAction == 2)
    {
        //emonstrational mode
        cout << "there are 5 options" << endl;
        cout << "1 - add elements" << endl;
        cout << "2 - print info to the file" << endl;
        cout << "3 - get data from the file" << endl;
        cout << "4 - print info to the console" << endl;
        cout << "5 - search (4)" << endl << endl;

        //print data (4)
        cout << "option number 4: print data" << endl;
        cout << "lets see the result" << endl << endl;
        for (int i = 0; i < AmountOfMonsters; i++)
        {
            PrintMonsterInfo(monsters[i]);
        }

        //add elements (1)
        cout << "option number 1: add el" << endl;
        cout << "lets see the res of 1 and 4 mon addition" << endl << endl;
        MonstersData mon = AddElements(monsters[0], monsters[3]);
        PrintMonsterInfo(mon);
        cout << "lets see the res of 2 and 3 mon addition" << endl << endl;
        AddElements(monsters[1], monsters[2]);
        cout << endl;

        // write info into file (2)
        ofstream fout;
        fout.open("fileoutput.txt", ios_base::out);
        if (!fout.is_open())
        {
            cout << "errror file not found" << endl;
            return 0;
        }
        cout << "option number 2: print info to the file" << endl;
        cout << "the program wrote every monsters info into file.txt" << endl << endl;
        fout << "\t\t" << "welcome" << endl;
        WiteIntoFile(fout, monsters, AmountOfMonsters);

        // get info from the file (3)
        ifstream fin("fileinput.txt");
        string buff;

        cout << "option number 3: get data from the file" << endl << endl;
        if (!fin.is_open()) 
            cout << "Файл не может быть открыт!\n\n";
        else
        {
            while (getline(fin, buff))
            {
                cout << buff << std::endl;
            }
            fin.close(); // закрываем файл
            cout << buff << endl;
        }

        //search for your criteria (5)
        cout << "option number 5: search el" << endl;
        cout << "searching options:" << endl;
        cout << "1 - name that contains your entered text" << endl;
        cout << "2 - have your mentioned attack type and amount of attacks in your entered range" << endl;
        cout << "3 - monsters that appeared in the game after your entered timing" << endl << endl;
        // num 1
        cout << "lets find text 'ik' " << endl << endl;
        Search_Name_That_Contents_Text("ik", monsters, AmountOfMonsters);
        cout << endl;
        // num 2
        cout << "lets find attack type 3 and amount of attacks in range of 500 to 1500" << endl << endl;
        Search_Attack_Type_And_Amount_Of_Attacks_Range(500, 1500, 3, monsters, AmountOfMonsters);
        // num 3
        cout << "lets find the monster that appeared after 16.40.00" << endl << endl;
        TimeOfCreation key = {16, 40, 00};
        Search_After_Timing(key, monsters, AmountOfMonsters);
        //num 4 (ADDITIONAL)
        cout << "\nadditional task:" << endl;
        cout << "\nlets find the monsters by location and other charactistics" << endl << endl;
        Additional_Search(50, 4000, 3, 0.4, monsters, AmountOfMonsters);
    }
    else if (FirstAction == 3)
    {
        //benchmark mode
        int N = 10;
        unsigned int start_time = 0;
        unsigned int end_time = 0;
        unsigned int search_time = 0;

        ofstream fout;
        fout.open("fileoutput.txt", ios_base::out);

        while (search_time / 1000.0 < 10.0000)
        {
            start_time = clock();

            cout << N << endl;
            MonstersData* monsters_rand = new MonstersData[N+N*N];
            for (int i = 0; i < N; i++)
            {
                CreateRandomMonsters(*monsters_rand, N);
                for (int j = 0; j < N; j++)
                {
                    monsters_rand[i*j] = AddElements(monsters_rand[i], monsters_rand[j]);
                }
                WiteIntoFile(fout, monsters_rand, N + N * N);
            }

            end_time = clock();
            search_time = end_time - start_time;
            if (search_time / 1000.0 > 1.000)
            {
                N = N + 5;
            }
            else
            {
                N = N + 10;
            }
        }
    }
    else
    {
        cout << "error, you choosed a wrong number";
    }
    return 0;
}




// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
