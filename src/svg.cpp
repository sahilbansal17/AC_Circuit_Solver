/*
    This file will contain the DECLARATIONS for the svg functions
    defined for drawing various components (resistors, capacitors,
    inductors, voltage source and current source, etc.)
*/

#include <fstream>
#include <string>

using namespace std;

ofstream fout;

void drawHorizontalLine(int X1, int Y1, int X2) {
    string res;
    res = "<line x1=\"" + to_string(X1) + "\"  y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X2) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />";

    // <text x=X1+50 y=Y1+20 dx="-30">count</text>
    fout << res;
}

void drawVerticalLine(int X1, int Y1, int Y2) {
    string res;
    res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1) + "\" y2=\"" +
          to_string(Y2) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y2) + "\" r=\"" +
          to_string(1) + "\" />";

    // <text x=X1+50 y=Y1+20 dx="-30">count</text>
    fout << res;
}

void drawResistor(int X1, int Y1, int X2) {           //minimum 30 t0 50
    float pt = X2 - X1;
    pt = pt - 25;
    pt = pt / 2;
    string res;
    res = "<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +
          "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 5) + "\" cy=\"" + to_string(Y1 - 5) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<line x1=\"" + to_string(X1 + pt) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt + 5) +
          "\" y2=\"" + to_string(Y1 - 5) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 10) + "\" cy=\"" + to_string(Y1 + 5) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<line x1=\"" + to_string(X1 + pt + 5) + "\" y1=\"" + to_string(Y1 - 5) + "\" x2=\"" +
          to_string(X1 + pt + 10) +
          "\" y2=\"" + to_string(Y1 + 5) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 15) + "\" cy=\"" + to_string(Y1 - 5) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<line x1=\"" + to_string(X1 + pt + 10) + "\" y1=\"" + to_string(Y1 + 5) + "\" x2=\"" +
          to_string(X1 + pt + 15) +
          "\" y2=\"" + to_string(Y1 - 5) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 20) + "\" cy=\"" + to_string(Y1 + 5) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<line x1=\"" + to_string(X1 + pt + 15) + "\" y1=\"" + to_string(Y1 - 5) + "\" x2=\"" +
          to_string(X1 + pt + 20) + "\" y2=\"" + to_string(Y1 + 5) +
          "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 25) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<line x1=\"" + to_string(X1 + pt + 20) + "\" y1=\"" + to_string(Y1 + 5) + "\" x2=\"" +
          to_string(X1 + pt + 25) + "\" y2=\"" + to_string(Y1) +
          "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 25) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" +
          to_string(X2) + "\" y2=\"" + to_string(Y1) +
          "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          // "\n<line x1=\"" + to_string(X1 + 150) + "\" y1=\"" + to_string(Y1 + 20) + "\" x2=\"" +
          // to_string(X1 + 160) + "\" y2=\"" + to_string(Y1 ) +
          // "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          // "\n<line x1=\"" + to_string(X1 + 160) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + 195) +
          // "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X2) + "\" cy=\"" + to_string(Y1) +
          "\" r= \" " + to_string(1) + "\" />";
    fout << res;
}

void drawCapacitor(int X1, int Y1, int X2) {       // minimum 10
    float pt = X2 - X1;
    pt = pt - 4;
    pt = pt / 2;
    string res;
    res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt) + "\" y1=\"" + to_string(Y1 - 4) + "\" x2=\"" + to_string(X1 + pt) +
          "\" y2=\"" + to_string(Y1 + 4) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 4) + "\" y1=\"" + to_string(Y1 - 4) + "\" x2=\"" +
          to_string(X1 + pt + 4) +
          "\" y2=\"" + to_string(Y1 + 4) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 4) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X2) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />";

    // "\n<text x=\"" + to_string(X1 + 60) + " \" y=\"" + to_string(Y1 + 50) + "\" dx=\"" + to_string(-30) +
    // "\">Capacitor</text>";
    fout << res;

}

void drawVoltage(int X1, int Y1, int X2) {
    float pt = X2 - X1;
    pt = pt - 20;
    pt = pt / 2;
    string res;
    res = "<circle cx=\"" + to_string(X1 + pt + 10) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(10) +
          "\" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"white\" />" +

          "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 20) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<path d=\"M " + to_string(X1 + pt + 10) + " " + to_string(Y1) +
          " q 2.5 -5 5 0\" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"none\" />" +

          "\n<path d=\"M " + to_string(X1 + pt + 5) + " " + to_string(Y1) +
          " q 2.5 5 5 0\" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"none\" />";
    fout << res;

}

void drawCurrent(int X1, int Y1, int X2) {
    float pt = X2 - X1;
    pt = pt - 20;
    pt = pt / 2;
    string res;
    res = "<circle cx=\"" + to_string(X1 + pt + 10) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(10) +
          "\" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"white\" />" +

          "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 20) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 2) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt + 5) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 15) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" +
          to_string(X1 + pt + 18) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />" +

          "\n<line x1=\"" + to_string(X1 + pt + 16.5) + "\" y1=\"" + to_string(Y1 - 1.5) + "\" x2=\"" +
          to_string(X1 + pt + 16.5) +
          "\" y2=\"" + to_string(Y1 + 1.5) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />";


    fout << res;

}


void drawInductor(int X1, int Y1, int X2) {       // minimum 30
    float pt = X2 - X1;
    pt = pt - 20;
    pt = pt / 2;
    string res;
    res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) + "\" y2=\"" +
          to_string(Y1) + "\" style=\" stroke:rgb(0,0,0);stroke-width: " + to_string(2) + "\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +
          "\n<path d=\"M " + to_string(X1 + pt) + " " + to_string(Y1) +
          "  q 2.5 5 5 0 \" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"none\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 5) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<path d=\"M " + to_string(X1 + pt + 5) + " " + to_string(Y1) +
          "  q 2.5 5 5 0 \" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"none\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 10) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<path d=\"M " + to_string(X1 + pt + 10) + " " + to_string(Y1) +
          "  q 2.5 5 5 0 \" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"none\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 15) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<path d=\"M " + to_string(X1 + pt + 15) + " " + to_string(Y1) +
          "  q 2.5 5 5 0 \" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"none\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + pt + 20) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
          to_string(1) + "\" />" +
          "\n<line x1=\"" + to_string(X1 + pt + 20) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
          "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:" + to_string(2) + "\" /> ";
    fout << res;

}


void start(int h, int w) {
    fout.open("output.svg");
    fout << "<svg height=\"" << to_string(h) << "\" width= \"" << to_string(w)
         << "\" xmlns=\"http://www.w3.org/2000/svg\">";
}

void end() {
    fout << "\n</svg>";
    fout.close();
}

int main() {
    start(1000, 1000);
    drawVerticalLine(5, 10, 25);
    drawResistor(25, 25, 75);
    drawCapacitor(50, 50, 100);
    drawInductor(100, 100, 150);
    drawVoltage(150, 150, 200);
    drawCurrent(200, 200, 250);
    end();
    fout.close();
    return 0;
}
