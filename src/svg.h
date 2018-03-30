/*
    This file will contain the DECLARATIONS for the svg functions
    defined for drawing various components (resistors, capacitors,
    inductors, voltage source and current source, etc.)
*/

// basic functions 
void start(int h, int w);
void end();
// horizontal drawer functions 
void drawHorizontalLine(int X1, int Y1, int X2);
void drawResistor(int X1, int Y1, int X2);
void drawCapacitor(int X1, int Y1, int X2);
void drawVoltage(int X1, int Y1, int X2);
void drawCurrent(int X1, int Y1, int X2);
void drawInductor(int X1, int Y1, int X2);
// vertical drawer functions 
void drawVerticalLine(int X1, int Y1, int Y2);
