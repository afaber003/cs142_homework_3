#include <vector>
#include <cstdio>

using namespace std;

struct Game {
    int xCount = 0, oCount = 0;
    bool xTurn;
    char gamestate[3][3] = {};

    bool canWinOnNextTurn() {
        char characterToInsert = xTurn ? 'X' : 'O';
        vector<int> moves = availableMoves();
        for (int move : moves) {
            gamestate[move / 3][move % 3] = characterToInsert;
            if (checkWinCondition() || checkTwoWaysToWin(characterToInsert)) return true;
            gamestate[move / 3][move % 3] = '#';
        }
        return false;
    }

    bool checkTwoWaysToWin(char override = ' ') {
        char characterToInsert = override;
        if (characterToInsert == ' ')
            characterToInsert = !xTurn ? 'X' : 'O';
        vector<int> moves = availableMoves();
        int wins = 0;
        for (int move : moves) {
            gamestate[move / 3][move % 3] = characterToInsert;
            if (checkWinCondition()) wins++;
            gamestate[move / 3][move % 3] = '#';
        }
        return wins > 1;
    }

    vector<int> availableMoves() {
        vector<int> moves;
        for (int i = 0; i < 9; i++) {
            if (gamestate[i / 3][i % 3] == '#') {
                moves.push_back(i);
            }
        }
        return moves;
    }

    bool isBoardEmpty() {
        for (int i = 0; i < 9; i++) {
            if (gamestate[i / 3][i % 3] != '#') {
                return false;
            }
        }
        return true;
    }

    bool isBoardFull() {
        for (int i = 0; i < 9; i++) {
            if (gamestate[i / 3][i % 3] == '#') {
                return false;
            }
        }
        return true;
    }

    int isXOptimal() {
        if (isBoardEmpty()) return 0;
        if (checkWinCondition()) {
            if (xTurn) return -1;
            return 1;
        }
        if (checkTwoWaysToWin()) {
            return !xTurn ? 1 : -1;
        }
        if (isBoardFull()) return 0;
        if (canWinOnNextTurn()) return xTurn ? 1 : -1;
        if (xCount == 1) {
            if (gamestate[0][0] == 'X' || gamestate[2][2] == 'X' || gamestate[0][2] == 'X' || gamestate[2][0] == 'X') {
                if (oCount == 0) {
                    return 0;
                } else {
                    if (gamestate[1][1] == 'O') {
                        return 0;
                    } else {
                        return 1;
                    }
                }
            } else {
                if (gamestate[0][0] == 'O' || gamestate[2][2] == 'O' || gamestate[0][2] == 'O' || gamestate[2][0] == 'O') {
                    if (gamestate[1][1] == 'X') {
                        return 0;
                    } else {
                        return -1;
                    }
                }
            }
        }
        return doesXEventuallyWin();
    }

    int doesXEventuallyWin() {
        Game copy = *this; // create snapshot
        vector<int> possibleMoves = availableMoves();
        vector<int> outcomes;
        for (int movePosition : possibleMoves) {
            char characterToInsert = xTurn ? 'X' : 'O';
            if (xTurn) {
                xCount++;
            } else {
                oCount++;
            }
            xTurn = !xTurn;
            gamestate[movePosition / 3][movePosition % 3] = characterToInsert;
            outcomes.push_back(isXOptimal());
            *this = copy;
            gamestate[movePosition / 3][movePosition % 3] = characterToInsert == 'X' ? 'Y' : '1';
            printf("%c%c%c\n", gamestate[0][0], gamestate[1][0], gamestate[2][0]);
            printf("%c%c%c\n", gamestate[0][1], gamestate[1][1], gamestate[2][1]);
            printf("%c%c%c\n", gamestate[0][2], gamestate[1][2], gamestate[2][2]);
            printf("%d\n\n", outcomes[outcomes.size() - 1]);
            *this = copy;
        }
        if (xTurn) {
            if (any_of(outcomes.begin(), outcomes.end(), [](int outcome) {return outcome == 1;})) {
                return 1;
            } else if (all_of(outcomes.begin(), outcomes.end(), [](int outcome) {return outcome == -1;})) {
                return -1;
            }
        } else {
            if (any_of(outcomes.begin(), outcomes.end(), [](int outcome) {return outcome == -1;})) {
                return -1;
            } else if (all_of(outcomes.begin(), outcomes.end(), [](int outcome) {return outcome == 1;})) {
                return 1;
            }
        }
        return 0;
    }

    void calculateCounts() {
        for (int i = 0; i < 9; i++) {
            if (gamestate[i / 3][i % 3] == 'O') {
                oCount++;
            } else if (gamestate[i / 3][i % 3] == 'X') {
                xCount++;
            }
        }
    }

    bool checkWinCondition() {
        if (
                gamestate[0][0] == gamestate[0][1] && gamestate[0][0] == gamestate[0][2] && gamestate[0][0] != '#' ||
                        gamestate[1][0] == gamestate[1][1] && gamestate[1][0] == gamestate[1][2] && gamestate[1][0] != '#'  ||
                        gamestate[2][0] == gamestate[2][1] && gamestate[2][0] == gamestate[2][2] && gamestate[2][0] != '#'  ||
                gamestate[0][0] == gamestate[1][0] && gamestate[0][0] == gamestate[2][0] && gamestate[0][0] != '#'  ||
                        gamestate[0][1] == gamestate[1][1] && gamestate[0][1] == gamestate[2][1] && gamestate[0][1] != '#'  ||
                        gamestate[0][2] == gamestate[1][2] && gamestate[0][2] == gamestate[2][2] && gamestate[0][2] != '#'  ||
                gamestate[0][0] == gamestate[1][1] && gamestate[0][0] == gamestate[2][2] && gamestate[0][0] != '#'  ||
                        gamestate[0][2] == gamestate[1][1] && gamestate[0][2] == gamestate[2][0] && gamestate[0][2] != '#'
                ) {
            return true;
        }
        return false;
    }
};

int main() {

    Game game; char temp;
    for (int j = 0; j < 3; j++) {
        scanf("%c%c%c%c", &game.gamestate[0][j], &game.gamestate[1][j], &game.gamestate[2][j], &temp);
    }
    game.calculateCounts();
    game.xTurn = game.xCount <= game.oCount;

    int output = game.isXOptimal();
    if (output == 1) {
        printf("Crosses win\n");
    } else if (output == 0) {
        printf("Draw\n");
    } else {
        printf("Noughts win\n");
    }


    return 0;
}
