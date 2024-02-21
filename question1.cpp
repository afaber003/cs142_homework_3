#include <cstdio>
#include <vector>

using namespace std;

struct Node {
    int value;
    int bestRight = -1;
    int bestLeft = -1;
};

void getSmallestValueRight(vector<Node>& numberLine, int index) {
    // If the number has already been calculated, skip it to save time
    if (numberLine[index].bestRight != -1) return;

    // iterate through all the possible "children" of this and solve
    // for them if they fit the criteria and haven't been solved already
    numberLine[index].bestRight = 0;
    int best = 0;
    for (int i = index + 1; i < numberLine.size(); i++) {
        if (numberLine[i].value < numberLine[index].value) {
            if (numberLine[i].bestRight == -1) {
                getSmallestValueRight(numberLine, i);
            }
            if (best < (numberLine[i].bestRight + 1)) best = (numberLine[i].bestRight + 1);
        }
    }
    numberLine[index].bestRight += best;
}

void getSmallestValueLeft(vector<Node>& numberLine, int index) {
    // If the number has already been calculated, skip it to save time
    if (numberLine[index].bestLeft != -1) return;

    // iterate through all the possible "children" of this and solve
    // for them if they fit the criteria and haven't been solved already
    numberLine[index].bestLeft = 0;
    int best = 0;
    for (int i = index - 1; i >= 0; i--) {
        if (numberLine[i].value < numberLine[index].value) {
            if (numberLine[i].bestLeft == -1) {
                getSmallestValueLeft(numberLine, i);
            }
            if (best < numberLine[i].bestLeft + 1) best = numberLine[i].bestLeft + 1;
        }
    }
    numberLine[index].bestLeft += best;
}

int main() {

    // read in the length
    int numberOfItems;
    scanf("%d", &numberOfItems);

    // generate numberLine with values puled from io
    vector<Node> numberLine(numberOfItems);
    for (auto& node : numberLine) {
        scanf("%d", &node.value);
    }

    // Trigger the recursive call across all (most will likely not work)
    for (int i = 0; i < numberOfItems; i++) {
        getSmallestValueLeft(numberLine, i);
        getSmallestValueRight(numberLine, i);
    }


    int best = 0;
    for (auto& node : numberLine) {
        if (best < node.bestLeft + node.bestRight) {
            best = node.bestLeft + node.bestRight;
        }
    }

    printf("%d\n", best + 1);

    return 0;
}
