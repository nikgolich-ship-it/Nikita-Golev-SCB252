Какие проблемы:
1. Нет деструктора, поэтому fclose никогда не вызывается. Файл остается открытым 
2. В конструкторе нет проверки на fopen. Если файл не откроется то при попытке записи в методе log программа не сработает. 
3. Проблема также с копированием как и в 3 варианте. Так как при копировании два объекта будут владеть адресом указателя , что приведёт к ошибкам. 
#include <cstdio>
#include <stdexcept>

class FileLogger {
    FILE* file;
public:
    FileLogger(const char* name) 
    {
    file = std::fopen(name, "w");
        if (file == nullptr)
        {
            throw std::runtime_error("Не могу открыть файл");
        }
    }
    ~FileLogger()
    {
        if (file != nullptr)
        {
            std::fclose(file);
        }
    }
        void log(const char* msg) {
        std::fputs(msg, file);
        }
        FileLogger(const FileLogger&) = delete;
        FileLogger& operator=(const FileLogger&) = delete;
};