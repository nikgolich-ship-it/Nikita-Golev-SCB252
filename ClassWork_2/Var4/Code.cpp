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
            throw std::runtime_error("Немогу открыть файл");
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