#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> fileToVector1(std::string file);

void day01() {
    std::cout << "Hello, World!" << std::endl;
    // Day 1
    std::vector<int> measurements = fileToVector1("../day01/day1_input.txt");
        // Part One
    int increase{0};
    for (int i = 0; i < (measurements.size()); i++) {
        if (measurements[i] < measurements[i + 1]) { ++increase; }
    }
    std::cout << "Day 1: How many measurements are larger than the previous measurement? " << increase << std::endl;

        // Part Two
    increase = 0;
    for (int i = 0; i < (measurements.size() - 2); i++) {
        int A = measurements[i] + measurements[i + 1] + measurements[i + 2];
        int B = measurements[i + 1] + measurements[i + 2] + measurements[i + 3];
        if (A < B) { ++increase; }
    }
    std::cout << "Day 1: How many sums are larger than the previous sum? " << increase << std::endl;
}

std::vector<int> fileToVector1(std::string file) {
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