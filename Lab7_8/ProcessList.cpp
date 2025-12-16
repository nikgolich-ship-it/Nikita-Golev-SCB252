#include "ProcessList.h"
#include <iostream>


ProcessList::ProcessList()
{
    head = nullptr;
}

ProcessList::~ProcessList()
{
    ListNode* current = head;
    while (current!=nullptr)
    {
    ListNode* del = current;
    current = current->next;
    delete del;
    }
}


bool ProcessList::insert(const PCB& newPCB)
{
    ListNode* newOne = new ListNode(newPCB);
    ListNode* current = head;
    if (head != nullptr and  head->data.processID == newPCB.processID)
        {
            return false;
        }
    if (head == nullptr or (head->data.processID) > newPCB.processID)
    {
        newOne->next = head;
        head = newOne;
        return true;
    }
    while (current->next!=nullptr and current->next->data.processID < newPCB.processID)
    {
        current = current ->next;
    }

    if (current->next != nullptr and current->next->data.processID == newPCB.processID)
    {
        delete newOne;
        return false;
    }
    newOne->next = current -> next;
    current->next = newOne;

    return true;
}
bool ProcessList::remove(int id) 
{
    if (head == nullptr)
    {
        return false;
    }
     
    if (head->data.processID == id)
    {
        ListNode* del = head;
        head = head -> next;
        delete del;
        return true;
    }

    ListNode* current = head;

    while (current->next and current->next->data.processID != id)
    {
        current = current->next;
    }
    if (current -> next == nullptr) return false;
    ListNode* del = current->next;
    current->next = del -> next;
    delete del;
    return true;
}

void ProcessList::printList()
{
    if (head == nullptr)
    {
        std::cout << "No process" << std::endl;
        return;
    }
    std::cout << "--- List of processes ---" << std::endl;
    ListNode* current = head;
    while (current != nullptr)
    {
        std::cout << "ID: " << current->data.processID << std::endl;
        std::cout << "Name: " << current->data.processName << std::endl;
        std::cout << "Status: " << current->data.whatStatusIs() << std::endl;
        std::cout << "Command: " << current->data.commandCounter << std::endl;
        current = current->next;
    }

}