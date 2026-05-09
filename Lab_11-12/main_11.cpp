#include <iostream>
#include <list>

using namespace std;
int main(){
    list<int> prices;
    int input;

    cout << "Введите цены (404 для завершения):\n";
    while (cin >> input && input != 404)
    {
        prices.push_back(input);
    }

    if (prices.empty()) {
        cout << "Список пустой!\n";
        return 0;
    }

    prices.sort(greater<int>());
    cout << "\nДо удаления цен ниже средней :\n";
    for (list<int>::iterator it = prices.begin(); it != prices.end(); ++it) 
    {
        cout << *it << " ";
    }

    double sum = 0;
    for (list<int>::iterator i=prices.begin(); i != prices.end();++i)
    {
        sum+= *i;
    }
    cout <<"\n";

   
    double sr = sum/prices.size();
    cout << "\nСредняя цена: " << sr << "\n";

    list<int>::iterator i=prices.begin();
    while(i != prices.end())
    {
        if (*i < sr)
        {
           i = prices.erase(i);
        }
        else
        {
            ++i;
        }
    }
    cout << "\nПосле удаления цен ниже средней :\n";
    for (list<int>::iterator it = prices.begin(); it != prices.end(); ++it) 
    {
        cout << *it << " ";
    }
    return 0;
}