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

int output(int * Array, int N)
{
    char str[5];    //Строка для преобразования чисел в строки
    for(int i=0; i<N; i++)    //Цикл N раз
    {
        if(i != 0 && i%16 == 0)    //Если в строке 16 эл-тов - перейти на следующую
            cout << endl;
        cout << Array[i];    //Вывести число
        for(int j=0; j<static_cast<int>(5-strlen(itoa(Array[i], str, 10))); j++)    //Вывести столько пробелов, сколько нужно для
            cout << ' ';                                                            //выравнивания строк с числами по левому символу
    }
    cout << endl << "------------------------------------------------------------------------------" << endl << endl;
    return 0;
};

int main()
{
    srand(time(nullptr));    //Инициализация rand() по времени
    int N;
    cout << "Enter array size: ";
    cin >> N;
    int* Array;
    Array = new int[N];
    int i, j, k, l, count = 0, start = 0;
    for(i=0; i<N; i++)
    {
        Array[i] = -99 + rand()%200;    //Генерация массива
    }

    int r = 0, n = N;    //Вычисление minrun
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    int minrun = r + n;
    cout << "minrun: " << minrun << endl << endl;
    cout << "Array:" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    output(Array, N);     //Вывод массива
    stack <run> Stack;
    run CurrentRun;
    for(i=0; i<N; i++)    //Цикл N раз
    {
        if(Array[i] <= Array[i+1])    //Если обнаружен возрастающий run
        {
            start = i;    //Начало с индекса i
            while(Array[i] <= Array[i+1])    //Пока элементы увеличиваются
            {
                count++;    //Увеличивать счетчик элементов
                i++;    //Увеличивать индекс
            }
            count++;
            if(count<=minrun)    //Если размер меньше minrun
            {
                i = i + minrun - count;    //Дополнить длину до minrun, набрав неотсортированных эл-тов
                if(i < N)    //Добавить в стек данные run'а
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
        else    //Аналогично для run, отсортированного в обратном порядке
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
    while(!Stack.empty())    //Переписать данные run'ов из стека в массив
    {
        Runs[i] = Stack.top();
        i--;
        Stack.pop();
    }
    cout << "runs: (start|size)" << endl;    //Вывести данные run'овна экран
    for(i=0; i<count; i++)
    {
        cout << Runs[i].start << ' ' << Runs[i].size << endl;
        Stack.push(Runs[i]);    //Параллельно записать данные обратно в стек
    }

    for(k=0; k<count; k++)    //Сортировка вставками
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
    cout << endl << "Array with sorted runs:" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    output(Array, N);     //Вывод массива

    run X, Y;    //Сливаемые run'ы
    int *temp;    //Указатель на временный массив, в котором будет результат сортировки
    int a, b;
    for(l=0; l<count-1; l++)    //Цикл на (количество run'ов - 1), то есть число слиянй
    {
        Y = Stack.top();    //Верхний эл-т стека - второй массив
        Stack.pop();
        X = Stack.top();    //Предпоследний эл-т стека - первый массив
        Stack.pop();
        int Size = X.size+Y.size;    //Размер результирующего массива
        temp = new int[Size];
        i = 0;
        j = 0;
        for(k=0; k<Size; k++)    //Цикл на размер результирующего массива
        {
            if(i > X.size - 1)    //Если кончился первый массив
            {
                a = Array[Y.start+j];    //Записать в результирующий очередной эл-т второго
                temp[k] = a;
                j++;
            }
            else
            {
                if(j > Y.size - 1)    //Если кончился второй массив
                {
                    a = Array[X.start+i];    //Записать в результирующий очередной эл-т первого
                    temp[k] = a;
                    i++;
                }
                else
                {
                    if(Array[X.start+i] > Array[Y.start+j])    //Если очередной эл-т первого больше
                    {                                          //очередного эл-та второго
                        a = Array[X.start+i];    //Записать в результирующий очередной эл-т первого
                        temp[k] = a;
                        i++;
                    }
                    else    //Если очередной эл-т второго больше или равен очередному эл-ту первого
                    {
                        b = Array[Y.start+j];    //Записать в результирующий очередной эл-т второго
                        temp[k] = b;
                        j++;
                    }
                }
            }
        }
        for(k=0; k<Size; k++)
        {
            Array[X.start+k] = temp[k];    //Переписать временный массив на место первого и второго
        }
        CurrentRun.start = X.start;
        CurrentRun.size = X.size + Y.size;
        Stack.push(CurrentRun);
    }

    cout << "Array with merged sorted runs:" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    output(Array, N);     //Вывод массива

    return 0;
}
