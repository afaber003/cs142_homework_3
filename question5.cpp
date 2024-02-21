#include <vector>
#include <cstdio>

using namespace std;

struct Game {
    bool xTurn;
    char gamestate[3][3] = {};

    vector<int> availableMoves() {
        vector<int> moves;
        for (int i = 0; i < 9; i++) {
            if (gamestate[i / 3][i % 3] == '#') {
                moves.push_back(i);
            }
        }
        return moves;
    }

    bool doMove(int x ,int y) {
        if (gamestate[x][y] != '#') {printf("Invalid move");return false;}
        char add = xTurn ? 'X' : 'O';

        gamestate[x][y] = add;
        xTurn = !xTurn;
        return checkWinCondition();
    }

    bool checkWinCondition() {
        if (
                gamestate[0][0] == gamestate[0][1] && gamestate[0][0] == gamestate[0][2] ||
                        gamestate[1][0] == gamestate[1][1] && gamestate[1][0] == gamestate[1][2] ||
                        gamestate[2][0] == gamestate[2][1] && gamestate[2][0] == gamestate[2][2] ||
                gamestate[0][0] == gamestate[1][0] && gamestate[0][0] == gamestate[2][0] ||
                        gamestate[0][1] == gamestate[1][1] && gamestate[0][1] == gamestate[2][1] ||
                        gamestate[0][2] == gamestate[1][2] && gamestate[0][2] == gamestate[2][2] ||
                gamestate[0][0] == gamestate[1][1] && gamestate[0][0] == gamestate[2][2] ||
                        gamestate[0][2] == gamestate[1][1] && gamestate[0][2] == gamestate[2][0]
        ) {
            return true;
        }
        return false;
    }

    int pointsResultingFromMove(int x, int y) {

    }
};

int main() {

    Game game;
    int xCount = 0, oCount = 0;
    for (int i = 0; i < 9; i++) {
        scanf("%c", &game.gamestate[i / 3][i % 3]);
        if (game.gamestate[i / 3][i % 3] == 'X') {
            xCount++;
        } else if (game.gamestate[i / 3][i % 3] == 'O') {
            oCount++;
        }
    }
    game.xTurn = xCount <= oCount;





    return 0;
}
