#ifndef PLANTSTORAGE_H
#define PLANTSTORAGE_H
#include <iostream>
#include <string>
#include <vector>
#define PLANTS_HEALTH_LEVELS 10


struct plants
{
    std::string name;
    int healthLevel;
    int waterNeed;
    std::string sunlightNeed;

    plants(std::string name, std::string sunlightNeed, int waterNeed, int healthLevel = 9)
    {
        this->sunlightNeed = sunlightNeed;
        this->name = name;
        this->waterNeed = waterNeed;
        if (healthLevel < 0 || healthLevel > PLANTS_HEALTH_LEVELS-1)
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
        if (level < 0 || level > PLANTS_HEALTH_LEVELS-1)
        {
            std::cout << "Invalid health level. It should be between 0 and " << PLANTS_HEALTH_LEVELS << ".\n";
            return;
        }

        this->healthLevel = level;
    }
};
void processPlantModule(std::vector<std::vector<plants>> &plantStorage);

#endif