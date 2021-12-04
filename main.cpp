#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

std::vector<int> fileToVector1(std::string file);
std::vector<std::string>fileToVector2(std::string file);

int main() {
    std::cout << "Hello, World!" << std::endl;
    // Day 1
    std::vector<int> measurements = fileToVector1("../day1_input.txt");
        // Part One
    int increase{0};
    for (int i = 0; i < (measurements.size()); i++) {
        if (measurements[i] < measurements[i + 1]) { ++increase; }
    }
    std::cout << "How many measurements are larger than the previous measurement? " << increase << std::endl;

    // Part Two
    increase = 0;
    for (int i = 0; i < (measurements.size() - 2); i++) {
        int A = measurements[i] + measurements[i + 1] + measurements[i + 2];
        int B = measurements[i + 1] + measurements[i + 2] + measurements[i + 3];
        if (A < B) { ++increase; }
    }
    std::cout << "How many sums are larger than the previous sum? " << increase << std::endl;

    // Day 2
    std::vector<std::string> input = fileToVector2("../day2_input.txt");
    int horizontalPosition{};
    int yourDepth{};
        // Part One
    for (int i = 0; i < input.size()-1; i++) {
        if (input[2*i] == "forward") { horizontalPosition += stoi(input[2*i+1]); }
        else if (input[2*i] == "up") { yourDepth -= stoi(input[2*i+1]); }
        else if (input[2*i] == "down") { yourDepth += stoi(input[2*i+1]); }
    }
    int result = horizontalPosition * yourDepth;
    std::cout << "What do you get if you multiply your final horizontal position "
                 "by your final depth? " << result << std::endl;
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

std::vector<std::string> fileToVector2(std::string file) {
    std::string textLine;
    std::string input{};
    std::ifstream myFile;
    myFile.open(file);
    while (getline(myFile, textLine))
    // textLine is one row in myFile
    {
     input = input + textLine + ' ';
    }
    myFile.close();
    std::vector<std::string> result;
    std::istringstream iss(input);
    for (std::string s; iss >> s; )
        result.push_back(s);
    return result;
}
