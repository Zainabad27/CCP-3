#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#define MAX_Health 9

using namespace std;

struct plant
{
    string name;
    int currenthealth;
    int sunlightneed;
    int waterlevel;
};

void addplant(unordered_map<int, vector<plant>> &store, plant TobeAdded)
{

    if (TobeAdded.currenthealth < 0 || TobeAdded.currenthealth > MAX_Health)
    {
        cout << "invalid heath level.\n";
        return;
    }

    store[TobeAdded.currenthealth].push_back(TobeAdded);
}

vector<plant> RetrievePlantsStatusWise(int healthlevel, unordered_map<int, vector<plant>> &store)
{
    if (healthlevel < 0 || healthlevel > MAX_Health)
    {
        cout << "invalid heath level.\n";
        return vector<plant>();
    }

    if(store[healthlevel].size()==0){
        cout<<"no plants of health level "<<healthlevel<<" found.\n";
          return vector<plant>();
    }

    return store[healthlevel];
}
void updatePlantHealth(int Oldhealthlevel, unordered_map<int, vector<plant>> &store,int newhealth,int index){
        if ((Oldhealthlevel < 0 || Oldhealthlevel > MAX_Health)|| (newhealth < 0 || newhealth > MAX_Health))
        {
            cout << "invalid heath level.\n";
            return;
        }
        if(store.find(Oldhealthlevel) == store.end())
        {
            cout << "No plants for this health level.\n";
            return;
        }

        if (index < 0 || index >= store[Oldhealthlevel].size())
        {
            cout << "plant at index " << index << " not found.\n";
            return;
        }

        store[Oldhealthlevel][index].currenthealth=newhealth;
        store[newhealth].push_back(store[Oldhealthlevel][index]);

        store[Oldhealthlevel].erase(store[Oldhealthlevel].begin()+index);
        cout<<"Plant health updated successfully.\n\n\n";
}
void waterPlants(int healthlevel, unordered_map<int, vector<plant>> &store){
     if (healthlevel < 0 || healthlevel > MAX_Health)
    {
        cout << "invalid heath level.\n";
        return;
    }



    vector<plant> Tobewatered=RetrievePlantsStatusWise(healthlevel,store);

    if(Tobewatered.size()==0){
        cout<<"no plants of health level "<<healthlevel<<" found.\n";
        return;
    }



    for(int i=0;i<Tobewatered.size();i++){
        if(Tobewatered[i].currenthealth==MAX_Health){
            continue;
        }
        Tobewatered[i].currenthealth+=1;
        updatePlantHealth(healthlevel,store,Tobewatered[i].currenthealth,i);

    }


    cout<<"plants of health level "<<healthlevel<<" watered successfully.\n";

}

void processplantmodule(){
    int input;

    unordered_map<int, vector<plant>> store;
    do
    {
        cout << "1: AddPlant\n2:RetreivePlant\n3:WaterPlants\n4:UpdateHealth Manually\n0:Exit\n";
        cin >> input;
        
        switch (input)
        {
        case 1:
        {

            plant p1;
            cout << "enter the name of plant.\n";
            cin >> p1.name;
            cout << "enter the sunlight need(hours/day)\n";
            cin >> p1.sunlightneed;
            cout << "enter the waterneed(mL/day)\n";
            cin >> p1.waterlevel;

            cout << "enter the health.\n";

            cin >> p1.currenthealth;

            addplant(store, p1);

            break;
        }

        case 2:
        {
            int health;
            cout << "at which level do you wanna retreive plants.\n";
            cin >> health;

            vector<plant> plants = RetrievePlantsStatusWise(health, store);

            for (int i = 0; i < plants.size(); i++)
            {
                cout << "Name: " << plants[i].name << "\n";
                cout << "sunlight need: " << plants[i].sunlightneed << "\n";
                cout << "water need: " << plants[i].waterlevel << "\n";
                cout << "Health status: " << plants[i].currenthealth << "\n";
                cout<<"Plant Index: " << i << "\n";
                cout<<"\n\n";
            }
            break;
        }
        case 3:
        {
            int health;
            cout << "which level of plants do you wanna water.\n";
            cin >> health;

            waterPlants(health,store);
            break;
        }
        case 4:
        {
            int oldhealth,newhealth,index;
            cout<<"enter the old health level of plant.\n";
            cin>>oldhealth;
            cout<<"enter the index of plant in that health level.\n";
            cin>>index;
            cout<<"enter the new health level of plant.\n";
            cin>>newhealth;

            updatePlantHealth(oldhealth,store,newhealth,index);
            break;
        }
        default:
        {
                cout << "invalid input.\n";
                break;
        }
        }

    } while (input != 0);
}

int main(){
    processplantmodule();
    return 0;   
}