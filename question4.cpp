#include <cstdio>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

struct Item {
    int value;
    int potential = -1;
};

void findLargestIncreasing(vector<Item>& memoryList, int index) {

    if (memoryList[index].potential != -1) {
        return;
    }

    memoryList[index].potential = 0;
    int prevBestChildValue = numeric_limits<int>::max();
    for (int childIndex = index + 1; childIndex < memoryList.size(); childIndex++) {
        if (memoryList[childIndex].value < prevBestChildValue && memoryList[childIndex].value > memoryList[index].value) {
            if (memoryList[childIndex].potential == -1) {
                findLargestIncreasing(memoryList, childIndex);
            }

            if (memoryList[index].potential < memoryList[childIndex].potential + memoryList[childIndex].value) {
                memoryList[index].potential = memoryList[childIndex].potential + memoryList[childIndex].value;
            }
            prevBestChildValue = memoryList[childIndex].value;
        }
    }
}

int main() {

    int memCount;
    //scanf("%d", &memCount);
    vector<Item> memories(10e5);
    for (Item& item : memories) {
        item.value = rand() % 10000;
        //scanf("%d", &item.value);
    }

    int best = 0, smallest = numeric_limits<int>::max();
    for (int i = 0; i < 10e5; i++) {
        if (memories[i].value < smallest) {
            findLargestIncreasing(memories, i);
            best = max(best, memories[i].value + memories[i].potential);
            smallest = memories[i].value;
        }
    }

    printf("%d", best);

    return 0;
}