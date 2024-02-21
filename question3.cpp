#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

// totalValue, weight, bestValue
map<int, map<int, int>> bestValuesForLeftValue;

int minWeight = numeric_limits<int>::max();

struct Item {
    int value;
    int itemsLeft;
    int weight;
};

int bestValueForWeight(vector<Item>& itemList, int weightRemaining, int totalValueLeft) {

    if (bestValuesForLeftValue[totalValueLeft][weightRemaining]) {
        return bestValuesForLeftValue[totalValueLeft][weightRemaining];
    }

    int best = 0, currentItemCount;
    for (Item& item : itemList) {
        if (item.weight <= weightRemaining && item.itemsLeft > 0) {
            currentItemCount = item.itemsLeft;
            item.itemsLeft--;
            best = max(best, item.value + (weightRemaining - item.weight > minWeight ? bestValueForWeight(itemList, weightRemaining - item.weight, totalValueLeft - item.value) : 0));
            item.itemsLeft = currentItemCount;
        }
    }

    bestValuesForLeftValue[totalValueLeft][weightRemaining] = best;

    return best;
}

int main() {

    // take parameters
    int maxWeight, numberOfItems, perItemLimit;
    scanf("%d %d %d", &maxWeight, &numberOfItems, &perItemLimit);

    // Set up store
    vector<Item> itemList(numberOfItems);
    int totalValue = 0;
    for (Item& item : itemList) {
        scanf("%d %d", &item.weight, &item.value);
        totalValue += perItemLimit * item.value;
        item.itemsLeft = perItemLimit;
        minWeight = min(minWeight, item.weight);
    }

    printf("%d", bestValueForWeight(itemList, maxWeight, totalValue));
    return 0;
}