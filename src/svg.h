/*
    This file will contain the DECLARATIONS for the svg functions
    defined for drawing various components (resistors, capacitors,
    inductors, voltage source and current source, etc.)
*/

// basic functions 
void start(string fileName, int h, int w);
void end();
// horizontal drawer functions 
void drawHorizontalLine(int X1, int Y1, int X2);
void drawResistor(int X1, int Y1, int X2);
void drawCapacitor(int X1, int Y1, int X2);
void drawVoltage(int X1, int Y1, int X2);
void drawCurrent(int X1, int Y1, int X2, bool np);
void drawInductor(int X1, int Y1, int X2);
// vertical drawer functions 
void drawVerticalLine(int X1, int Y1, int Y2, float width); // width specified to adjust nets 0 and N-1 
// text drawing
void drawText(string txt, int X1, int Y1);