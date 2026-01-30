#include <stdexcept>
#include <vector>
#include <fstream>
using namespace std;
void process(const char* name)
{
    ifstream file(name);

    if (file.is_open()==false)
    {
        throw runtime_error("open failed");
    }
    vector<char> buf(256);
    int c = file.get(); // берём первый символ

    if (c==EOF)
    {
        throw std::runtime_error("empty file");
    }
    // .... Что то тут с ними делаем и нам не надо прописывать delete[] buf; std::fclose(f); 
    // Так как деструктору автоматически вызовутся когда мы из функции выйдем
}