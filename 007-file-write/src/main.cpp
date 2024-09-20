#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::string item;

    std::ifstream file("food.txt");
    file >> item;
    file.close();
    std::cout << item;
}
