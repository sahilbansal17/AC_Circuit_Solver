/*
    This file will contain the DECLARATIONS of functions DEFINED in draw.cpp
*/

void drawMain(int N, vector <element> el, vector <source> cs, vector <source> vs);

/*
N   : total number of nets 
el  : elements (R, L, C)
cs  : current sources 
vs  : voltage sources 
*/

// combining elements and sources into components for ease of drawing 
struct component;

// comparison functions to sort the components based on netEnd  
bool orderByNetEnd(const component &a, const component &b);

