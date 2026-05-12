#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_Budget 10
#define MAX_TOOLS 10
struct tool
{
    string name;
    int price;
    int benifit;
};

void calculateMaxBenifit(vector<tool> &tools)
{
    tools.insert(tools.begin(), tool{});
    int lastCol, lastRow;

    int arr[MAX_Budget + 1][tools.size() + 1];

    for (int currentRow = 0; currentRow < tools.size(); currentRow++)
    {
        for (int currentBudget = 0; currentBudget <= MAX_Budget; currentBudget++)
        {
            if (currentRow == 0 || currentBudget == 0)
            {
                arr[currentRow][currentBudget] = 0;
            }
            else if (tools[currentRow].price <= currentBudget)
            {
                arr[currentRow][currentBudget] = max(arr[currentRow - 1][currentBudget], tools[currentRow].benifit + arr[currentRow - 1][currentBudget - tools[currentRow].price]);
            }

            else
            {
                arr[currentRow][currentBudget] = arr[currentRow - 1][currentBudget];
            }
            lastCol = currentBudget;
        }
        lastRow = currentRow;
    }

    // calculating which tools are present in the benifit score.
    // bool itemsFound = false;

    // int tool1 = 0, tool2 = 0;

    // while (!itemsFound)
    // {
    //     if (arr[lastRow][lastCol] == arr[lastRow - 1][lastCol])
    //     {
    //         lastRow--;
    //         continue;
    //     }
    //     if (arr[lastRow][lastCol] != arr[lastRow - 1][lastCol])
    //     {
    //         if (tool1)
    //         {
    //             tool2 = lastRow;
    //             itemsFound = true;
    //         };
    //         tool1 = lastRow;
    //         int ValueTobeFoundInUpperRow = arr[lastRow][lastCol] - tools[tool1].benifit;

    //         lastRow--;

    //         // have to update lastcol value in the upper row in which tool one was found.

    //         while (arr[lastRow][lastCol] != ValueTobeFoundInUpperRow)
    //         {
    //             lastCol--;
    //         }
    //     }
    // }

    int w = MAX_Budget;
    int n = tools.size() - 1;
    cout << "Selected tools:\n";
    for (int row = n; row >= 1; row--)
    {
        if (arr[row][w] != arr[row - 1][w])
        {
            cout << "  - " << tools[row].name << "\n";
            w -= tools[row].price;
        }
    }
}

void processModule3()
{
    vector<tool> tools;
    int choice;

    do
    {
        cout << "\n=== Tool Benefit Calculator ===\n";
        cout << "1. Enter tools\n";
        cout << "2. Calculate max benefit\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int n;
            cout << "Enter number of tools: ";
            cin >> n;

            tools.clear();
            // tools.emplace(tools.begin(), Tool{});  // your dummy padding

            for (int i = 1; i <= n; i++)
            {
                tool t;
                cout << "\nTool " << i << ":\n";
                cout << "  Name: ";
                cin >> t.name;
                cout << "  Price: ";
                cin >> t.price;
                cout << "  Benefit: ";
                cin >> t.benifit;
                tools.push_back(t);
            }

            cout << "Tools stored successfully!\n";
            break;
        }

        case 2:
        {
            if (tools.size() <= 0)
            { // only dummy element present
                cout << "Please enter tools first!\n";
                break;
            }
            calculateMaxBenifit(tools);
            break;
        }

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 3);
}

int main()
{
    processModule3();
    return 0;
}