#include <map>
#include <vector>
struct returnValues {
    std::string s1, s2;
};
std::vector<std::string> fileToVector03(std::string file);
returnValues findMostCommon(std::vector<std::string> input);
int binaryToDecimal(long n);

void day03(){
    std::vector<std::string> input = fileToVector03("../day03/day3_input.txt");
    auto [epsilonRate, gammaRate] = findMostCommon(input);
    int powerConsumption = binaryToDecimal(std::stol(epsilonRate)) * binaryToDecimal(std::stol(gammaRate));
    std::cout << "What is the power consumption of the submarine? " << powerConsumption << std::endl;
}

int binaryToDecimal(long n)
{
    int decValue{};
    int baseValue = 1;
    while (n) {
        long lastDigit = n % 10;
        n = n / 10;
        decValue += lastDigit * baseValue;
        baseValue = baseValue * 2;
    }
    return decValue;
}

returnValues findMostCommon(std::vector<std::string> input){
    std::stringstream ssEpsilonRate;
    std::stringstream ssGammaRate;
    for (int column = 0; column < input[0].length(); column++) {
        std::map<bool, int> frequencies{{false, 0},{true, 0}};
        for (std::string row : input) {
            if (row[column] == '0') {
                frequencies[false] += 1;
            } else if (row[column] == '1') {
                frequencies[true] += 1;
            } else { std::cout << "fuck" << std::endl; }
        }
        if (frequencies[false] > frequencies[true]) {
            ssEpsilonRate << "0";
            ssGammaRate << "1";
        } else {
            ssEpsilonRate << "1";
            ssGammaRate << "0";
        }

    }
    std::string epsilonRate = ssEpsilonRate.str();
    std::string gammaRate = ssGammaRate.str();

    return returnValues{epsilonRate, gammaRate};
}

std::vector<std::string> fileToVector03(std::string file){
    std::ifstream ifs{file};
    std::istream_iterator<std::string> start{ifs};
    std::istream_iterator<std::string> end{};
    std::vector<std::string> text{};
    std::copy(start, end, std::back_inserter(text));
    return text;
}
