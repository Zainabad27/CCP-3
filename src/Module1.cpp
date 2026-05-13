// the module that keep the track of all the plants and their data and condition.

#include <iostream>
#include <string>
#include <vector>
#include "Module1.h"
using namespace std;
// #define PLANTS_HEALTH_LEVELS 10

// we basically have to write four main funcs here which are
// show plants, add plant, remove plant and update plant health.
void waterPlants(vector<vector<plants>> &plantStorage)
{
    for (size_t i = 0; i < PLANTS_HEALTH_LEVELS; i++)
    {
        for (size_t j = 0; j < plantStorage[i].size(); j++)
        {
            if (plantStorage[i][j].waterNeed <= 0)
            {
                cout << "Plant " << plantStorage[i][j].name << " does not need water currently.\n\n";    
                plantStorage[i][j].waterNeed = 0;
            }
            else
            {
                plantStorage[i][j].waterNeed -= plantStorage[i][j].waterNeed;
            }
        }
    }

    cout << "Plants watered successfully. All water needs have been updated.\n";
}
void showPlants(vector<vector<plants>> plantStorage, int healthLevel)
{
    if (plantStorage[healthLevel].size() == 0)
    {
        // cout << "no plants with health level " << healthLevel << " in the database curently.\n";
        return;
    }
    cout << "Plants with health level " << healthLevel << ":\n";
    for (int i = 0; i < plantStorage[healthLevel].size(); i++)
    {
        cout << "Name: " << plantStorage[healthLevel][i].name << ", Water Need(mL): " << plantStorage[healthLevel][i].waterNeed << ", Sunlight Need (Hours/Day): " << plantStorage[healthLevel][i].sunlightNeed << " Index: " << i << "\n\n\n";
    }
}
void addPlant(plants plant, vector<vector<plants>> &plantStorage)
{
    if(plant.healthLevel < 0 || plant.healthLevel > PLANTS_HEALTH_LEVELS-1)
    {
        cout << "Invalid health level. It should be between 0 and " << PLANTS_HEALTH_LEVELS-1 << ".\n";
        return;
    }
    plantStorage[plant.healthLevel].push_back(plant);
}

void removePlant(int plantIndex, int healthLevel, vector<vector<plants>> &plantStorage)
{
      if((healthLevel < 0 || healthLevel > PLANTS_HEALTH_LEVELS-1))
    {
        cout << "Invalid health level. It should be between 0 and " << PLANTS_HEALTH_LEVELS-1 << ".\n";
        return;
    }
    // this function will remove the plant from the storage vector.

    swap(plantStorage[healthLevel][plantIndex], plantStorage[healthLevel][(plantStorage[healthLevel]).size() - 1]);
    plantStorage[healthLevel].pop_back();
}

void updateplantHealth(int newhealth, int plantIndex, int oldHealthLevel, vector<vector<plants>> &plantStorage)
{
    if((oldHealthLevel < 0 || oldHealthLevel > PLANTS_HEALTH_LEVELS-1) ||(newhealth < 0 || newhealth > PLANTS_HEALTH_LEVELS-1))
    {
        cout << "Invalid health level. It should be between 0 and " << PLANTS_HEALTH_LEVELS-1 << ".\n";
        return;
    }
    // this function will also update the plants position in the storage vector if their health level changes.

    plantStorage[oldHealthLevel][plantIndex].updateHealthLevel(newhealth);
    plantStorage[newhealth].push_back(plantStorage[oldHealthLevel][plantIndex]);

    swap(plantStorage[oldHealthLevel][plantIndex], plantStorage[oldHealthLevel][(plantStorage[oldHealthLevel]).size() - 1]);
    plantStorage[oldHealthLevel].pop_back();
}

void Module1()
{
    system("clear");
    vector<vector<plants>> plantStorage(10); // Assuming 10 health levels
    int input;
    do
    {
         system("clear");  
        string name, sunlightNeed;
        int waterNeed, healthLevel;
        int plantIndex;
        cout << "1. Show Plants\n2. Add Plant\n3. Remove Plant\n4. Update Plant Health\n5. Show All Plants\n6. Water Plants\n0. Exit\n";
        cin >> input;
        switch (input)
        {
        case 1:
            int healthLevel;
            cout << "Enter health level to show flowers: ";
            cin >> healthLevel;
            showPlants(plantStorage, healthLevel);
            break;
        case 2:
            name, sunlightNeed;
            waterNeed, healthLevel;
            cout << "Enter flower name: ";
            cin >> name;
            cout << "Enter sunlight need(Hours/Day): ";
            cin >> sunlightNeed;
            cout << "Enter water need(mL): ";
            cin >> waterNeed;
            cout << "Enter health level (0-9): ";
            cin >> healthLevel;
            addPlant(plants(name, sunlightNeed, waterNeed, healthLevel), plantStorage);
            break;
        case 3:
            plantIndex, healthLevel;
            cout << "Enter health level of the plant to remove: ";
            cin >> healthLevel;
            cout << "Enter index of the plant to remove: ";
            cin >> plantIndex;
            removePlant(plantIndex, healthLevel, plantStorage);
            break;
        case 4:
        {
            cout << "Updating all plants one by one.\n";
            for (size_t i = 0; i < PLANTS_HEALTH_LEVELS; i++)
            {
                for (size_t j = 0; j < plantStorage[i].size(); j++)
                {
                    cout << "do you want to update the plant of health level " << i << " with name " << plantStorage[i][j].name << " ? (y/n) : \nPress 'x' to exit the update process.\n ";
                    char choice;
                    cin >> choice;
                    if (choice == 'x' || choice == 'X')
                    {
                        cout << "Exiting plant health update process.\n";
                        break;
                    }
                    if (choice == 'y' || choice == 'Y')
                    {
                        int newHealth;
                        cout << "Enter new health level (0-9): ";
                        cin >> newHealth;

                        updateplantHealth(newHealth, j, i, plantStorage);
                        cout << "Plant health updated successfully.\n";
                    }
                }
            }
        }
        case 5:
        {
            cout << "Showing all plants in the database:\n";
            for (size_t i = 0; i < PLANTS_HEALTH_LEVELS; i++)
            {
                showPlants(plantStorage, i);
            }
            break;
        }
        case 6:
            waterPlants(plantStorage);
            break;
        case 0:
            cout << "Exiting Plant Module.\n";
            break;
        default:    
            cout << "Invalid input. Please try again.\n";
            break;
        }
    } while (input != 0);
}
