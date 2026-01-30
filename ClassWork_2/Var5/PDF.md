Почему плохой дизайн:
1. Поля public. Можно обратиться напрямую к возрасту имени и это сломает всю логику. 

Проверку лучше сделать в классе. Почему проверку лучше сделать в классе ? Чтобы в мейне много раз не переписывать одну и туже проверку. Также создать "плохого студента" просто будет невозможно
#include <string>
#include <stdexcept>
class Student 
{
    private:
        std::string name;
        int age;
    public:
    Student(std::string n,int a)
    {
        if (n.size()==0)
        {
             throw std::invalid_argument("Имя не может быть пустым");
        }
        name = n;
        if (a<0)
        {
             throw std::invalid_argument("Возраст не может быть меньше 0");
        }
        age =a;
    }

    std::string get_Name() const 
    {
        return name;
    }

    void set_Age(int a)
    {
       if (a<0)
        {
             throw std::invalid_argument("Возраст не может быть меньше 0");
        }
        age =a;  
    }
    int get_Age() const 
    {
        return age;
    }
};