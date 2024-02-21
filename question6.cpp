#include <cstdio>
#include <vector>

using namespace std;

int main() {

    int numberOfCereals;
    scanf("%d", &numberOfCereals);

    vector<int> cereals(numberOfCereals);
    for (int i = 0; i < numberOfCereals; i++) {
        scanf("%d", &cereals[numberOfCereals]);
    }

    vector<int> checkedCereals;
    int numberDeleted = 0;
    bool incremented;
    for (int& cereal : cereals) {
        incremented = false;
        for (int& checkedCereal : checkedCereals) {
            if (cereal % checkedCereal == 0) {
                incremented = true;
                numberDeleted++;
                break;
            }
        }
        if (!incremented && cereal != 0){
            checkedCereals.push_back(cereal);
        }
    }

    printf("%d", numberDeleted);


    return 0;
}