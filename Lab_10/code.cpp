#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>

using namespace std;

template <class T> // Шаги считать
//Структура шага
struct Step
{
    string name;
    function <T(T)> func;
};
// закрыли шаги
template <class T>
class MyPipeLine {
    private:
        vector <Step<T>> steps;
    public:
        MyPipeLine() {}  //конструктор по умолчанию пустой

        size_t size() const             // стандартные методы
        {
            return steps.size();
        }

        bool empty() const
        {                               
            return steps.empty();
        }

        void clear()
        {
            steps.clear();
        }                           // закрыли стандартные методы
        // Добавляем шаги
        template <class F>
            void addStep(const string& newName, F newFunc)
            {
                if (newName=="")
                {
                    throw invalid_argument("Шаг не может быть пустым");
                }
                Step<T> newStep;
                newStep.name = newName;
                newStep.func = newFunc;
                steps.push_back(newStep);
            }
        // Закрыли шаги

        // Убераем шаги
        void removeStep(size_t index)
        {
            if (index >= steps.size())
            {
                throw out_of_range("Индекс улетел");
            }
            steps.erase(steps.begin()+index);
        }   
        // Закончили уборку 

        // Запуск конвейера
        // run покажет только итоговое значение он не покажет шаги
        T run(T value) const {  
            T current = value;
            for (size_t i = 0; i<steps.size();i++)
            {
                current = steps[i].func(current);
            }
            return current;
        }
        // закрыли run


        // Трасировка 
        // trace покажет все преобразования
        vector<T> trace(T value) const
        {
            vector<T> result;
            if (steps.empty()){ return result;}
            T current = value;
            for (size_t i = 0; i<steps.size();i++)
            {
                current = steps[i].func(current);
                result.push_back(current);
            }
            return result;
        }
        // Закрыли trace


        // Перегружаем << через out stream и 
            // лезем в private через friendа//

        friend ostream& operator<<(ostream& outstream , const MyPipeLine<T>& pipeline)
        {
            outstream << "\nКол-во шагов " << pipeline.size() << "\n";
            for (size_t i = 0; i < pipeline.steps.size(); i++)
            {
                outstream << i+1 << ") " << pipeline.steps[i].name << "\n";
            }
            return outstream;
        }
        // Закончили перегрузку
};

int main()
{
    cout <<"\n    Демонстрация MyPipeline<int>    ";
    MyPipeLine<int> intPipe;
    intPipe.addStep("+10",[](int x){return x+10;});
    intPipe.addStep("*8",[](int x){return x*8;});
    intPipe.addStep("-3",[](int x){return x-3;});
    cout << intPipe;

    int start = 10;
    cout << "Старт: " << start << "\n";

    cout << "Результат run(): " << intPipe.run(start) << "\n";
    cout << "Результат trace():" << "\n";
    vector<int> intTrace = intPipe.trace(start);
    for (size_t i = 0;i <intTrace.size();i++)
    {
        cout << "Шаг " << i+1 << ":" << intTrace[i] << "\n";
    }


    cout <<"\n    Демонстрация MyPipeline<string>    \n";
    MyPipeLine<string> stringPipe;
    stringPipe.addStep("дописать что-то",[](string x){return x + "Конец";});
    stringPipe.addStep("преписать что-то",[](string x){return "Начало" + x;});
    stringPipe.addStep("дописать вопросительный знак",[](string x){return x + "?";});
    string first = "Япы";
    cout << "\nСтарт: " << first << "\n";
    cout << "Результат run(): " << stringPipe.run(first) << "\n";



    cout <<"\n    Демонстрация исключений    \n";
    try {
        cout << "Попытка удалить шаг с индексом 100 "<< "\n";
        intPipe.removeStep(100);
    } 
    catch (const out_of_range error) {
        cout << "Перехвачено исключение out_of_range: " << error.what() << "\n";
    }
    return 0;
}