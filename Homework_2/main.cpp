#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class TaskQueue{
    private:
        vector<int> tasks;
        mutex flag_mtx;
        condition_variable flag_cv;
        bool done = false;
    public:
    // Методы класса push,pop,Done
    //1
    void push(int task)
    {
        {
            unique_lock<mutex> lock(flag_mtx);
            tasks.push_back(task);
        }
        flag_cv.notify_one();
    }
    // 2
    bool pop(int& out)
    {
        unique_lock<mutex> lock(flag_mtx);
        while (tasks.empty() && done==false)
        {
            flag_cv.wait(lock);
        }
        if (!tasks.empty())
        {
            out = tasks.front();
            tasks.erase(tasks.begin());
            return true;
        }
        return false;
    }
    // 3
    void Done()
    {
        {
        unique_lock<mutex> lock(flag_mtx);
        done = true;
        }
        flag_cv.notify_all();
    }
};

void workersFunc(int id,TaskQueue& que, mutex& mtx_out)
{
    int task;
    while(que.pop(task))
    {
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> lock(mtx_out);
        std::cout << "[Worker-" << id << "] обработал задачу " << task << "\n";
    }
}

int main()
{
    const int Num_workers = 4;
    const int Num_tasks = 20;

    TaskQueue queue;
    mutex mtx_out;

    for (int i =1; i <=  Num_tasks;++i)
    {
        queue.push(i);
    }
    vector<thread> workers;
    for (int i =1; i <= Num_workers;++i)
    {
        workers.emplace_back(workersFunc,i,ref(queue),ref(mtx_out));
    }

    queue.Done();

    for (auto& j: workers)
    {
        j.join();
    }
    cout << "\nВсе задачи выполнены!\n";
    return 0;
}