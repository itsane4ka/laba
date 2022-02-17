#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

int mercennenew0 ()
{
    random_device rd; 
    mt19937 mersenne(rd()); 
    
    unsigned int ArrayMersenne1[100];
    unsigned int ArrayMersenne2[10000];

    double expected_value = 0;

    double arithmetical_mean1 = 0;
    double arithmetical_mean2 = 0;

    for (int arr_elements = 0; arr_elements < 10000; arr_elements++)
    {
        expected_value += (double) arr_elements / 10000.0;
    }

    int MercRepeat1 = 0, MercRepeat2 = 0;

    for (int count = 0; count < 100; ++count)
    {
        ArrayMersenne1[count] = mersenne()%10000;
        arithmetical_mean1 = arithmetical_mean1 + ArrayMersenne1[count];
        //cout << arithmetical_mean1 << " " << endl;
    }
    arithmetical_mean1 = arithmetical_mean1 / 100;
        
    for (int count = 0; count < 10000; ++count)
    {
        ArrayMersenne2[count] = mersenne()%10000;
        arithmetical_mean2 = arithmetical_mean2 + ArrayMersenne2[count];
        //cout << ArrayMersenne2[count] << " " << expected_value2 << endl;
    }
    arithmetical_mean2 = arithmetical_mean2 / 10000;
        
    for (int i = 0; i < 99; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            if (ArrayMersenne1[i] == ArrayMersenne1[j])
                MercRepeat1++;
        }
    }
    cout << "repetitions amount in SMALL mercenne array " << MercRepeat1 << endl;
    cout << "the repetitions percenatge " << MercRepeat1/100.0 << endl;
    cout << "arithmatical mean (1, 10000) " << arithmetical_mean1 << endl;
    cout << "mathematical prediction " << expected_value << endl << endl;
    
    for (long i = 0; i < 9999; i++)
    {
        for (long j = i + 1; j < 10000; j++)
        {
            if (ArrayMersenne2[i] == ArrayMersenne2[j] && ArrayMersenne2[i] != 0)
            {
                ArrayMersenne2[j] = 0;
                MercRepeat2++;
            }
        }
    }
    cout << "repetitions amount in BIG mercenne array " << MercRepeat2 << endl;
    cout << "the repetitions percenatge " << MercRepeat2/100.0 << endl;
    cout << "arithmatical mean (1, 10000) " << arithmetical_mean2 << endl;
    cout << "mathematical prediction " << expected_value << endl << endl;
    return MercRepeat2;
}

int mercennenew0dist ()
{
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(1,10000);
    
    unsigned int ArrayMersenne1[100];
    unsigned int ArrayMersenne2[10000];
    
    int MercRepeatDist1 = 0, MercRepeatDist2 = 0;

    for (int count = 0; count < 100; ++count)
        ArrayMersenne1[count] = dist(gen);
        
    for (int count = 0; count < 10000; ++count)
        ArrayMersenne2[count] = dist(gen);
        
    for (int i = 0; i < 99; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            if (ArrayMersenne1[i] == ArrayMersenne1[j])
                MercRepeatDist1++;
        }
    }
    cout << "repetitions amount in SMALL mercenne-dist array " << MercRepeatDist1 << endl;
    cout << "the repetitions percenatge " << MercRepeatDist1 << endl << endl;
    
    for (long i = 0; i < 9999; i++)
    {
        for (long j = i + 1; j < 10000; j++)
        {
            if (ArrayMersenne2[i] == ArrayMersenne2[j] && ArrayMersenne2[i] != 0)
            {
                ArrayMersenne2[j] = 0;
                MercRepeatDist2++;
            }
        }
    }
    cout << "repetitions amount in BIG mercenne-dist array " << MercRepeatDist2 << endl;
    cout << "the repetitions percenatge " << MercRepeatDist2/100.0 << endl<< endl << endl;
    return MercRepeatDist2;
}

int mercennenew ()
{
    random_device rd; 
    mt19937 mersenne(rd()); 
    
    unsigned int ArrayMersenne1[100];
    unsigned int ArrayMersenne2[10000];
    
    int MercRepeat1 = 0, MercRepeat2 = 0;

    for (int count = 0; count < 100; ++count)
        ArrayMersenne1[count] = mersenne()%10000;
        
    for (int count = 0; count < 10000; ++count)
        ArrayMersenne2[count] = mersenne()%10000;
        
    for (int i = 0; i < 99; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            if (ArrayMersenne1[i] == ArrayMersenne1[j])
                MercRepeat1++;
        }
    }
    for (long i = 0; i < 9999; i++)
    {
        for (long j = i + 1; j < 10000; j++)
        {
            if (ArrayMersenne2[i] == ArrayMersenne2[j] && ArrayMersenne2[i] != 0)
            {
                ArrayMersenne2[j] = 0;
                MercRepeat2++;
            }
        }
    }
    return MercRepeat2;
}

