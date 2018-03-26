/*
    This file will contain the code(definitions) for the svg
    functions defined for drawing various components (resistors,
    capacitors, inductors, voltage source and current source, etc.)
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream fout;

int llx2, lly2;
void line(int X1, int Y1, int angle) {
    string res;
    if (angle == 0) {
        res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + 50) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(3) +
              "\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + 50) + "\" cy=\"" + to_string(Y1) + "\" r=\"" +
              to_string(3) + "\" />";

        // <text x=X1+50 y=Y1+20 dx="-30">count</text>

        llx2 = X1 + 50;
        lly2 = Y1;
    } else if (angle == 90) {

        res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1) + "\" y2=\"" +
              to_string(Y1 + 50) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(3) +
              "\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1 + 50) + "\" r=\"" +
              to_string(3) + "\" />";

        // <text x=X1+50 y=Y1+20 dx="-30">count</text>

        llx2 = X1;
        lly2 = Y1 + 50;
    }

    fout << res;
}

int lrx2, lry2;

void resistor(int X1, int Y1, int angle) {
    string res;
    // <circle cx="168" cy="200" r="98" stroke="black" stroke-width="4" fill="white" />

    if (angle == 0) {
        // 70      200
        res = "<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(3) +
              "\" />" +

              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + 35) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 35) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + 50) +
              "\" y2=\"" + to_string(Y1 - 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 50) + "\" y1=\"" + to_string(Y1 - 20) + "\" x2=\"" + to_string(X1 + 70) +
              "\" y2=\"" + to_string(Y1 + 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 70) + "\" y1=\"" + to_string(Y1 + 20) + "\" x2=\"" + to_string(X1 + 90) +
              "\" y2=\"" + to_string(Y1 - 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 90) + "\" y1=\"" + to_string(Y1 - 20) + "\" x2=\"" +
              to_string(X1 + 110) + "\" y2=\"" + to_string(Y1 + 20) +
              "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 110) + "\" y1=\"" + to_string(Y1 + 20) + "\" x2=\"" +
              to_string(X1 + 130) + "\" y2=\"" + to_string(Y1 - 20) +
              "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 130) + "\" y1=\"" + to_string(Y1 - 20) + "\" x2=\"" +
              to_string(X1 + 150) + "\" y2=\"" + to_string(Y1 + 20) +
              "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 150) + "\" y1=\"" + to_string(Y1 + 20) + "\" x2=\"" +
              to_string(X1 + 160) + "\" y2=\"" + to_string(Y1 + 20) +
              "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 160) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + 195) +
              "\" y2=\"" + to_string(Y1 + 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + 195) + "\" cy=\"" + to_string(Y1 + 20) +
              "\" r=\"to_string3\" />";

        lrx2 = X1 + 195;
        lry2 = Y1 + 20;


    } else if (angle == 90) {

        res = "<circle id=pointA cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\"r=\"" + to_string(3) +
              "\"/>" +

              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1) + "\" y2=\"" +
              to_string(Y1 + 35) + "\"style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +


              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1 + 35) + "\" x2=\"" + to_string(X1 - 20) +
              "\" y2=\"" + to_string(Y1 + 50) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 - 20) + "\" y1=\"" + to_string(Y1 + 50) + "\" x2=\"" + to_string(X1 + 20) +
              "\" y2=\"" + to_string(Y1 + 70) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 20) + "\" y1=\"" + to_string(Y1 + 70) + " x2=\"" + to_string(X1 - 20) +
              "\" y2=\"" + to_string(Y1 + 90) + " \"style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 - 20) + "\" y1=\"" + to_string(Y1 + 90) + "\" x2=\"" + to_string(X1 + 20) +
              " \"y2=\"" + to_string(Y1 + 110) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2 \"/> " +

              "\n<line x1=\"" + to_string(X1 + 20) + "\" y1=\"" + to_string(Y1 + 110) + "\" x2=\"" +
              to_string(X1 - 20) + "\" y2=\"" + to_string(Y1 + 130) +
              "\"style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 - 20) + "\" y1=\"" + to_string(Y1 + 130) + "\" x2=\"" +
              to_string(X1 + 20) + " \"y2=\"" + to_string(Y1 + 150) +
              "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 20) + "\" y1=\"" + to_string(Y1 + 150) + "\" x2=\"" +
              to_string(X1 + 20) + "\" y2=\"" + to_string(Y1 + 160) +
              "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1 + 160) + " \"x2=\"" + to_string(X1 + 20) +
              "\" y2=\"" + to_string(Y1 + 195) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<circle id=pointA cx=\"" + to_string(X1 + 20) + "\" cy=\"" + to_string(Y1 + 195) + "\" r=\"" +
              to_string(3) + "\" />";


        lrx2 = X1 + 20;
        lry2 = Y1 + 195;

    }

    fout << res;
}


int lcx2, lcy2;

void capacitor(int X1, int Y1, int angle) {
    string res;
    if (angle == 0) {
        //      100  200
        res = "<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1) + "\" x2=\"" + to_string(X1 + 50) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 50) + " \"y1=\"" + to_string(Y1 - 20) + " \"x2=\"" + to_string(X1 + 50) +
              " \"y2=\"" + to_string(Y1 + 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 60) + "\" y1=\"" + to_string(Y1 - 20) + "\" x2=\"" + to_string(X1 + 60) +
              "\" y2=\"" + to_string(Y1 + 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 + 60) + " \"y1=\"" + to_string(Y1) + " \"x2=\"" + to_string(X1 + 110) +
              " \"y2=\"" + to_string(Y1 + 20) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + "\" cy=\"" + to_string(Y1) + "\" r=\"" + to_string(3) +
              "\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + 110) + "\" cy=\"" + to_string(Y1 + 20) + " \"r=\"" +
              to_string(3) + "\" />" +

              "\n<text x=\"" + to_string(X1 + 60) + " \"y=\"" + to_string(Y1 + 50) + "\" dx=\"" + to_string(-30) +
              "\">Capacitor</text>";

        lcx2 = X1 + 110;
        lcy2 = Y1 + 20;
    } else if (angle == 90) {
        res = "<line x1=\"" + to_string(X1) + " \"y1=\"" + to_string(Y1) + " \"x2=\"" + to_string(X1) + " \"y2=\"" +
              to_string(Y1 + 50) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 - 20) + " \"y1=\"" + to_string(Y1 + 50) + "\" x2=\"" + to_string(X1 + 20) +
              "\" y2=\"" + to_string(Y1 + 50) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1 - 20) + "\" y1=" + to_string(Y1 + 60) + " \"x2=\"" + to_string(X1 + 20) +
              " \"y2=\"" + to_string(Y1 + 60) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<line x1=\"" + to_string(X1) + " \"y1=\"" + to_string(Y1 + 60) + "\" x2=\"" + to_string(X1 + 20) +
              " \"y2=\"" + to_string(Y1 + 110) + " \"style=\"stroke:rgb(0,0,0);stroke-width:2\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1) + " \"cy=\"" + to_string(Y1) + "\" r=\"" + to_string(3) +
              "\" />" +

              "\n<circle id=\"pointA\" cx=\"" + to_string(X1 + 20) + "\" cy=\"" + to_string(Y1 + 110) + " \"r=\"" +
              to_string(3) + "\" />" +

              "\n<text x=\"" + to_string(X1 + 50) + "\" y=\"" + to_string(Y1 + 60) + " dx=" + to_string(-30) +
              ">Capacitor</text>";

        lcx2 = X1 + 20;
        lcy2 = Y1 + 110;

    }

    fout << res;
}

int lvx2, lvy2;

void Alt_voltage(int X1, int Y1) {

    string res;

    res = "<circle cx=\"" + to_string(X1 + 40) + "\" cy=\"" + to_string(Y1 + 40) + " \"r=\"" + to_string(40) +
          "\" stroke=\"black\" stroke-width=\"" + to_string(4) + " \"fill=\"white\" />" +

          "\n<path d=M \" " + to_string(X1 - 70) + to_string(Y1 + 40) +
          " \" q 15 -30 30 0  stroke=\" black \"stroke-width=\"" + to_string(5) + "\" fill=\"none\" />" +

          "\n<path d=M \" " + to_string(X1 + 40) + to_string(Y1 + 40) +
          " \" q 15 30 30 0  stroke=\" black \" stroke-width=\"" + to_string(5) + "\"fill=\"none\" />";
    lvx2 = X1 + 80;
    lvy2 = Y1 + 80;
    fout << res;
}

int lix2, liy2;
void Inductor(int X1, int Y1, int angle) {
    string res;
    if (angle == 0) {
        res = "<line x1=\"" + to_string(X1) + " \"y1=\"" + to_string(Y1) + "\"x2=\"" + to_string(X1 + 33) + "\" y2=\"" +
              to_string(Y1) + "\" style=\" stroke:rgb(0,0,0);stroke-width: \"" + to_string(5) + "\" />" +

              "\n<path d=M \"" + to_string(X1 + 33) + to_string(Y1) +
              " \" q 15 30 30 0 stroke=\"black\" stroke-width=\"" + to_string(5) + "\" fill=\"none />" +

              "\n<path d=M \"" + to_string(X1 + 55) + to_string(Y1) +
              " \" q 15 30 30 0 stroke=\"black\" stroke-width=\"" + to_string(5) + " \"fill=\"none />" +

              "\n<path d=M \"" + to_string(X1 + 80) + to_string(Y1) +
              " \" q 15 30 30 0 stroke=\"black\" stroke-width=\"" + to_string(5) + "\" fill=\"none />" +


              "\n<path d=M \"" + to_string(X1 + 105) + to_string(Y1) +
              " \" q 15 30 30 0 stroke=\"black\" stroke-width=" + to_string(5) + "\" fill=\"none />" +

              "\n<line x1=\"" + to_string(X1 + 132) + "\" y1=\"" + to_string(Y1) + " \"x2=\"" + to_string(X1 + 166) +
              "\" y2=\"" + to_string(Y1) + "\" style=\"stroke:rgb(0,0,0);stroke-width:\"" + to_string(5) + "\" /> ";

        lix2 = X1 + 166;
        liy2 = Y1;
    } else if (angle == 90) {
        res = "<line x1=\"" + to_string(X1) + " \"y1=\"" + to_string(Y1) + " \"x2=\"" + to_string(X1) + "\" y2=\"" +
              to_string(Y1 + 33) + " \"style=\"stroke:rgb(0,0,0);stroke-width:\"" + to_string(5) + " />" +

              "\n<path d=M \"" + to_string(X1) + to_string(Y1 + 33) +
              "\" q -30 15 0 30 stroke=\"black\" stroke-width=\"" + to_string(5) + " \"fill=\"none\" />" +

              "\n<path d=M\" " + to_string(X1) + to_string(Y1 + 55) +
              "\" q -30 15 0 30 stroke=\"black\" stroke-width=\"" + to_string(5) + " \"fill=\"none\" />" +

              "\n<path d=M \"" + to_string(X1) + to_string(Y1 + 80) +
              "\" q -30 15 0 30 stroke=\"black\" stroke-width=\"" + to_string(5) + " \"fill=\"none\" />" +

              "\n<path d=M\" " + to_string(X1) + to_string(Y1 + 105) +
              "\" q -30 15 0 30 stroke=\"black\" stroke-width=\"" + to_string(5) + " \"fill=\"none\" />" +

              "\n<line x1=\"" + to_string(X1) + "\" y1=\"" + to_string(Y1 + 132) + "\" x2=\"" + to_string(X1) +
              "\" y2=\"" + to_string(Y1 + 166) + "\" style=\"stroke:rgb(0,0,0);stroke-width:\"" + to_string(5) +
              "\" />";

        lix2 = X1;
        liy2 = Y1 + 166;

    }
    fout << res;
}


void start(int h, int w) {
    fout << "<svg height=\"" << to_string(h) << "\" width= \"" << to_string(w) << "\" xmlns=\"http://www.w3.org/2000/svg\">";
}

void end() {
    fout << "\n</svg>";
}

int main(){
        fout.open("output.svg");
        start(200, 300);
        line(50, 50, 0);
        end();
        fout.close();
    return 0;
}
