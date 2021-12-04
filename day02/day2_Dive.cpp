#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<std::string>fileToVector2(std::string file);

void day02() {
    // Day 2
    std::vector<std::string> input = fileToVector2("../day02/day2_input.txt");
    int horizontalPosition{};
    int yourDepth{};
    // Part One
    for (int i = 0; i < input.size()-1; i++) {
        if (input[2*i] == "forward") { horizontalPosition += stoi(input[2*i+1]); }
        else if (input[2*i] == "up") { yourDepth -= stoi(input[2*i+1]); }
        else if (input[2*i] == "down") { yourDepth += stoi(input[2*i+1]); }
    }
    int result = horizontalPosition * yourDepth;
    std::cout << "Day 2: What do you get if you multiply your final horizontal position "
                 "by your final depth? " << result << std::endl;

    // Part Two
    int aim{};
    horizontalPosition = 0;
    yourDepth = 0;
    for (int i = 0; i < input.size()-1; i++) {
        if (input[2*i] == "down") {
            aim += stoi(input[2*i+1]);
        }
        else if (input[2*i] == "up") {
            aim -= stoi(input[2*i+1]);
        }
        else if (input[2*i] == "forward") {
            horizontalPosition += stoi(input[2*i+1]);
            yourDepth += aim * stoi(input[2*i+1]);
        }
    }
    result = horizontalPosition * yourDepth;
    std::cout << "Day 2: What do you get if you multiply your final horizontal position by your final "
                 "depth? " << result << std::endl;
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
