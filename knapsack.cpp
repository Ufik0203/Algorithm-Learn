#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }
struct Item
{
    int value, weight;
    Item(int value, int weight) : value(value), weight(weight) {}
};

int knapSackBruteForce(int W, vector<int> &bobot, vector<int> &value, int n)
{
    if (n == 0 || W == 0)
        return 0;
    if (bobot[n - 1] > W)
        return knapSackBruteForce(W, bobot, value, n - 1);
    else
        return max(value[n - 1] + knapSackBruteForce(W - bobot[n - 1], bobot, value, n - 1), knapSackBruteForce(W, bobot, value, n - 1));
}

bool cmpByProfit(struct Item a, struct Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

bool cmpByWeight(struct Item a, struct Item b)
{
    return a.weight < b.weight;
}

bool cmpByDensity(struct Item a, struct Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double knapsackGreedy(int W, vector<Item> &arr, int n, bool (*cmp)(Item, Item))
{
    sort(arr.begin(), arr.end(), cmp);

    int curWeight = 0;
    double finalvalue = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (curWeight + arr[i].weight <= W) 
        {
            curWeight += arr[i].weight;
            finalvalue += arr[i].value;
        }
        else
        {
            int remain = W - curWeight;
            finalvalue += arr[i].value * ((double)remain / arr[i].weight);
            break;
        }
    }

    return finalvalue;
}

void run()
{
    int W;
    cout << "Enter the capacity of knapsack: ";
    cin >> W;

    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> value(n), bobot(n);
    vector<Item> arr;
    cout << "Enter the values and weights of items:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> value[i] >> bobot[i];
        arr.push_back(Item(value[i], bobot[i]));
    }

    int x;
    do
    {
        cout << "\nChoose method:" << endl;
        cout << "1. Brute Force\n2. Greedy by profit\n3. Greedy by weight\n4. Greedy by density\n5. Back to menu" << endl;
        cin >> x;
        switch (x)
        {
        case 1:
            cout << "\nHasil yang diperoleh dari metode Brute Force adalah " << knapSackBruteForce(W, bobot, value, n) << endl;
            break;
        case 2:
            cout << "\nHasil yang diperoleh dari metode Greedy by Profit adalah " << knapsackGreedy(W, arr, n, cmpByProfit) << endl;
            break;
        case 3:
            cout << "\nHasil yang diperoleh dari metode Greedy by Weight  adalah " << knapsackGreedy(W, arr, n, cmpByWeight) << endl;
            break;
        case 4:
            cout << "\nHasil yang diperoleh dari metode Greedy by Density adalah " << knapsackGreedy(W, arr, n, cmpByDensity) << endl;
            break;
        default:
            cout << "\nPilihan tidak valid" << endl;
            break;
        }
    } while (x != 5);
}