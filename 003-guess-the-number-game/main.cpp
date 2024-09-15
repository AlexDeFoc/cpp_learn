#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>

unsigned int GenerateAns() {
    // Randomise seed
    std::srand(time(0));

    // Make random number
    unsigned int ans = std::rand();

    // Create bounds
    unsigned int min = 0;
    unsigned int max = 10;

    // Return ans
    return (ans % (max - min));
}

class Computer {
private:
    unsigned int m_ans;

public:
    Computer () 
        : m_ans(GenerateAns()) {}

    unsigned int GetAns() {
        return m_ans;
    }
};

class Player {
private:
    unsigned int m_guess;

public:
    void SetGuess(unsigned int guess) {
        m_guess = guess;
    }

    unsigned int GetGuess() {
        return m_guess;
    }
};

int main() {
    Player p;
    Computer c;
    unsigned int PlayerGuess;
    unsigned int tries = 0;

    while (true) {
        std::cout << "Guess: ";
        std::cin >> PlayerGuess;
        p.SetGuess(PlayerGuess);

        if (p.GetGuess() == c.GetAns()) {
            // Guess matches ans
            if (tries > 0) {
                std::cout << "\n\n";
                std::cout << "You win! The real answear was: " << PlayerGuess << "\nYou finished in: " << tries << " tries" << std::endl;
            } else {
                std::cout << "\n\n";
                std::cout << "You win! The real answear was: " << PlayerGuess << "\nYou finished first try!" << std::endl;
            }

            // End game
            break;
        } else {
            // Wrong guess - continue game
            std::cout << "Wrong! Try again!" << std::endl;

            // Increment tries counter
            tries++;

            continue;
        }
    }
}
