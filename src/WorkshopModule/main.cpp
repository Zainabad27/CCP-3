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

void addAWorkshop(unordered_map<string, workshop> &workshops, workshop w, string workshopName)
{
    workshops[workshopName] = w;
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

int main()
{

    return 0;
}