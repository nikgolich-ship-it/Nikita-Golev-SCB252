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