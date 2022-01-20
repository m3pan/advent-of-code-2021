#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

struct returnValues {
    std::string s1, s2;
};

struct returnVectors {
    std::vector<std::string> oxygenGeneratorRating, co2ScrubberRating;
};

returnValues findRatings(std::vector<std::string> oxygenGeneratorRatings);
returnVectors splitVector(std::vector<std::string> oxygenGeneratorRatings);
int findBitCriteria(std::vector<std::string> input, int column, std::string type);
int binaryToDecimal(long n);
returnValues findMostCommon(std::vector<std::string> input);
std::vector<std::string> fileToVector03(std::string file);


void day03(){
    // Day 3
    std::vector<std::string> input = fileToVector03("../day03/day3_input.txt");
    // Part One
    auto [epsilonRate, gammaRate] = findMostCommon(input);
    int powerConsumption = binaryToDecimal(std::stol(epsilonRate)) * binaryToDecimal(std::stol(gammaRate));
    std::cout << "What is the power consumption of the submarine? " << powerConsumption << std::endl;
    // Part Two
    auto [oxygenGeneratorRating, co2ScrubberRating] = findRatings(std::vector<std::string> (input));
    long long lifeSupportRating = binaryToDecimal(stol(oxygenGeneratorRating)) * binaryToDecimal(stol(co2ScrubberRating));
    std::cout << "What is the life support rating of the submarine? " << lifeSupportRating << std::endl;

}

returnVectors splitVector(std::vector<std::string> oxygenGeneratorRatings) {
    std::vector<std::string> co2ScrubberRatings;
    /* We find the most common value in the first position and moves all the elements that doesn't have it to a new
     * vector where we will find the CO2 rubber rating. Lastly, we erase the elements removed from the first vector.
     * The two cases are for when the most common value is 0 and 1 respectively. */
    if (findBitCriteria(oxygenGeneratorRatings, 0, "OxygenGeneratorRatings") == '0') {
        // most common value is 0, so we keep them in OxygenGenerator and move the other elements
        // stable_partition maintains relative order in each group
        auto p = std::stable_partition(oxygenGeneratorRatings.begin(), oxygenGeneratorRatings.end(),
                                       [&](const auto& x) { return x[0]=='0'; });
        // range insert with move
        co2ScrubberRatings.insert(co2ScrubberRatings.end(), std::make_move_iterator(p),
                                  std::make_move_iterator(co2ScrubberRatings.end()));
        // erase the elements I removed from the first vector
        oxygenGeneratorRatings.erase(p, oxygenGeneratorRatings.end());
    }
    else {
        // most common value is 1
        auto p = std::stable_partition(oxygenGeneratorRatings.begin(), oxygenGeneratorRatings.end(),
                                       [&](const auto& x) { return x[0]=='1'; });

        co2ScrubberRatings.insert(co2ScrubberRatings.cend(), std::make_move_iterator(p),
                                  std::make_move_iterator(oxygenGeneratorRatings.end()));

        oxygenGeneratorRatings.erase( p,oxygenGeneratorRatings.end());
    }
    return returnVectors{oxygenGeneratorRatings, co2ScrubberRatings};
}

returnValues findRatings(std::vector<std::string> input){
    // we split the vector
    auto [oxygenGeneratorRating, co2ScrubberRating] = splitVector(input);

    int column = 1;
    while(oxygenGeneratorRating.size() > 1) {
        int bitCriteria = findBitCriteria(oxygenGeneratorRating, column, "OxygenGeneratorRatings");
        std::string tmp = std::to_string(bitCriteria);
        char const *bitCriteriaChar = tmp.c_str();
        auto p = std::stable_partition(oxygenGeneratorRating.begin(), oxygenGeneratorRating.end(),
                                       [&column, &bitCriteriaChar](const auto& x) { return x[column] == *bitCriteriaChar; });
        oxygenGeneratorRating.erase(p,oxygenGeneratorRating.end());
        ++column;
    }
    column = 1;

    while(co2ScrubberRating.size() > 1) {
        int bitCriteria = findBitCriteria(co2ScrubberRating, column, "CO2ScrubberRatings");
        std::string tmp = std::to_string(bitCriteria);
        char const *bitCriteriaChar = tmp.c_str();
        auto p = std::stable_partition(co2ScrubberRating.begin(), co2ScrubberRating.end(),
                                       [&column, &bitCriteriaChar](const auto& x) { return x[column] == *bitCriteriaChar; });
        co2ScrubberRating.erase(p,co2ScrubberRating.end());
        ++column;
    }
    return returnValues{ oxygenGeneratorRating[0], co2ScrubberRating[0],};
}

int findBitCriteria(std::vector<std::string> input, int column, std::string type) {
    std::map<bool, int> frequencies{{false, 0},
                                    {true,  0}};
    for (std::string row : input) {
        if (row[column] == '0') {
            frequencies[false] += 1;
        } else if (row[column] == '1') {
            frequencies[true] += 1;
        } else { break; }
    }
    if (type == "OxygenGeneratorRatings") {
        if (frequencies[false] > frequencies[true]) {
            return 0;
        } else { return 1;}
    } else if (type == "CO2ScrubberRatings"){
        if (frequencies[false] > frequencies[true]) {
            return 1;
        } else { return 0;}
    }
    return 666;
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
