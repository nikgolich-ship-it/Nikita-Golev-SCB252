Если написать Buffer b = a программа сломается. Оба объекта (b и a) будут указывать на один и тот же адрес памяти. При удаленни памяти первый объект очистит память ,а второй попробует это сделать ещё раз, что приведёт к ошибке. 

По заданию можно было запретить копирование
Поэтому я запретил копирование вида Buffer b = a
через Buffer(const Buffer&) = delete; и копирование вида b = a при предворительном создании объектов a и b через 
Buffer& operator=(const Buffer&) = delete; 
Вообщем говоря запретил конструктор копирования и оператор присваивания


class Buffer 
{
    int* data;
    int size;
public:
    Buffer(int n) : data(new int[n]), size(n) {}
    ~Buffer() { delete[] data; }


    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
};