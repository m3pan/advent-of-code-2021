#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> readFile(std::string file);

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> measurements = readFile("../day1_input.txt");
    // Part One
    int increase{0};
    for (int i = 0; i < (measurements.size()); i++) {
        if (measurements[i] < measurements[i + 1]) { ++increase; }
    }
    std::cout << "How many measurements are larger than the previous measurement? " << increase << std::endl;

    // Part two
    increase = 0;
    for (int i = 0; i < (measurements.size()-2); i++) {
        int A = measurements[i] + measurements[i+1] + measurements[i+2];
        int B = measurements[i+1] + measurements[i+2] + measurements[i+3];
        if (A < B) {++increase;}
    }
    std::cout << "How many sums are larger than the previous sum? " << increase << std::endl;
}

std::vector<int> readFile(std::string file) {
    std::string textLine;
    std::ifstream myFile;
    myFile.open(file);
    std::vector<int> input;
    while (getline(myFile, textLine)) // add a third argument to get an optional delimiter
    {
        int number = std::stoi(textLine); //convert from string to int
        input.push_back(number);
    }
    myFile.close();
    return input;
    }
