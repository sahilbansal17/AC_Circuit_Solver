/*
    This file will contain the code for scanning and parsing the
    given netlist input to extract the tokens and work on them.
*/
#include <vector>
using namespace std;

// structure for element to be used in scanning and parsing
struct element{
    char* elementName;
    int elementNum, netStart, netEnd, value;
    char* unit;
};

// structure for source to be used in scanning and parsing
struct source{
    char* sourceName;
    int sourceNum, netStart, netEnd;
    double dcOffset, amplitude, freq, delay, dampingFactor;
    // assuming freq in Khz only and delay in S only
};

// the vector storing the element/source connections
extern vector <element> circuitElements;
extern vector <source> sourceElements;

// the function to be called to parse the netlist fill the vectors
extern int parse(char* fileName);
