struct Board;
struct returnData{
    std::vector<int> numbers;
    std::vector<Board*> boards;
};

returnData createMatrices(const std::string& file);
typedef int matrix[5][5];
#define ROW(n) (*(*val+((n)*5)+0),*(*val+((n)*5)+1), *(*val+((n)*5)+2), *(*val+((n)*5)+3, *(*val+((n)*5)+4)))

struct Board {
    explicit Board(matrix val) : values{{val[0][0], val[0][1], val[0][2], val[0][3], val[0][4]},
                                   {val[1][0], val[1][1], val[1][2], val[1][3], val[1][4]},
                                   {val[2][0], val[2][1], val[2][2], val[2][3], val[2][4]},
                                   {val[3][0], val[3][1], val[3][2], val[3][3], val[3][4]},
                                   {val[4][0], val[4][1], val[4][2], val[4][3], val[4][4]}}
    {}
    //Board(mat val) : values{ROW(0), ROW(1), ROW(2),ROW(3), ROW(4)} {} //TODO: Constructor using Macro

    matrix values;
    bool markedValues[5][5]{};
    static bool bingo(); //TODO
    void markValues(int input); //TODO
};

bool Board::bingo() { return false; }

void Board::markValues(int input) {}

void day04(){
    // Part One
    auto [numbers, boards] = createMatrices("../day04/day4_test.txt");
}

returnData createMatrices(const std::string& file) {
    /** Read file, thereafter place numbers in vector vector and create a Board for each set of 5x5 grid of numbers.
     * Lastly, we return a vector with all randomly chosen numbers and a vector with pointers to all boards **/
    std::vector<std::string> s = fileToVector03("../day04/day4_test.txt");
    std::string stringNumbers = s[0];
    std::stringstream ss(stringNumbers);
    std::vector<int> numbers;
    while(ss.good())
    {
        std::string substr;
        getline(ss, substr, ',');
        numbers.push_back(std::stoi(substr));
    }
    s.erase(s.begin());

    // Type conversion to every element
    std::vector<int> i(s.size());
    std::transform(s.begin(), s.end(), i.begin(), [](const std::string& val)
    {
        return std::stoi(val);
    });
    std::vector<Board*> boards;

    while(!i.empty()){
        matrix board = {{i[0],i[1],i[2],i[3],i[4]},
                     {i[5],i[6],i[7],i[8],i[9]},
                     {i[10],i[11],i[12],i[13],i[14]},
                     {i[15],i[16],i[17],i[18],i[19]},
                     {i[20],i[21],i[22],i[23],i[24]}};

        auto* m = new Board{board};
        boards.push_back(m);
        i.erase(i.begin(),i.begin()+25);
    }
    return returnData{numbers, boards};
}


