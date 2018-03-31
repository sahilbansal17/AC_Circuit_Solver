/*
    This file will contain the DECLARATIONS of functions DEFINED in draw.cpp
*/

void drawMain(string fileName, int N, vector <element> el, vector <source> cs, vector <source> vs);

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

// to draw an individual component
inline void drawComponent(char name, int num, bool updated, int xCor1, int yCor, int xCor2, int cmax = 0);