#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define tableSize 3

class Bot {
private:
    int m_Level;

public:
    enum Level {
        Random = 0,
    };

private:
    void RandomGuess(std::string (&Miss)[tableSize][tableSize]) {
        int prevGuessRow = -1;
        int prevGuessCol = -1;

        while (true) {
            // Generate random guess for row and column
            int guessRow = std::rand() % tableSize;
            int guessCol = std::rand() % tableSize;

            // Ensure guess is different from previous
            if (guessRow != prevGuessRow || guessCol != prevGuessCol) {
                if (Miss[guessRow][guessCol] == "_") {
                    std::cout << "Guess: (" << guessRow << ", " << guessCol << ")" << std::endl;
                    Miss[guessRow][guessCol] = "o";
                    prevGuessRow = guessRow;
                    prevGuessCol = guessCol;
                    break;
                }
            }
        }
    }

public:
    void SetLevel(Level level) {
        m_Level = level;
    }

    void Guess(std::string (&Miss)[tableSize][tableSize]) {
        if (m_Level == Random) {
            RandomGuess(Miss);
        }
    }

    void PrintLevel() {
        std::cout << m_Level << std::endl;
    }
};

void PrintBoard(const std::string (&Board)[tableSize][tableSize]) {
    // Print column numbers
    std::cout << "  ";
    for (int j = 0; j < tableSize; j++) {
        std::cout << " " << j + 1 << " ";  // Print column numbers starting from 1
    }
    std::cout << std::endl;

    // Print rows
    for (int i = 0; i < tableSize; i++) {
        std::cout << i + 1 << " ";  // Print row numbers starting from 1
        for (int j = 0; j < tableSize; j++) {
            std::cout << "[" << Board[i][j] << "] ";
        }
        std::cout << std::endl;
    }
}

bool CheckWinner(const std::string (&Board)[tableSize][tableSize]) {
    // Check rows for winner
    for (int i = 0; i < tableSize; i++) {
        bool rowWin = true;
        for (int j = 1; j < tableSize; j++) {
            if (Board[i][j] != Board[i][0] || Board[i][0] == "_") {
                rowWin = false;
                break;
            }
        }
        if (rowWin) {
            std::cout << "Winner is: " << Board[i][0] << " (row " << i + 1 << ")" << std::endl;
            return true;
        }
    }

    // Check columns for winner
    for (int j = 0; j < tableSize; j++) {
        bool colWin = true;
        for (int i = 1; i < tableSize; i++) {
            if (Board[i][j] != Board[0][j] || Board[i][j] == "_") {
                colWin = false;
                break;
            }
        }
        if (colWin) {
            std::cout << "Winner is: " << Board[0][j] << " (column " << j + 1 << ")" << std::endl;
            return true;
        }
    }

    // Check main diagonal for winner
    bool mainDiagWin = true;
    for (int i = 1; i < tableSize; i++) {
        if (Board[i][i] != Board[0][0] || Board[i][i] == "_") {
            mainDiagWin = false;
            break;
        }
    }
    if (mainDiagWin) {
        std::cout << "Winner is: " << Board[0][0] << " (main diagonal)" << std::endl;
        return true;
    }

    // Check reversed diagonal for winner
    bool reversedDiagWin = true;
    for (int i = 1; i < tableSize; i++) {
        if (Board[i][tableSize - 1 - i] != Board[0][tableSize - 1] || Board[i][tableSize - 1 - i] == "_") {
            reversedDiagWin = false;
            break;
        }
    }
    if (reversedDiagWin) {
        std::cout << "Winner is: " << Board[0][tableSize - 1] << " (reversed diagonal)" << std::endl;
        return true;
    }

    // No winner found
    return false;
}

int main() {
    std::srand(std::time(0));

    Bot cpu;
    cpu.SetLevel(Bot::Random);

    std::string CheckBoard[tableSize][tableSize] = {
        {"_", "_", "_"},
        {"_", "_", "_"},
        {"_", "_", "_"},
    };

    PrintBoard(CheckBoard);

    int pX = -1;
    int pY = -1;
    int emptySlots = tableSize * tableSize;

    while (emptySlots > 0) {
        std::cout << "Enter X coordinate (1-" << tableSize << "): ";
        std::cin >> pX;

        if (pX < 1 || pX > tableSize) {
            std::cout << "Invalid X coordinate. Try again." << std::endl;
            continue;
        }

        pX -= 1;  // Adjust for 0-based index

        std::cout << "Enter Y coordinate (1-" << tableSize << "): ";
        std::cin >> pY;

        if (pY < 1 || pY > tableSize) {
            std::cout << "Invalid Y coordinate. Try again." << std::endl;
            continue;
        }

        pY -= 1;  // Adjust for 0-based index

        if (CheckBoard[pX][pY] != "_") {
            std::cout << "Cell already taken. Try another cell." << std::endl;
            continue;
        }
        CheckBoard[pX][pY] = "x";
        cpu.Guess(CheckBoard);

        PrintBoard(CheckBoard);

        if (CheckWinner(CheckBoard)) {
            std::cout << "Game over. We have a winner!" << std::endl;
            break;
        }

        emptySlots--;
        if (emptySlots == 0) {
            std::cout << "The game ended in a draw!" << std::endl;
            break;
        }
    }

    return 0;
}
