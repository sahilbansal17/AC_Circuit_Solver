/*
    This file will contain the code for scanning and parsing the
    given netlist input to extract the tokens and work on them.
*/
#include <vector>
#include <complex>
#include <algorithm>
#include <string>
using namespace std;

// structure for element to be used in scanning and parsing
struct element{
    char* elementName;
    int elementNum, netStart, netEnd;
    double value; // could be in decimals 
    char* unit;
    
    complex <double> current, voltage, admittance; // the part required for solving the circuit 
    double valWithUnit;  
};

// structure for source to be used in scanning and parsing
struct source{
    char* sourceName;
    int sourceNum, netStart, netEnd;
    double dcOffset, amplitude, freq, delay, dampingFactor;
    // assuming freq in Khz only and delay in S only
    
    // currently assuming dcOffset = 0 
    complex <double> current, voltage; // part required for solving the circuit 
};

// the vector storing the element/source connections
extern vector <element> circuitElements;
extern vector <source> sourceElements;

// the function to be called to parse the netlist fill the vectors
extern int parse(char* fileName);
