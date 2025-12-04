#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <tuple>

using namespace std;

class Player {
    char mark;
public:
    Player(char m) { mark = m; }
    virtual int getMove() = 0;
    char getMark() const { return mark; }
};

class HPlayer : public Player {
public:
    HPlayer(char mark) : Player(mark) {}
    int getMove() override {
        int index;
        cout << "Enter box number to put " << getMark() << " : ";
        cin >> index;
        return index;
    }
};

class Board {
    char arr[9];
    bool setMove(int index, char mark) {
        char m = arr[index - 1];
        if (m >= '1' && m <= '9') {
            arr[index - 1] = mark;
            return true;
        }
        return false;
    }
    friend class Game;
public:
    void init() {
        for (int i = 0; i < 9; i++)
            arr[i] = i + '1';
    }
    void getBoard(char b[]) {
        for (int i = 0; i < 9; i++)
            b[i] = arr[i];
    }
    void draw() {
        cout << endl;
        cout << " ___ ___ ___ " << endl;
        cout << "|   |   |   |" << endl;
        cout << "| " << arr[0] << " | " << arr[1] << " | " << arr[2] << " |" << endl;
        cout << "|___|___|___|" << endl;
        cout << "|   |   |   |" << endl;
        cout << "| " << arr[3] << " | " << arr[4] << " | " << arr[5] << " |" << endl;
        cout << "|___|___|___|" << endl;
        cout << "|   |   |   |" << endl;
        cout << "| " << arr[6] << " | " << arr[7] << " | " << arr[8] << " |" << endl;
        cout << "|___|___|___|" << endl;
    }

    bool makeMove(int pos, char mark) {
        return setMove(pos, mark);
    }
};

class NonsenseComputerPlayer : public Player {
public:
    NonsenseComputerPlayer(char mark) : Player(mark) {
        srand(time(0));
    }
    int getMove() override {
        int move = rand() % 9 + 1;
        cout << "Nonsense Computer chose: " << move << endl;
        return move;
    }
};

class SensibleComputerPlayer : public Player {
    Board* board;
public:
    SensibleComputerPlayer(char mark, Board* b) : Player(mark), board(b) {}
    int getMove() override {
        char bArr[9];
        board->getBoard(bArr);
        char myMark = getMark();
        char oppMark = (myMark == 'X') ? 'O' : 'X';

        auto checkLine = [&](int i, int j, int k, char mark) -> int {
            int count = 0, empty = -1;
            if (bArr[i] == mark) count++; else if (bArr[i] >= '1' && bArr[i] <= '9') empty = i;
            if (bArr[j] == mark) count++; else if (bArr[j] >= '1' && bArr[j] <= '9') empty = j;
            if (bArr[k] == mark) count++; else if (bArr[k] >= '1' && bArr[k] <= '9') empty = k;
            return (count == 2 && empty != -1) ? empty + 1 : -1;
        };

        int move;
        for (auto line : { tuple{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} }) {
            move = checkLine(get<0>(line), get<1>(line), get<2>(line), myMark);
            if (move != -1) return move;
        }
        for (auto line : { tuple{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} }) {
            move = checkLine(get<0>(line), get<1>(line), get<2>(line), oppMark);
            if (move != -1) return move;
        }
        for (int i = 0; i < 9; i++) {
            if (bArr[i] >= '1' && bArr[i] <= '9')
                return i + 1;
        }
        return 1;
    }
};

class Game {
    Board* b;
    Player *p1, *p2;
public:
    Game(Player* player1, Player* player2, Board* board) {
        p1 = player1;
        p2 = player2;
        b = board;
        b->init();
        b->draw();
    }

    bool checkWin(char b[], int pos, char mark) {
        int row = (pos / 3) * 3;
        if (b[row] == mark && b[row+1] == mark && b[row+2] == mark) return true;

        int col = pos % 3;
        if (b[col] == mark && b[col+3] == mark && b[col+6] == mark) return true;

        if ((b[0] == mark && b[4] == mark && b[8] == mark) ||
            (b[2] == mark && b[4] == mark && b[6] == mark)) return true;

        return false;
    }

    void runGame() {
        int count = 0, pos, turn = 1;
        char a[9], mark = p1->getMark();
        Player* currentPlayer = p1;

        while (count < 9) {
            do {
                pos = currentPlayer->getMove();
                mark = currentPlayer->getMark();
            } while (!b->makeMove(pos, mark));

            b->draw();
            b->getBoard(a);

            if (checkWin(a, pos - 1, mark)) break;

            count++;
            currentPlayer = (currentPlayer == p1) ? p2 : p1;
        }

        if (count == 9) cout << "Game Draw!\n";
        else cout << "Player with mark '" << mark << "' Won!\n";
    }
};

int toss() {
    return rand() % 2;
}

int main() {
    srand(time(0));
    int choice, playAgain;

    do {
        cout << "Select option that u want to play with:\n"
             << "1. human vs human\n"
             << "2. Human vs nonsense Computer\n"
             << "3. Human vs Sensible Computer\n"
             << "4. Nonsense vs Sensible Computer\n"
             << "Enter choice: ";
        cin >> choice;

        Player *p1, *p2;
        Board* board = new Board();

        char mark1, mark2;
        cout << "Enter mark for Player 1 (O/X): ";
        cin >> mark1;
        cout << "Enter mark for Player 2 (O/X): ";
        cin >> mark2;

        int tossResult = toss();
        cout << "Toss result: Player " << (tossResult == 0 ? "1" : "2") << " goes first\n";

        if (choice == 1) {
            p1 = new HPlayer(mark1);
            p2 = new HPlayer(mark2);
        }
        else if (choice == 2) {
            if (tossResult == 0) {
                p1 = new HPlayer(mark1);
                p2 = new NonsenseComputerPlayer(mark2);
            } else {
                p1 = new NonsenseComputerPlayer(mark1);
                p2 = new HPlayer(mark2);
            }
        }
        else if (choice == 3) {
            if (tossResult == 0) {
                p1 = new HPlayer(mark1);
                p2 = new SensibleComputerPlayer(mark2, board);
            } else {
                p1 = new SensibleComputerPlayer(mark1, board);
                p2 = new HPlayer(mark2);
            }
        }
        else if (choice == 4) {
            if (tossResult == 0) {
                p1 = new NonsenseComputerPlayer(mark1);
                p2 = new SensibleComputerPlayer(mark2, board);
            } else {
                p1 = new SensibleComputerPlayer(mark1, board);
                p2 = new NonsenseComputerPlayer(mark2);
            }
        }
        else {
            cout << "invalid choice"<<endl;
            continue;
        }

        Game g(p1, p2, board);
        g.runGame();

        delete p1;
        delete p2;
        delete board;

        cout << "played again if user want to? (1 for yes & 0 for No): ";
        cin >> playAgain;
    } while (playAgain == 1);

    return 0;
}
