/*
    This will be the main file for the entire project. It will
    use draw.cpp to write to an svg file (which in turn will use the svg.cpp
    file for svg functions). The circuit solver functionalities are currently
    included in this file only.
*/
#include <iostream>
#include "Eigen/Eigen"
#include "parse.h"

#define KILO 1000.0
#define NANO 10e-9
#define MILLI 10e-3

using namespace std;
using namespace Eigen;

double pi = 4*atan(1); // atan is defined in complex library 

// this function returns the phase of a complex number in degrees 
double phase(complex <double> &c){
    double im = c.imag(), re = c.real();
    if(im == 0){
        if(re > 0)
            return 0;
        return 180;
    }
    else if(re == 0){
        if(im > 0)
            return 90;
        return -90;
    }
    double res = atan(im/re) * 180/pi ; 
    // converting to the proper range (-pi, pi]
    // if both im and re are negative, res = res - 180
    // else if im > 0 and re < 0 then res = res + 180
    if(im < 0 && re < 0)
        res -= 180;
    else if(im > 0 && re < 0)
        res += 180;
    return res;
}

int main(int argc, char** argv){
    
    // first of all check whether draw returned success status 
    // int status = draw(argv[1]);
    // if(status == -1){
    //     cout << "\nErrors in input netlist...aborting!\n";
    // }
    
    int status = parse(argv[1]);
    if(status == -1){
        cout << "\nErrors in input netlist...aborting!\n";
    }
    
    /* INITIALIZATION */
    vector <source> vSource, iSource; // seperate the two types of sources
    
    // assing proper value to the circuit elements 
    for(int i = 0 ; i < circuitElements.size(); i ++){
        switch(circuitElements[i].unit[0]){
            case 'K':
                    circuitElements[i].valWithUnit = KILO * circuitElements[i].value;
                    break;
            case 'N':
                    circuitElements[i].valWithUnit = NANO * circuitElements[i].value;
                    break;
            case 'M':
                    circuitElements[i].valWithUnit = MILLI * circuitElements[i].value;
                    break;
            default:
                    circuitElements[i].valWithUnit = circuitElements[i].value;
                    break;
        }
    }
    
    // find the maximum no of nodes in the circuit 
    int totalNodes = 0 ; // doesn't include the ground node
    // this highest numbered node can be amongst the elements  
    for(int i = 0 ; i < circuitElements.size(); i ++){
        if(circuitElements[i].netStart > totalNodes){
            totalNodes = circuitElements[i].netStart;
        }
        if(circuitElements[i].netEnd > totalNodes){
            totalNodes = circuitElements[i].netEnd;
        }
    }
    // or it can be amongst the sources 
    
    int totalVoltageSources = 0; // also compute the total num of volt sources
    for(int i = 0 ; i < sourceElements.size(); i ++){
        // seperate out the two sources I & V
        if(sourceElements[i].sourceName[0] == 'V'){
            vSource.push_back(sourceElements[i]);
            totalVoltageSources ++;
        }
        else{
            iSource.push_back(sourceElements[i]);
        }
        if(sourceElements[i].netStart > totalNodes){
            totalNodes = sourceElements[i].netStart;
        }
        if(sourceElements[i].netEnd > totalNodes){
            totalNodes = sourceElements[i].netEnd;
        }
    }
    
    // modified nodal analysis method will be used to solve the circuit 
    vector < complex <double> > VoltageNode ; // stores the node voltages   
    complex <double> temp(0, 0); // 0 + 0j
    // initialise VoltageNode  
    for(int i = 0 ; i <= totalNodes; i ++){
        VoltageNode.push_back(temp);
    }
    
    // now we will use the Eigen library functions to construct the required matrices in the modified nodal analysis method 
    
    double omega = vSource[0].freq;
    
    /* for interconnections between passive circuit elements */
    MatrixXcd G(totalNodes, totalNodes); // x-arbitrary_size, c-complex, d-double
    G = MatrixXd::Constant(totalNodes, totalNodes, 0); // assign all values to 0 
    
    /*
    1. each element in the diagonal matrix is equal to the sum of admittance of each element connected to the corresponding node 
    2. the off-diagonal elements are sum of negative admittance of elements connected to the pair of corresponding nodes 
    */
    
    for(int i = 0 ; i < circuitElements.size(); i ++){
        int ns = circuitElements[i].netStart;
        int ne = circuitElements[i].netEnd;
        
        double val = circuitElements[i].valWithUnit;
        double re, im; 
        // compute the admittance
        switch(circuitElements[i].elementName[0]){
            case 'R':
                    re = 1/(val);
                    im = 0;
                    break;
            case 'L':
                    re = 0;
                    im = -1/(omega*val);
                    break;
            case 'C':
                    re = 0;
                    im = omega*val;
                    break;
            default:
                    break;
        }
        complex <double> Y(re, im); // admittance = 1/impedance
        if(ns != 0 && ne != 0){
            // diagonal elements corresponding to ns-1 and ne-1 
            G(ns - 1, ns - 1) += Y;
            G(ne - 1, ne - 1) += Y; 
            // off-diagonals for pair of connected nodes 
            G(ns - 1, ne - 1) -= Y;
            G(ne - 1, ns - 1) -= Y;
        }
        else if(ns == 0){
            G(ne - 1, ne - 1) += Y;
        }
        else if(ne == 0){
            G(ns - 1, ns - 1) += Y;
        }
        // element cannot have both terminals as ground 
    }
    
    /* 
    B & C for connections of voltage sources
    E is for the values of known voltage sources  
    => B and C will have values only either 0, 1 or -1
    => C = B transpose ( no dependent sources involved )
    */
    MatrixXcd B(totalNodes, totalVoltageSources);
    B = MatrixXd::Constant(totalNodes, totalVoltageSources, 0); // assign all values to 0 
    MatrixXcd C(totalVoltageSources, totalNodes);
    C = MatrixXd::Constant(totalVoltageSources, totalNodes, 0); // assign all values to 0 
    MatrixXcd E(totalVoltageSources, 1);
    E = MatrixXd::Constant(totalVoltageSources, 1, 0); // assign all values to 0 
    /*
    1. if +ve terminal (netStart) of ith voltage source is connected to node k then C(i, k) = 1
    2. if -ve terminal (netEnd) of ith voltage source is connected to node k then C(i, k) = -1 
    3. E(i, 0) = value of voltage of ith voltage source 
    */
    
    for(int i = 0 ; i < vSource.size(); i ++){
        E(i, 0) = vSource[i].amplitude;
        int ns = vSource[i].netStart;
        int ne = vSource[i].netEnd;
        if(ns != 0 && ne != 0){
            C(i, ns - 1) += 1;
            C(i, ne - 1) += -1;
        }
        else if(ns == 0){
            C(i, ne - 1) += -1;
        }
        else if(ne == 0){
            C(i, ns - 1) += 1;
        }
    }
    
    B = C.transpose();
    
    // for knowing whether the program works fine till now, we need to print the matrices formed till now 
    
    cout << "G : \n";
    for(int i = 0 ; i < totalNodes; i ++){
        for(int j = 0 ; j < totalNodes; j ++){
            cout << G(i,j) << " ";
        }
        cout << "\n";
    }
    
    cout << "\nC : \n";
    for(int i = 0 ; i < totalVoltageSources; i ++){
        for(int j = 0 ; j < totalNodes; j ++){
            cout << B(i, j) << " ";
        }
        cout << "\n";
    }
    
    cout << "\nE : \n";
    for(int i = 0 ; i < totalVoltageSources ; i ++){
        for(int j = 0 ; j < 1; j ++){
            cout << E(i, j) << " ";
        }
        cout << "\n";
    }
    return 0;
}