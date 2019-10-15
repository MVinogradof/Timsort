#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

using namespace std;

struct run
{
    int start;
    int size;
};

int main()
{
    srand(time(nullptr));
    int N;
    cout << "Enter array size: ";
    cin >> N;
    int* Array;
    Array = new int[N];
    int i, j, k, count = 0, start = 0;
    char str[5];
    for(i=0; i<N; i++)
    {
        Array[i] = -99 + rand()%200;
    }

    int r = 0, n = N;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    int minrun = r + n;
    cout << "minrun: " << minrun << endl << endl;

    for(i=0; i<N; i++)
    {
        if(i != 0 && i%16 == 0)
            cout << endl;
        cout << Array[i];
        for(j=0; j<static_cast<int>(5-strlen(itoa(Array[i], str, 10))); j++)
            cout << ' ';
    }
    cout << endl <<  "------------------------------------------------------------------------------" << endl;

    stack <run> Stack;
    run CurrentRun;
    for(i=0; i<N; i++)
    {
        if(Array[i] <= Array[i+1])
        {
            start = i;
            while(Array[i] <= Array[i+1])
            {
                count++;
                i++;
            }
            count++;
            if(count<=minrun)
            {
                i = i + minrun - count;
                if(i < N)
                {
                    CurrentRun.size = minrun;
                    CurrentRun.start = start;
                    Stack.push(CurrentRun);
                }
                else
                {
                    CurrentRun.size = minrun - (i - N) - 1;
                    CurrentRun.start = start;
                    Stack.push(CurrentRun);
                }
            }
            else
            {
                CurrentRun.size = count;
                CurrentRun.start = start;
                Stack.push(CurrentRun);
            }
            count = 0;
        }
        else
        {
            start = i;
            while(Array[i] > Array[i+1])
            {
                count++;
                i++;
            }
            count++;
            if(count<=minrun)
            {
                i = i + minrun - count;
                if(i < N)
                {
                    CurrentRun.size = minrun;
                    CurrentRun.start = start;
                    Stack.push(CurrentRun);
                }
                else
                {
                    CurrentRun.size = minrun - (i - N) - 1;
                    CurrentRun.start = start;
                    Stack.push(CurrentRun);
                }
            }
            else
            {
                CurrentRun.size = count;
                CurrentRun.start = start;
                Stack.push(CurrentRun);
            }
            count = 0;
        }
    }

    run* Runs;
    Runs = new run[Stack.size()];
    i = count = Stack.size() - 1;
    while(!Stack.empty())
    {
        Runs[i] = Stack.top();
        i--;
        Stack.pop();
    }
    for(i=0; i<=count; i++)
    {
        cout << Runs[i].start << ' ' << Runs[i].size << endl;
    }

    for(k=0; k<=count; k++)
    {
        for(i=1; i<Runs[k].size; i++)
        {
            for(j=i; j>0; j--)
            {
                if(Array[Runs[k].start+j-1]>Array[Runs[k].start+j])
                    break;
                swap(Array[Runs[k].start+j-1],Array[Runs[k].start+j]);
            }
        }
    }

    for(i=0; i<N; i++)
    {
        if(i != 0 && i%16 == 0)
            cout << endl;
        cout << Array[i];
        for(j=0; j<static_cast<int>(5-strlen(itoa(Array[i], str, 10))); j++)
            cout << ' ';
    }
    cout << endl <<  "------------------------------------------------------------------------------" << endl;

    return 0;
}
