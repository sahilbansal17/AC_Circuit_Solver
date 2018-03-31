/*
    This file will contain the DEFINITIONS for the svg functions
    for drawing various components (resistors, capacitors,
    inductors, voltage source and current source, etc.)
*/

#include <fstream>

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
          
    fout << res;
}

void drawVerticalLine(int X1, int Y1, int Y2, float width) {
    string res;
    res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1) + "\" y2=\"" +
          to_string(Y2) + "\" style=\"stroke:rgb(0,0,0);stroke-width:"+to_string(width)+"\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(1) +
          "\" />" +

          "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y2) + "\" r=\"" +
          to_string(1) + "\" />";

    fout << res;
}

void drawResistor(int X1, int Y1, int X2) {           //minimum 30 to 50
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

void drawCurrent(int X1, int Y1, int X2, bool np) {
    float pt = X2 - X1;
    pt = pt - 20;
    pt = pt / 2;
    string res;
    if (np == true) {

        res = "<circle cx=\"" + to_string(X1 + pt + 10) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(10) +
              "\" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"white\" />" +

              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 20) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 2) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" +
              to_string(X1 + pt + 5) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 15) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" +
              to_string(X1 + pt + 18) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 16.5) + "\" y1=\"" + to_string(Y1 - 1.5) + "\" x2=\"" +
              to_string(X1 + pt + 16.5) +
              "\" y2=\"" + to_string(Y1 + 1.5) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />";
    } else {
        res = "<circle cx=\"" + to_string(X1 + pt + 10) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(10) +
              "\" stroke=\"black\" stroke-width=\"" + to_string(2) + "\" fill=\"white\" />" +

              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + pt) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 20) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X2) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 2) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" +
              to_string(X1 + pt + 5) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 15) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" +
              to_string(X1 + pt + 18) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />" +

              "\n<line x1=\"" + to_string(X1 + pt + 3.5) + "\" y1=\"" + to_string(Y1 - 1.5) + "\" x2=\"" +
              to_string(X1 + pt + 3.5) +
              "\" y2=\"" + to_string(Y1 + 1.5) + "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />";
    }
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

void drawText(string txt, int X1, int Y1) {
    string res;
    
    res = "<g font-size=\"" + to_string(10) +
          "\" font-family=\"sans-serif\" fill=\"black\" stroke=\"none\" text-anchor=\"middle\">" +
          "\n<text x=\"" + to_string(X1) + "\" y=\"" + to_string(Y1) + "\">"+txt+"</text>" +
          "\n</g>";
    fout << res;
}

void start(string fileName, int h, int w) {
    fout.open(fileName);
    fout << "<svg height=\"" << to_string(h) << "\" width= \"" << to_string(w)
         << "\" xmlns=\"http://www.w3.org/2000/svg\">";
}

void end() {
    fout << "\n</svg>";
    fout.close();
}

