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
    int i, j, k, l, count = 0, start = 0;
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
    cout << "Array:" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    for(i=0; i<N; i++)
    {
        if(i != 0 && i%16 == 0)
            cout << endl;
        cout << Array[i];
        for(j=0; j<static_cast<int>(5-strlen(itoa(Array[i], str, 10))); j++)
            cout << ' ';
    }
    cout << endl << "------------------------------------------------------------------------------" << endl << endl;

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
    i = Stack.size() - 1;
    count = Stack.size();
    while(!Stack.empty())
    {
        Runs[i] = Stack.top();
        i--;
        Stack.pop();
    }
    cout << "runs: (start|size)" << endl;
    for(i=0; i<count; i++)
    {
        cout << Runs[i].start << ' ' << Runs[i].size << endl;
        Stack.push(Runs[i]);
    }
    cout << endl << "Array with sorted runs:" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    for(k=0; k<count; k++)
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
    cout << endl << "------------------------------------------------------------------------------" << endl << endl;

    run X, Y;
    int *temp;
    int a, b;
    for(l=0; l<count-1; l++)
    {
        Y = Stack.top();
        Stack.pop();
        X = Stack.top();
        Stack.pop();
        int Size = X.size+Y.size;
        temp = new int[Size];
        i = 0;
        j = 0;
        for(k=0; k<Size; k++)
        {
            if(i > X.size - 1)
            {
                a = Array[Y.start+j];
                temp[k] = a;
                j++;
            }
            else
            {
                if(j > Y.size - 1)
                {
                    a = Array[X.start+i];
                    temp[k] = a;
                    i++;
                }
                else
                {
                    if(Array[X.start+i] > Array[Y.start+j])
                    {
                        a = Array[X.start+i];
                        temp[k] = a;
                        i++;
                    }
                    else
                    {
                        b = Array[Y.start+j];
                        temp[k] = b;
                        j++;
                    }
                }
            }
        }
        for(k=0; k<Size; k++)
        {
            Array[X.start+k] = temp[k];
        }
        CurrentRun.start = X.start;
        CurrentRun.size = X.size + Y.size;
        Stack.push(CurrentRun);
    }

    cout << "Array with merged sorted runs:" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    for(i=0; i<N; i++)
    {
        if(i != 0 && i%16 == 0)
            cout << endl;
        cout << Array[i];
        for(j=0; j<static_cast<int>(5-strlen(itoa(Array[i], str, 10))); j++)
            cout << ' ';
    }
    cout << endl << "------------------------------------------------------------------------------" << endl;

    return 0;
}
