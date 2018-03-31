/*
    This file will contain the code to draw the different circuit
    elements and connections between them using the functions
    defined in the svg.cpp file
*/

#include "parse.h"
#include "svg.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std; 

// combining elements and sources into components for ease of drawing 
struct component{
    char* name;
    int num, netStart, netEnd;
    double value; 
    complex <double> current, voltage; 
    bool updated; // tells whether netStart and netEnd are swapped or not  
};

// comparison function to sort the components based on netEnd  
bool orderByNetEnd(const component &a, const component &b){
    return a.netEnd <= b.netEnd; // two components CAN have the same netEnd since THEN their diff between netEnds is same in the vector
}

inline void drawComponent(char name, int num, bool updated, int xCor1, int yCor, int xCor2, int cmax = 0){
    switch(name){
        case 'R':
                drawResistor(xCor1, yCor + cmax*30, xCor2);
                drawText("R"+to_string(num),(xCor1 + xCor2)/2, yCor + cmax*30 - 10);
                break;
        case 'L':
                drawInductor(xCor1, yCor + cmax*30, xCor2);
                drawText("L"+to_string(num),(xCor1 + xCor2)/2, yCor + cmax*30 - 10);
                break;
        case 'C':
                drawCapacitor(xCor1, yCor + cmax*30, xCor2);
                drawText("C"+to_string(num),(xCor1 + xCor2)/2, yCor + cmax*30 - 10);
                break;
        case 'V':
                drawVoltage(xCor1, yCor + cmax*30, xCor2);
                drawText("V"+to_string(num),(xCor1 + xCor2)/2, yCor + cmax*30 - 10);
                break;
        case 'I':
                drawCurrent(xCor1, yCor, xCor2, updated); // draw +ve at ns and -ve at ne
                drawText("I"+to_string(num),(xCor1 + xCor2)/2, yCor + cmax*30 - 10);
                break;
    }
}

