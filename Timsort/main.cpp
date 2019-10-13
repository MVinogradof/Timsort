#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(nullptr));
    int Array[100];
    for(int i=0; i<100; i++)
    {
        Array[i] = rand()%100;
    }
    for(int i=0; i<100; i++)
    {
        if(i != 0 && i%10 == 0)
            cout << endl;
        cout << Array[i] << ' ';
    }
    return 0;
}
