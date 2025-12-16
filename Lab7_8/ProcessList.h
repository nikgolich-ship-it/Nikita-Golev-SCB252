#ifndef ProcessListh
#define ProcessListh
#include <iostream>
#include <string>

enum processStatus
{
    Running, //типо 0
    Waiting, // 1
    Stopped // 2
};
struct PCB {int processID;std::string processName ;
    processStatus status; int  commandCounter;
                int cpuRegisters[4];

    std::string whatStatusIs() const 
    {
        switch (status)
        {
            case Running : return "Running";
            case Waiting : return "Waiting";
            case Stopped : return "Stopped";
            default : return "HZ";
        }
        
    }
};
class ListNode
{
public :
    PCB data;
    ListNode* next;
    ListNode(PCB pcb)
    {
        data = pcb;
        next = nullptr;
    }
};

class ProcessList
{
    private:

    ListNode* head;
    
    public :
    ProcessList();
    ~ProcessList();

    bool insert(const PCB& newPCB);
    bool remove(int pid);
    void printList();
};
#endif