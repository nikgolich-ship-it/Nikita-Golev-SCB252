#include <iostream>
#include <list>
#include <string>
#include <iterator>

using namespace std;

struct Version{
    int number;
    string what;
};
class RevIterator {
private:
    list<Version>::iterator cur;
public:
    RevIterator(list<Version>::iterator i)
    {
        cur = i;
    }
    Version& operator*()
    {
        list<Version>::iterator temp = cur;
        --temp;
        return *temp;
    }
   RevIterator& operator++() {
        --cur;       
        return *this;
    }
    bool operator!=(const RevIterator& other) {
        return cur != other.cur;
    }
};

int main()
{
    list<Version> history;
    int count = 1 ;

    Version v1;
    v1.number = count++;
    v1.what = "Один";
    history.push_back(v1);

    Version v2;
    v2.number = count++;
    v2.what = "Два";
    history.push_back(v2);

    Version v3;
    v3.number = count++;
    v3.what = "Три";
    history.push_back(v3);

    Version v4;
    v4.number = count++;
    v4.what = "Четыре";
    history.push_back(v4);

    RevIterator i(history.end());
    RevIterator end(history.begin());
    while(i!=end)
    {
        Version& v = *i;
         cout << "Версия " << v.number << ": " << v.what << "\n";
        ++i;
    }

    return 0;
}