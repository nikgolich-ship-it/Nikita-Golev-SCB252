Перепроектирую


#include <stdexcept>


class Range
{
    private:
    int low_c;
    int high_c;
    public:

    Range (int low,int high)
    {
        if (low > high)
        {
            throw std::invalid_argument("Low должно быть меньше High");
        }
        low_c= low;
        high_c= high;
    }

    int low() const{
        return low_c;
    }
    int high() const{
        return high_c;
    }
    // по заданию нужно именно так написать но можно и getHigh() и getLow()
    bool contains(int value) const
    {
        return (value >= low_c and value<=high_c);

    }
};


Условие корректности которое должно выполняться:
(value >= low and value<=high) и low <= high, которая проверяется постредством if (low > high)
throw std::invalid_argument("Low должно быть меньше High");

Закрыл поля и положил low_с и high_с в приват чтоб их никто не мог изменить и они были защищены,добавил методы low() и high() для чтения данных.
Проверки должны быть внутри класса чтоб не повторять проверки много раз. Также сломать данные (сделать low больше high) физически невозможно будет. 