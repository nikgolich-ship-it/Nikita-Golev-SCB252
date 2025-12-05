#include <iostream>
using namespace std;

void inputData(float** p, int d , int h)
{
    for (int i = 0;i<d;i++)
    {
        cout << "День" << i+1 << ":";
        for (int j = 0;j<h;j++)
        {
            while (true)
            {
                if (!(cin >> *(*(p+i)+j)))
                {
                    cin.clear();
                    cin.ignore(252,'\n');
                    cout << "Число";
                    continue;
                }
                if (*(*(p+i)+j) < -50 or *(*(p+i)+j) > 50)
                {
                    cout << "Числа в диапозоне от -50 до +50 ";
                    continue;
                }
                break;
            }
        }
    }
}
float dayOverage(float* row,int h)
{
    float sum = 0;
    for (int i = 0;i<h;i++)
    {
        sum+=*(row+i);
    }
    return sum / h;
}

float overallAverage(float** p,int d,int h)
{
    float sum = 0;
    for (int i = 0;i<d;i++)
    {
        for (int j = 0;j<h;j++)
        {
            sum += *(*(p+i)+j);
        }
    }
    return sum /(d*h);
}

void showHotDays(float** p, int d, int h)
{
    float srznach = overallAverage(p,d,h);
    cout << "Общая средняя температура:" << srznach << endl;
    cout << "Теплые дни:" << endl;
    for (int i = 0; i < d ; i++)
    {
        float srday = dayOverage(*(p+i),h);
        if (srday > srznach)
        {
            cout << "День" << i+1 << "(среднее = " << srday << ")" << endl;
        }
    }
}
int main()
{
cout << "=== Анализ температурных датчиков ===\n";
int d,h;
cout << "Введите количество дней: ";

while (true)
{
    if (!(cin >> d)) {
        cin.clear();
        cin.ignore(252, '\n');
        cout << "Введите целое число от 1 до 30: ";
        continue;
    }
    if (d < 1 || d > 30) {
        cin.ignore(252, '\n');
        cout << "Введите целое число от 1 до 30: ";
        continue;
    }
    cin.ignore(252, '\n');
    break;
}
cout << "Введите количество измерений: ";
while (true)
{
    if (!(cin >> h)) {
        cin.clear();
        cin.ignore(252, '\n');
        cout << "Введите целое число от 1 до 24: ";
        continue;
    }

    if (h < 1 || h > 24) {
        cin.ignore(252, '\n');
        cout << "Введите целое число от 1 до 24: ";
        continue;
    }
    cin.ignore(252, '\n');
    break;
}
float** data = new float*[d];
for (int i = 0 ; i<d;i++)
{
    data[i] = new float[h];
}
cout << "Введите значения температуры:\n";
inputData(data,d,h);
showHotDays(data,d,h);
for (int i = 0 ; i<d;i++)
{
    delete[] data[i];
}
delete[] data;
return 0;
}
