/*
    This file will contain the code to draw the different circuit
    elements and connections between them using the functions
    defined in the svg.cpp file
*/

#include "parse.h"
#include "svg.h"
#include <vector>
using namespace std; 

void drawMain(int N, vector <element> el, vector <source> cs, vector <source> vs){
    int E = el.size(); // total number of circuit elements 
    int VS = vs.size(); // total no of voltage sources 
    int CS = cs.size(); // total no of current sources 
    start(1000, 1000);
    drawVerticalLine(250, 0, 900);
    drawVerticalLine(500, 0, 1000);
    drawResistor(250, 250, 500);
    drawCapacitor(250, 500, 500);
    drawInductor(250, 750, 500);
    drawVoltage(250, 850, 500);
    drawHorizontalLine(0, 999, 999);
    end();
}