#include <cmath>
#include <vector>
#include <string>
#include <iostream>

class Table {
private:
    const int m_Size;
    std::vector<std::string> m_Board;
    int m_EmptySlots;
    std::string Winner;

public:
    Table (const int size)
        : m_Size(size*size), m_Board(size*size), m_EmptySlots(size*size)
    {
        for (int i = 0; i < size*size; i++) {
            m_Board[i] = "_";
        }
    }

    const int GetSize() {
        return int(sqrt(m_Size));
    }

    int GetEmpty() {
        return m_EmptySlots;
    }

    bool Add(std::string symbol, const int slot, const int row) {
        if (m_Board[(row-1)*int(sqrt(m_Size))+slot-1] == "_") {
            m_Board[(row-1)*int(sqrt(m_Size))+slot-1] = symbol;
            m_EmptySlots--;
            return true;
        }
        return false;
    }

    void Reset() {
        for (int i = 0; i < m_Size; i++) {
            m_Board[i] = "_";
        }
    }

    void Print() {
        for (int i = 1; i < m_Size+1; i++) {
            std::cout << m_Board[i-1];
            if (i % int(sqrt(m_Size)) == 0) {
                    std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    bool CheckWinner() {
        int size = int(sqrt(m_Size));
        bool rowMatched, colMatched, diagMatched, antiDiagMatched = true;
        std::string firstElement;

        // Get first elements for diagonal and anti-diagonal checks
        std::string diagFirstElement = m_Board[0];
        std::string antiDiagFirstElement = m_Board[size - 1];

        // If the first diagonal or anti-diagonal element is "_", skip those checks
        if (diagFirstElement == "_") diagMatched = false;
        if (antiDiagFirstElement == "_") antiDiagMatched = false;

        for (int i = 0; i < size; i++) {
            // Check rows
            rowMatched = true;
            firstElement = m_Board[i * size];
            if (firstElement != "_") {
                for (int j = 1; j < size; j++) {
                    if (m_Board[i * size + j] != firstElement) {
                        rowMatched = false;
                        break;
                    }
                }
                if (rowMatched) {
                    Winner = firstElement;
                    return true;
                }
            }

            // Check columns
            colMatched = true;
            firstElement = m_Board[i];
            if (firstElement != "_") {
                for (int j = 1; j < size; j++) {
                    if (m_Board[j * size + i] != firstElement) {
                        colMatched = false;
                        break;
                    }
                }
                if (colMatched) {
                    Winner = firstElement;
                    return true;
                }
            }

            // Check main diagonal
            if (diagMatched && m_Board[i * size + i] != diagFirstElement) {
                diagMatched = false;
            }

            // Check anti-diagonal
            if (antiDiagMatched && m_Board[i * size + (size - 1 - i)] != antiDiagFirstElement) {
                antiDiagMatched = false;
            }
        }

        // Check if diagonals matched and not "_"
        if (diagMatched && diagFirstElement != "_") {
            Winner = diagFirstElement;
            return true;
        }
        if (antiDiagMatched && antiDiagFirstElement != "_") {
            Winner = antiDiagFirstElement;
            return true;
        }

        return false;
    }

    const std::string GetWinner() {
        return Winner;
    }
};

class Bot {
private:
    int guess;
    const int m_Level;
    const int m_TableSize;

public:
    enum Level {
        Random
    };

    Bot (const Level level, const int size)
        : m_Level(level), m_TableSize(size) {}

    const int Guess() {
        // Make a random guess
        if (m_Level == Random) {
            // Make guess
            guess = std::rand() % m_TableSize + 1;
            return guess;
        }

        return 0;
    }
};

int main() {
    // Generate seed
    srand(time(0));

    // Create table
    Table b(3);

    // Create Bot
    Bot cpu(Bot::Random, b.GetSize());

    // Create user input container
    int slot;
    int row;

    while(b.GetEmpty() > 0) {
        // Get user input
        std::cout << "Select a slot <1-3>: ";
        std::cin >> slot;
        std::cout << std::endl;
        std::cout << "Select a row <1-3>: ";
        std::cin >> row;
        std::cout << std::endl;

        // Add user input
        if (b.GetEmpty() > 0 && b.Add("x", slot, row) == false) {
            std::cout << "Invalid position" << std::endl;
            continue;
        }
        
        // Make & add cpu guess
        while (b.GetEmpty() > 0 && !b.Add("o", cpu.Guess(), cpu.Guess()));

        // Print current table
        b.Print();
        if (b.CheckWinner()) {
            break;
        }
    }

    std::cout << "Winner is: " << b.GetWinner() << std::endl;
}
