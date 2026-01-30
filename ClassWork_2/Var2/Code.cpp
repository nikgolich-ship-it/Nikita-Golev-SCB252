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