int srandom0 ()
{
    srand(static_cast<unsigned int>(time(0)));
    
    unsigned int ArraySrand1[100];
    unsigned int ArraySrand2[10000];
    
    int SrandRepeat1 = 0, SrandRepeat2 = 0;

    for (int count = 0; count < 100; ++count)
        ArraySrand1[count] = rand()%10000;
        
    for (int count = 0; count < 10000; ++count)
        ArraySrand2[count] = rand()%10000;
        
        
    for (int i = 0; i < 99; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            if (ArraySrand1[i] == ArraySrand1[j])
                SrandRepeat1++;
        }
    }
    cout << "repetitions amount in SMALL srand array " << SrandRepeat1 << endl;
    cout << "the repetitions percenatge " << SrandRepeat1 << endl << endl;
    
    for (int i = 0; i < 9999; i++)
    {
        for (int j = i + 1; j < 10000; j++)
        {
            if (ArraySrand2[i] == ArraySrand2[j] && ArraySrand2[i] != 0)
            {
                ArraySrand2[j] = 0;
                SrandRepeat2++;
            }
        }
    }
    cout << "repetitions amount in BIG srand array " << SrandRepeat2 << endl;
    cout << "the repetitions percenatge " << SrandRepeat2/100.0 << endl << endl << endl;
    return SrandRepeat2;
}


int srandom ()
{
    srand(static_cast<unsigned int>(time(0)));
    
    unsigned int ArraySrand1[100];
    unsigned int ArraySrand2[10000];
    
    int SrandRepeat1 = 0, SrandRepeat2 = 0;

    for (int count = 0; count < 100; ++count)
        ArraySrand1[count] = rand()%10000;
        
    for (int count = 0; count < 10000; ++count)
        ArraySrand2[count] = rand()%10000;
        
        
    for (int i = 0; i < 99; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            if (ArraySrand1[i] == ArraySrand1[j])
                SrandRepeat1++;
        }
    }
    for (int i = 0; i < 9999; i++)
    {
        for (int j = i + 1; j < 10000; j++)
        {
            if (ArraySrand2[i] == ArraySrand2[j] && ArraySrand2[i] != 0)
            {
                ArraySrand2[j] = 0;
                SrandRepeat2++;
            }
        }
    }
    return SrandRepeat2;
}


int main()
{
    int num1[10] = {}, num2[10] = {};
    
    cout << "EXAMPLE of program work" << endl << endl;

    cout << "1: mersenne\n";

    auto begin_mersenne = std::chrono::steady_clock::now();
    mercennenew0();
    auto end_mersenne = std::chrono::steady_clock::now();
    auto elapsed_ms_mersenne = std::chrono::duration_cast<std::chrono::milliseconds>(end_mersenne - begin_mersenne);
    cout << "The time of c++ randomisimg(1): " << (float)elapsed_ms_mersenne.count() / 1000.0 << " s\n\n\n\n";

    cout << "2: gen (using dist)\n";
    auto begin_mersenne_dist = std::chrono::steady_clock::now();
    mercennenew0dist();
    auto end_mersenne_dist = std::chrono::steady_clock::now();
    auto elapsed_ms_mersenne_dist = std::chrono::duration_cast<std::chrono::milliseconds>(end_mersenne_dist - begin_mersenne_dist);
    cout << "The time of c++ randomisimg(2): " << (float)elapsed_ms_mersenne_dist.count() / 1000.0 << " s\n\n\n\n";

    cout << "3: srand\n";
    auto begin_srand = std::chrono::steady_clock::now();
    srandom0();
    auto end_srand = std::chrono::steady_clock::now();
    auto elapsed_ms_srand = std::chrono::duration_cast<std::chrono::milliseconds>(end_srand - begin_srand);
    cout << "The time of c randomisimg: " << (float)elapsed_ms_srand.count() / 1000.0 << " s\n\n\n\n";

    cout << endl;
    
    int DiffCounter = 0, flag = 0;
    for (int p = 0; p < 10; p++)
    {
        num1[p] = mercennenew();
        num2[p] = srandom();
        
        cout << p << ": reperations difference equls " << num2[p] - num1[p] << " for 10.000 elements";
        flag = num2[p] - num1[p];
        DiffCounter += flag;
        cout << endl;
    }
    
    cout << "avarege difference equals " << DiffCounter/10 << endl;
    return 0;
}











