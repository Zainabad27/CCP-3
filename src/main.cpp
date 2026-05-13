#include <iostream>
#include "Module1.h"
#include "Module2.h"
#include "Module3.h"    


using namespace std;    



int main(){
    // now i want a main menu with 3 options that asks user from console 
    //1: plant management
    //2: Workshop management
    //3: tool benefit calculator

    int choice;
    do
    {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Plant Management\n";
        cout << "2. Workshop Management\n";
        cout << "3. Tool Benefit Calculator\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            Module1();
            break;
        case 2:
            Module2();
            break;
        case 3:
            Module3();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }while (choice != 0);
    


}