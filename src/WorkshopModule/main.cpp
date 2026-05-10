#include <iostream>
#include <unordered_map>
#include <string>
#include "Tree.h"
using namespace std;

struct workshop
{
    string GardenerName;
    string GardenerExpertise;
    string date;
    int slots;
};

void addAWorkshop(unordered_map<string, workshop> &workshops,unordered_map<string, AVLTree> workshopRegistrations, string workshopName,workshop w)
{
    workshops[workshopName] = w;
    workshopRegistrations[workshopName] = AVLTree();

}

void bookSeat(unordered_map<string, workshop> &workshops, string workshopName, registration regis, unordered_map<string, AVLTree> &workshopRegistrations)
{
    if (workshops.find(workshopName) == workshops.end())
    {
        cout << "Workshop not found.\n";
        return;
    }

    if (workshops[workshopName].slots < regis.seatsBooked)
    {
        cout << "Not enough slots available.\n";
        cout << "Available slots: " << workshops[workshopName].slots << "\n";
        return;
    }

    // workshop found and enough slots available, proceed with booking
    workshops[workshopName].slots -= regis.seatsBooked;

    // i now just have to check if the workshop registration tree already has that id and if it does then i will show an error message but if it doesn't then i will insert the registration into the tree
    if (workshopRegistrations.find(workshopName) == workshopRegistrations.end())
    {
        workshopRegistrations[workshopName] = AVLTree();
    }

    if (workshopRegistrations[workshopName].search(regis.regID) != nullptr)
    {
        cout << "Registration ID already exists for this workshop.\n";
        cout << "Please choose a different ID.\n";
        return;
    }
    workshopRegistrations[workshopName].insert(regis);
    cout << "Seats booked successfully for " << regis.cusName << " in " << workshopName << ".\n";
}

void RemoveWorkshopAndRegistrations(unordered_map<string, workshop> &workshops, unordered_map<string, AVLTree> &workshopRegistrations, string workshopName)
{
    // we call this function when the workshop is cancelled or conducted and we want to remove all the registrations for that workshop and also remove the workshop from the system

    if (workshops.find(workshopName) == workshops.end())
    {
        cout << "Workshop not found.\n";
        if (workshopRegistrations.find(workshopName) != workshopRegistrations.end())
        {
            workshopRegistrations.erase(workshopName);
        }
        return;
    }
    workshops.erase(workshopName);
    workshopRegistrations.erase(workshopName);
    cout << "Workshop and its registrations removed successfully.\n";
}

bool verifyRegistration(unordered_map<string, AVLTree> &workshopRegistrations, string workshopName, int regID)
{
    if (workshopRegistrations.find(workshopName) == workshopRegistrations.end())
    {
        cout << "Workshop not found.\n";
        return false;
    }

    registration *reg = workshopRegistrations[workshopName].search(regID);
    if (reg != nullptr)
    {
        cout << "Registration found:\n";
        cout << "RegID: " << reg->regID
             << " | Customer: " << reg->cusName
             << " | Workshop: " << reg->workshopName
             << " | Date: " << reg->WorkshopDate
             << " | Seats: " << reg->seatsBooked
             << endl;
        return true;
    }
    else
    {
        cout << "Registration not found.\n";
        return false;
    }
}

bool IsworkshopFullOrCancalled(unordered_map<string, workshop> &workshops, string workshopName)
{
    if (workshops.find(workshopName) == workshops.end())
    {
        cout << "Workshop not found.\n";
        return true; // cancalled 

    }

    if (workshops[workshopName].slots <= 0)
    {
        cout << "Workshop is full.\n";
        return true;
    }

    cout << "Workshop is not full. Available slots: " << workshops[workshopName].slots << "\n";
    return false;
}

void GetAllRegistrationsForWorkshop(unordered_map<string, AVLTree> &workshopRegistrations, string workshopName)
{
    if (workshopRegistrations.find(workshopName) == workshopRegistrations.end())
    {
        cout << "Workshop not found.\n";
        return;
    }

    cout << "Registrations for " << workshopName << ":\n";
    cout << "Printing the registrations queue: \n";
    workshopRegistrations[workshopName].printInorder();
}

void processWorkshopModule()
{
    unordered_map<string, workshop> workshops;
    unordered_map<string, AVLTree> workshopRegistrations;

    // Example usage:
    int input;
    do
    {
        cout << "1. Add a workshop\n2. Book a slot\n3. Remove a workshop and its registrations\n4. Verify a registration\n5. Get all registrations for a workshop\n0. Exit\n";
        cin >> input;
        switch (input)
        {
        case 1:
            // Add a workshop
            {
                workshop w;
                string workshopName;
                cout << "Enter workshop name: ";
                cin >> workshopName;
                cout << "Enter gardener name: ";
                cin >> w.GardenerName;
                cout << "Enter gardener expertise: ";
                cin >> w.GardenerExpertise;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> w.date;
                cout << "Enter available slots: ";
                cin >> w.slots;

                addAWorkshop(workshops, workshopRegistrations, workshopName,w);
                cout << "Workshop added successfully.\n";
            }
            break;
        case 2:
            // Book a slot
            {
                registration reg;
                string workshopName;
                cout << "Enter workshop name: ";
                cin >> workshopName;

                if (!IsworkshopFullOrCancalled(workshops, workshopName))
                {
                    cout << "Enter registration ID: ";
                    cin >> reg.regID;
                    cout << "Enter customer name: ";
                    cin >> reg.cusName;
                    reg.workshopName = workshopName;
                    reg.WorkshopDate = workshops[workshopName].date;
                    cout << "Enter number of seats to book: ";
                    cin >> reg.seatsBooked;

                    bookSeat(workshops, workshopName, reg, workshopRegistrations);
                }
            }
            break;

        case 3:
            // Remove a workshop and its registrations
            {
                string workshopName;
                cout << "Enter workshop name to remove: ";
                cin >> workshopName;
                RemoveWorkshopAndRegistrations(workshops, workshopRegistrations, workshopName);
            }
            break;

        case 4:
            // Verify a registration
            {
                string workshopName;
                int regID;
                cout << "Enter workshop name: ";
                cin >> workshopName;
                cout << "Enter registration ID: ";
                cin >> regID;
                verifyRegistration(workshopRegistrations, workshopName, regID);
            }
            break;
        case 5:
            // Get all registrations for a workshop
            {
                string workshopName;
                cout << "Enter workshop name: ";
                cin >> workshopName;
                GetAllRegistrationsForWorkshop(workshopRegistrations, workshopName);
            }
            break;

        default:
            cout << "Invalid input. Please try again.\n";
            break;
        }

    } while (input != 0);
}

int main()
{
    processWorkshopModule();

    return 0;
}