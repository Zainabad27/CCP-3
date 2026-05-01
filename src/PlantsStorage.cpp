// the module that keep the track of all the plants and their data and condition.

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define PLANTS_HEALTH_LEVELS 10

// we basically have to write four main funcs here which are

struct plants
{
    string name;
    int healthLevel;
    int waterNeed;
    string sunlightNeed;

    plants(string name, string sunlightNeed, int waterNeed, int healthLevel = 9)
    {
        this->sunlightNeed = sunlightNeed;
        this->name = name;
        this->waterNeed = waterNeed;
        if (healthLevel < 0 || healthLevel > PLANTS_HEALTH_LEVELS)
        {
            this->healthLevel = 9; // default health level
        }
        else
        {
            this->healthLevel = healthLevel;
        }
    }

    void updateHealthLevel(int level)
    {
        if (level < 0 || level > PLANTS_HEALTH_LEVELS)
        {
            cout << "Invalid health level. It should be between 0 and " << PLANTS_HEALTH_LEVELS << ".\n";
            return;
        }

        this->healthLevel = level;
    }
};

void showPlants(vector<vector<plants>> plantStorage, int healthLevel)
{
    if (plantStorage[healthLevel].size() == 0)
        return;
    cout << "Plants with health level " << healthLevel << ":\n";
    for (int i = 0; i < plantStorage[healthLevel].size(); i++)
    {
        cout << "Name: " << plantStorage[healthLevel][i].name << ", Water Need: " << plantStorage[healthLevel][i].waterNeed << ", Sunlight Need: " << plantStorage[healthLevel][i].sunlightNeed << endl;
    }
}
void addPlant(plants plant, vector<vector<plants>> &plantStorage)
{
    plantStorage[plant.healthLevel].push_back(plant);
}

void removePlant(int plantIndex, int healthLevel, vector<vector<plants>> &plantStorage){
    // this function will remove the plant from the storage vector. 

}

void updateplantHealth(int newhealth, int plantIndex, int oldHealthLevel, vector<vector<plants>> &plantStorage){
    // this function will also update the plants position in the storage vector if their health level changes.  

    plantStorage[oldHealthLevel][plantIndex].updateHealthLevel(newhealth);
    


}




int main()
{
    vector<vector<plants>> plantStorage(PLANTS_HEALTH_LEVELS);
}
