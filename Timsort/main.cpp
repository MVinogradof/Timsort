#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
    srand(time(nullptr));
    int Array[256];
    int i, j;
    char str[5];
    for(i=0; i<256; i++)
    {
        Array[i] = -99 + rand()%200;
    }
    for(int i=0; i<256; i++)
    {
        if(i != 0 && i%16 == 0)
            cout << endl;
        cout << Array[i];
        for(j=0; j<5-strlen(itoa(Array[i], str, 10)); j++)
            cout << ' ';
    }
    return 0;
}
