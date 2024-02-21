#include <cstdio>
#include <vector>
#include <limits>
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int weight;
    vector<int> childrenIndices;
    int parentIndex = -1;
    int iAmRoot = numeric_limits<short>::min();
    int bestWeightWithMe = numeric_limits<short>::min(); // include me
    int bestWeightBelow = numeric_limits<short>::min(); // exclude me

    bool hasChildren() const {
        return !this->childrenIndices.empty();
    }

    int getBestChildrenCombination(const vector<Node>& masterList) {
        int total = this->weight;
        vector<int> childBests;
        for (int& childIndex : this->childrenIndices) {
            if (masterList[childIndex].bestWeightWithMe > 0) {
                childBests.push_back(masterList[childIndex].bestWeightWithMe);
            }
        }
        if (childBests.size() >= 2) {
            sort(childBests.begin(), childBests.end());
            childBests = {childBests[childBests.size() - 1], childBests[childBests.size() - 2]};
        }
        for (auto& i : childBests) {
            total += i;
        }
        return total;
    }
};

void doIt(vector<Node>& masterList, int index) {

    // make sure the children have the chance to update me
    if (masterList[index].hasChildren()) {
        for (int childIndex : masterList[index].childrenIndices) {
            doIt(masterList, childIndex);
        }
        if (masterList[index].bestWeightBelow <= 0) {
            masterList[index].bestWeightWithMe = masterList[index].weight;
            masterList[index].iAmRoot = masterList[index].weight;
        } else {
            masterList[index].bestWeightWithMe = masterList[index].bestWeightBelow + masterList[index].weight;
            masterList[index].iAmRoot = masterList[index].getBestChildrenCombination(masterList);
        }
    } else {
        masterList[index].bestWeightBelow = 0;
        masterList[index].bestWeightWithMe = masterList[index].weight;
        masterList[index].iAmRoot = masterList[index].weight;
    }

    if (index == 0) {
        return;
    }

    // update my parent
    if (masterList[index].bestWeightBelow <= 0) {
        masterList[masterList[index].parentIndex].bestWeightBelow = max(masterList[index].weight, masterList[masterList[index].parentIndex].bestWeightBelow);
    } else {
        if (masterList[index].weight >= 0) {
            masterList[masterList[index].parentIndex].bestWeightBelow = max(masterList[masterList[index].parentIndex].bestWeightBelow, masterList[index].bestWeightWithMe);
        } else {
            masterList[masterList[index].parentIndex].bestWeightBelow = max(masterList[index].bestWeightBelow, masterList[masterList[index].parentIndex].bestWeightBelow);
        }
    }
}

int main() {

    // Create tree
    int treeSize;
    scanf("%d", &treeSize);
    vector<Node> masterList(treeSize);
    for (auto& node : masterList) {
        scanf("%d", &node.weight);
    }

    // Build relationships
    int current;
    for (int i = 1; i < treeSize; i++) {
        scanf("%d", &current);
        masterList[i].parentIndex = current;
        masterList[current].childrenIndices.push_back(i);
    }

    doIt(masterList, 0);

    int best = 0;
    for (const auto& node : masterList) {
        if (best < node.iAmRoot) {
            best = node.iAmRoot;
        }
    }

    printf("%d\n", max(max(masterList[0].bestWeightBelow, masterList[0].bestWeightWithMe), best));
    return 0;
}