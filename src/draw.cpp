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
};

// comparison function to sort the components based on netEnd  
bool orderByNetEnd(const component &a, const component &b){
    return a.netEnd < b.netEnd; // two components will not have the same netEnd since their diff between netEnds is same in the vector
}

void drawMain(int N, vector <element> el, vector <source> cs, vector <source> vs){
    int E = el.size(); // total number of circuit elements 
    int VS = vs.size(); // total no of voltage sources 
    int CS = cs.size(); // total no of current sources 
    start(1000, 1000);
    
    int distBWnets = 1000/N ; // assuming max nets is around 50 - 100
    int xNets[N]; // x coordinates of nets
    int yStart = 100, yEnd = 800; // end points for vertical nets 
    xNets[0] = distBWnets/2;
    for(int i = 1; i < N; i ++){
        xNets[i] = xNets[i-1] + distBWnets;
    }
    for(int i = 0; i < N; i ++){
        drawVerticalLine(xNets[i], yStart, yEnd);
    }

    vector < vector <component> > ordByNetDiff(N); // diff from 1 to N-1 (since total N nets, 0 till N-1) possible for these components  
    int yNet = 100; // this will store the starting yCor for next elements to be drawn 
    
    component c;

    for(int i = 0 ; i < E ; i ++){
        c.netStart  =   el[i].netStart;
        c.netEnd    =   el[i].netEnd;
        c.name      =   el[i].elementName;
        c.num       =   el[i].elementNum;
        c.value     =   el[i].valWithUnit;
        c.current   =   el[i].current;
        c.voltage   =   el[i].voltage;
        int ns = el[i].netStart, ne = el[i].netEnd;
        int diff = abs(ns - ne);
        ordByNetDiff[diff].push_back(c);
    }
    
    for(int i = 0 ; i < VS ; i ++){
        c.netStart  =   vs[i].netStart;
        c.netEnd    =   vs[i].netEnd;
        c.name      =   vs[i].sourceName;
        c.num       =   vs[i].sourceNum;
        c.value     =   vs[i].amplitude;
        c.current   =   vs[i].current;
        c.voltage   =   vs[i].voltage;
        int ns = vs[i].netStart, ne = vs[i].netEnd;
        int diff = abs(ns - ne);
        ordByNetDiff[diff].push_back(c);
    }
    for(int i = 0 ; i < CS ; i ++){
        c.netStart  =   cs[i].netStart;
        c.netEnd    =   cs[i].netEnd;
        c.name      =   cs[i].sourceName;
        c.num       =   cs[i].sourceNum;
        c.value     =   cs[i].amplitude;
        c.current   =   cs[i].current;
        c.voltage   =   cs[i].voltage;
        int ns = cs[i].netStart, ne = cs[i].netEnd; 
        int diff = abs(ns - ne);
        ordByNetDiff[diff].push_back(c);
    }
    
    /*
    algorithm followed is :
    1. 
        ordByNetDiff[i] contains components whose netStart and netEnd differ by amount of i. 
    2.
        sort each vector ordByNetDiff[i] based on the netEnd so that a greedy technique can be used to draw the MAXIMUM disjoint set of components of a particular "net difference value"
    3.    
        for i = 1: maxNetDifference 
            while totalDrawnComponents not equal to DrawnComponentsWithNetDifference "i"
                draw all those components that can have the same yCor based on the greedy technique 
                
                update yNet by 20 (since no more components can be drawn on the same line without an overlap)
        
    */
    
    // sort all vectors ordByNetDiff[i] on the basis of the ending nets, so that disjoint segments can be drawn on the same yCor 
    for(int i = 0 ; i < N ; i ++){
        sort(ordByNetDiff[i].begin(), ordByNetDiff[i].end(), orderByNetEnd);
    }
    
    for(int i = 1 ; i < N ; i ++){
        // no of elements to draw 
        // int drawEl = ordByNetDiffE[i].size();
        // int drawS = ordByNetDiffS[i].size();
        int drawComp = ordByNetDiff[i].size();
        int xCor1, xCor2, yCor, ns, ne;
        char name;
        // component c; already declared 
        vector <int> visitedC (drawComp, 0); // to mark visited onces 
        // drawing disjoint set of components at once, so that yNet can be updated at next iteration 
        int countedC = 0, startC = 0;
        // startC for 1st component in each iteration 
        while(countedC != drawComp){
            int flagUpdatedStart = 0;
            // draw 1st component (startC) independently so that ns and ne can be updated accordingly
            c = ordByNetDiff[i][startC];
            ns = c.netStart; ne = c.netEnd;
            name = c.name[0];
            xCor1 = xNets[ns], xCor2 = xNets[ne];
            yCor = yNet;
            switch(name){
                case 'R':
                        drawResistor(xCor1, yCor, xCor2);
                        break;
                case 'L':
                        drawInductor(xCor1, yCor, xCor2);
                        break;
                case 'C':
                        drawCurrent(xCor1, yCor, xCor2);
                        break;
                case 'V':
                        drawVoltage(xCor1, yCor, xCor2);
                        break;
                case 'I':
                        drawVoltage(xCor1, yCor, xCor2);
                        break;
            }
            visitedC[startC] = 1;
            countedC ++;
            for(int j = startC + 1 ; j < drawComp ; j++){
                if(!visitedC[j]){
                    c = ordByNetDiff[i][j];
                    if(c.netStart >= ne){
                        // if netStart more than ne of previous drawn element 
                        ns = c.netStart;
                        ne = c.netEnd;
                        name = c.name[0];
                        xCor1 = xNets[ns], xCor2 = xNets[ne];
                        yCor = yNet;
                        switch(name){
                            case 'R':
                                    drawResistor(xCor1, yCor, xCor2);
                                    break;
                            case 'L':
                                    drawInductor(xCor1, yCor, xCor2);
                                    break;
                            case 'C':
                                    drawCurrent(xCor1, yCor, xCor2);
                                    break;
                            case 'V':
                                    drawVoltage(xCor1, yCor, xCor2);
                                    break;
                            case 'I':
                                    drawVoltage(xCor1, yCor, xCor2);
                                    break;
                        }
                        visitedC[j] = 1;
                        countedC ++;
                    }
                }
                else if(flagUpdatedStart == 0 && !visitedC[j]){
                    startC = j;
                    flagUpdatedStart = 1;
                }
            }
            yNet += 20; // update for next iteration of loop 
        }
        /*
        OLD WORK FOR SOURCES 
        for(int j = 0 ; j < drawS ; j++){
            s = ordByNetDiffS[i][j];
            ns = s.netStart; ne = s.netEnd;
            name = s.sourceName[0];
            xCor1 = xNets[ns], xCor2 = xNets[ne];
            if(i != 1){
                yNet += 20; // for each next element, yCor will be 20 more to avoid overlaps, not a good way to handle since disjoint horizontal lines also possible
            }
            yCor = yNet;
            switch(name){
                case 'V':
                        drawVoltage(xCor1, yCor, xCor2);
                        break;
                case 'I':
                        drawCurrent(xCor1, yCor, xCor2);
                        break;
            }
        }
        */
    }
    
    end();
}