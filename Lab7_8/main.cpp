#include <iostream>
#include "ProcessList.h"
#include <limits>
int vvod_and_durak()
{
    int a;
    while (true)
    {
        std::cin >> a;
        if (std::cin.fail()==true)
        {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout << "Wrong input. Please enter a number: ";
        }
        else{
            std::cin.ignore(1000,'\n');
            return a;
        }
    }
}
int main()
{
    ProcessList function;
    int choice;

    while (true)
    {
        std::cout << "    PROCESS MANAGER    " << std::endl;
        std::cout << "1. Add process" << std::endl;
        std::cout << "2. Remove process" << std::endl;
        std::cout << "3. Show list" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Your choice: " << std::endl;
        choice = vvod_and_durak();

        if (choice == 0)
        {
            std::cout << "Program was closed." << std::endl;
            break;
        }
        switch (choice)
        {
            case 1:
            {
                PCB newPCB;
                int statusIn;

                std::cout << "--- Add Process ---" << std::endl;
                std::cout << "Enter Id: ";
                newPCB.processID = vvod_and_durak();

                std::cout << "Enter Name: ";
                std::cin >> newPCB.processName;


                std::cout << "What Status(Run,Wait or Stop (0,1,2) for each other): ";
                statusIn = vvod_and_durak();

               if (statusIn < 0 || statusIn > 2) {
                    std::cout << "Error! Invalid status they must be 0, 1 or 2" << std::endl;
                    break; 
                }
                newPCB.status = (processStatus)statusIn;

                std::cout << "Enter command counter (number): ";
                newPCB.commandCounter = vvod_and_durak();

                for(int i=0; i<4; i++) 
                {
                    newPCB.cpuRegisters[i] = 0;
                }
                if (function.insert(newPCB) == true)
                {
                   std::cout << "Success, process added" << std::endl;
                } else 
                {
                    std::cout << "Error,process with this ID already exists"<< std::endl;
                }
                break;
            } 
                case 2:
                {
                    int delId;
                    std::cout << "Remove Process" << std::endl;
                    std::cout << "Enter ID for removing: ";
                    delId = vvod_and_durak();
                    if (function.remove(delId)) 
                    {
                        std::cout << "Process removed." << std::endl;
                    } else 
                    {
                        std::cout << "Error! Process with ID " << delId << " was not found" << std::endl;
                    }
                    break;
                }
                case 3:
                {
                    function.printList();
                    break;
                }
                default:
                    std::cout << "Wrong command. Try again" << std::endl;
            }
        }
    return 0;
}