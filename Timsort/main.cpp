#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

using namespace std;

int main()
{
    srand(time(nullptr));
    int Array[SIZE];
    int i, j;
    char str[5];
    for(i=0; i<SIZE; i++)
    {
        Array[i] = -99 + rand()%200;
    }

    int r = 0, n = SIZE;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    int minrun = r + n;
    cout << minrun << endl << endl;

    int currminrun[16][32];
    for(i=0; i<SIZE; i++)
    {
        currminrun[i/32][i%32] = Array[i];
    }

    for(int i=0; i<SIZE; i++)
    {
        if(i != 0 && i%16 == 0)
            cout << endl;
        cout << Array[i];
        for(j=0; j<5-strlen(itoa(Array[i], str, 10)); j++)
            cout << ' ';
    }
    cout << endl <<  "------------------------------------------------------------------------------" << endl;

    for(int k=0; k<16; k++)
    {
        for(i=1;i<32;i++)
        {
            for(j=i; j>0; j--)
            {
                if(currminrun[k][j-1]<currminrun[k][j])
                    break;
                swap(currminrun[k][j-1],currminrun[k][j]);
            }
        }
    }

    for(int k=0; k<16; k++)
    {
        for(j=0; j<32; j++)
        {
            cout << currminrun[k][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