void drawMain(string fileName, int N, vector <element> el, vector <source> cs, vector <source> vs){
    int E = el.size(); // total number of circuit elements 
    int VS = vs.size(); // total no of voltage sources 
    int CS = cs.size(); // total no of current sources 
    
    int distBWnets = 50 ; // fixed 
    int xNets[N]; // x coordinates of nets
    int yStart = 200, yEnd; // end points for vertical nets 
    xNets[0] = 200;
    for(int i = 1; i < N; i ++){
        xNets[i] = xNets[i-1] + distBWnets;
    }
    
    int height = 200 + 30*(E + VS + CS) + 40 ; // this is the max possible height, all connections in parallel, each connection has height of around 30, extra 40 for text 
    int width = xNets[N-1] + 100; // maximum width of the screen 
    start(fileName, height, width);
    
    vector < vector <component> > ordByNetDiff(N); // diff from 1 to N-1 (since total N nets, 0 till N-1) possible for these components  
    int yNet = 200; // this will store the starting yCor for next elements to be drawn 
    
    component c;

    // netStart is ensured smaller than netEnd for all the components to make sure that drawing happens properly 
    for(int i = 0 ; i < E ; i ++){
        c.name      =   el[i].elementName;
        c.num       =   el[i].elementNum;
        c.value     =   el[i].valWithUnit;
        c.current   =   el[i].current;
        c.voltage   =   el[i].voltage;
        int ns = el[i].netStart, ne = el[i].netEnd;
        if(ns > ne){
            swap(ns, ne);
            c.updated = 1;
        }
        int diff = ne - ns;
        c.netStart  =   ns;
        c.netEnd    =   ne;
        ordByNetDiff[diff].push_back(c);
    }
    
    for(int i = 0 ; i < VS ; i ++){
        c.name      =   vs[i].sourceName;
        c.num       =   vs[i].sourceNum;
        c.value     =   vs[i].amplitude;
        c.current   =   vs[i].current;
        c.voltage   =   vs[i].voltage;
        int ns = vs[i].netStart, ne = vs[i].netEnd;
        if(ns > ne){
            swap(ns, ne);
            c.updated = 1;
        }
        int diff = ne - ns;
        c.netStart  =   ns;
        c.netEnd    =   ne;
        ordByNetDiff[diff].push_back(c);
    }
    for(int i = 0 ; i < CS ; i ++){
        c.name      =   cs[i].sourceName;
        c.num       =   cs[i].sourceNum;
        c.value     =   cs[i].amplitude;
        c.current   =   cs[i].current;
        c.voltage   =   cs[i].voltage;
        int ns = cs[i].netStart, ne = cs[i].netEnd; 
        if(ns > ne){
            swap(ns, ne);
            c.updated = 1;
        }
        int diff = ne - ns;
        c.netStart  =   ns;
        c.netEnd    =   ne;
        ordByNetDiff[diff].push_back(c);
    }
    
    /*
    algorithm followed is :
    1. 
        ordByNetDiff[i] contains components whose netStart and netEnd differ by amount of i. 
    2.
        sort each vector ordByNetDiff[i] based on the netEnd so that a greedy technique can be used to draw the MAXIMUM disjoint set of components of a particular "net difference value"
    3.    
        for i = maxNetDifference->1 // changed since better visualization obtained 
            while totalDrawnComponents not equal to DrawnComponentsWithNetDifference "i"
                draw all those components that can have the same yCor based on the greedy technique 
                
                update yNet by 30 (since no more components can be drawn on the same line without an overlap)
    
    THE PREVIOUS IMPLEMENTATION ALGO IS NOT APPROPRIATE WHEN TWO ELEMENTS HAVING THE SAME NET START AND NET END 
    
    CHANGES:
        If more than two components have same net end and net start, 
        draw them in parallel in the same iteration but increment yNet by 30*(max no of such components between any two nets in this iteration)
        to avoid conflicts (overlaps) in the next iteration 
    
    */
    
    // sort all vectors ordByNetDiff[i] on the basis of the ending nets, so that disjoint segments can be drawn on the same yCor 
    for(int i = 0 ; i < N ; i ++){
        sort(ordByNetDiff[i].begin(), ordByNetDiff[i].end(), orderByNetEnd);
    }
    
    for(int i = N-1 ; i >= 1 ; i --){
        // no of components to draw 
        int drawComp = ordByNetDiff[i].size();
        int xCor1, xCor2, yCor, ns, ne;
        char name;
        // component c; already declared 
        vector <int> visitedC (drawComp, 0); // to mark visited onces 
        // drawing disjoint set of components at once, so that yNet can be updated at next iteration 
        int countedC = 0, startC = 0;
        // startC for 1st component in each iteration 
        while(countedC != drawComp){
            // int yIncrement = 30; // default 
            int maxBWtwoNets = 1; // default 
            // yNet += 30 * maxBWtwoNets; this will be used at the end of iteration now 
            int flagUpdatedStart = 0;
            // draw 1st component (startC) independently so that ns and ne can be updated accordingly
            c = ordByNetDiff[i][startC];
            ns = c.netStart; ne = c.netEnd;
            name = c.name[0];
            xCor1 = xNets[ns], xCor2 = xNets[ne];
            yCor = yNet;
            // cout << "Drawing " << name << ": " << ns << " to " << ne << "\n";
            drawComponent(name, c.num, c.updated, xCor1, yCor, xCor2);
            visitedC[startC] = 1;
            countedC ++;
            int cmax = 1; // for one iteration, the current max between current ns and ne 
            for(int j = startC + 1 ; j < drawComp ; j++){
                c = ordByNetDiff[i][j];
                if(!visitedC[j]){
                    if(c.netEnd == ne){
                        // case when this component and previous one have same netStart and netEnd
                        // all elements with same ns and ne 
                        // to handle the bug in previous implementation raised on solveTest5.cir
                        xCor1 = xNets[ns], xCor2 = xNets[ne];
                        name = c.name[0];
                        // ns, ne, xCor1, xCor2 all remain the same
                        // we won't change yNet but while drawing, we use an incrementer for yNet
                        
                        // cout << "Drawing " << name << ": " << ns << " to " << ne << "\n";
                        drawComponent(name, c.num, c.updated, xCor1, yCor, xCor2, cmax);
                        visitedC[j] = 1;
                        countedC ++;
                        cmax ++;
                        // updated the maxBWtwoNets if cmax is larger than it, so that yNet can be correctly updated for next iteration 
                        if(cmax > maxBWtwoNets){
                            maxBWtwoNets = cmax; 
                        }                        
                    }
                    else if(c.netStart >= ne){
                        cmax = 1;
                        // if netStart more than ne of previous drawn element, it is disjoint from other components drawn  
                        ns = c.netStart;
                        ne = c.netEnd;
                        name = c.name[0];
                        xCor1 = xNets[ns], xCor2 = xNets[ne];
                        // cout << "Drawing " << name << ": " << ns << " to " << ne << "\n";
                        drawComponent(name, c.num, c.updated, xCor1, yCor, xCor2);
                        visitedC[j] = 1;
                        countedC ++;
                    }
                    else if(flagUpdatedStart == 0){
                        // else next time the iteration must start from this element since it coincides with other elements drawn in this iteration 
                        startC = j;
                        flagUpdatedStart = 1;
                    }
                }
            }
            yNet += 30*maxBWtwoNets; // update for next iteration of loop 
        }
    }
    
    yEnd = yNet - 30;  // last components drawn at this line
    // draw vertical lines for nets 
    for(int i = 0; i < N; i ++){
        // draw ending nets thicker 
        if(i == 0 || i == N - 1)
            drawVerticalLine(xNets[i], yStart, yEnd, 2);
        else
            drawVerticalLine(xNets[i], yStart, yEnd, 0.5);
        string res = "NET"+to_string(i);
        drawText(res, xNets[i], yEnd + 30);
    }
    end();
}