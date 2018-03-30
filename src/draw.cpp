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
    
    // int countEle_NetS_NetE[N][N]; // (i, j) gives no of elements from net i to net j
    // for(int i = 0 ; i < E ; i ++){
    //     // undirected graph 
    //     countEle_NetS_NetE[el[i].netStart][el[i].netEnd] ++;
    //     countEle_NetS_NetE[el[i].netEnd][el[i].netStart] ++;
    // }
    // for(int i = 0 ; i < VS ; i ++){
    //     countEle_NetS_NetE[vs[i].netStart][vs[i].netEnd] ++;
    //     countEle_NetS_NetE[vs[i].netEnd][vs[i].netStart] ++;
    // }
    // for(int i = 0 ; i < CS ; i ++){
    //     countEle_NetS_NetE[cs[i].netStart][cs[i].netEnd] ++;
    //     countEle_NetS_NetE[cs[i].netEnd][cs[i].netStart] ++;
    // }
    
    /*
    algorithm followed is :
    1. 
        ordByNetDiffE[i] contains elements whose netStart and netEnd differ by amount of i. 
        Similarly, for ordByNetDiffS.
    2.
        first draw all the elements that have a difference of 1 between the nets, then those with difference 2, and continue till difference of N (max possible)
        
        need to maintain the max y-coordinate free at a particular net 
    */
    
    vector < vector <element> > ordByNetDiffE(N); // diff from 1 to N-1 (since total N nets, 0 till N-1) possible - elements  
    vector <int> yNets (N, 100); // currently each net can have a element at y = 100, we will assume max height of an element is 20, so nearly 30-35 elements can be drawn from a net 
    
    for(int i = 0 ; i < E ; i ++){
        int ns = el[i].netStart, ne = el[i].netEnd;
        int diff = abs(ns - ne);
        ordByNetDiffE[diff].push_back(el[i]);
    }
    vector < vector <source> > ordByNetDiffS(N); // sources 
    for(int i = 0 ; i < VS ; i ++){
        int ns = vs[i].netStart, ne = vs[i].netEnd;
        int diff = abs(ns - ne);
        ordByNetDiffS[diff].push_back(vs[i]);
    }
    for(int i = 0 ; i < CS ; i ++){
        int ns = cs[i].netStart, ne = cs[i].netEnd; 
        int diff = abs(ns - ne);
        ordByNetDiffS[diff].push_back(cs[i]);
    }
    
    for(int i = 1 ; i < N ; i ++){
        // no of elements to draw 
        int drawEl = ordByNetDiffE[i].size();
        int drawS = ordByNetDiffS[i].size();
        for(int j = 0 ; j < drawEl ; j++){
            element e = ordByNetDiffE[i][j];
            int ns = e.netStart, ne = e.netEnd;
            char name = e.elementName[0];
            int xCor1, xCor2, yCor; 
            if(ns > ne){
                // always draw from left net to right net  
                swap(ns, ne);
            }
            xCor1 = xNets[ns], xCor2 = xNets[ne];
            yCor = yNets[ns]; yNets[ns] += 20; // update for next time
            // also for all the nets which come in between, update the yCor availble to be yCor of this net 
            for(int net = ns; net <= ne ; net ++){
                yNets[net] = yNets[ns];
            } 
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
            }
        }
        for(int j = 0 ; j < drawS ; j++){
            source s = ordByNetDiffS[i][j];
            int ns = s.netStart, ne = s.netEnd;
            char name = s.sourceName[0];
            int xCor1, xCor2, yCor; 
            if(ns > ne){
                // always draw from left net to right net  
                swap(ns, ne);
            }
            xCor1 = xNets[ns], xCor2 = xNets[ne];
            yCor = yNets[ns]; yNets[ns] += 20; // update for next time 
            // also for all the nets which come in between, update the yCor availble to be yCor of this net 
            for(int net = ns; net <= ne ; net ++){
                yNets[net] = yNets[ns];
            }
            switch(name){
                case 'V':
                        drawVoltage(xCor1, yCor, xCor2);
                        break;
                case 'I':
                        drawCurrent(xCor1, yCor, xCor2);
                        break;
            }
        }
    }
    for(int i = 0 ; i < N ; i++){
        cout << yNets[i] << " ";
    }
    
    end();
}