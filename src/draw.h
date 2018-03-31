/*
    This file will contain the DECLARATIONS of functions DEFINED in draw.cpp
*/

void drawMain(string fileName, int N, vector <element> el, vector <source> so);

/*
N   : total number of nets 
el  : elements (R, L, C)
so  : sources
*/

// combining elements and sources into components for ease of drawing 
struct component;

// comparison functions to sort the components based on netEnd  
bool orderByNetEnd(const component &a, const component &b);

// to draw an individual component
inline void drawComponent(component c, int xCor1, int yCor, int xCor2, int cmax = 0);

// function for rounding decimal upto 3 places 
inline double roundMe(double val);