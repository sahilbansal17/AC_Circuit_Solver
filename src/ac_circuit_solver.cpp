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
#define NANO 0.000000001
#define MILLI 0.001

using namespace std;
using namespace Eigen;

double pi = 4*atan(1); // atan is defined in complex library 

// this function returns the phase of a complex number in degrees 
double phase(complex <double> &c){
    double im = c.imag(), re = c.real();
    if(im == 0){
        if(re >= 0)
            return 0;
        return 180;
    }
    else if(re == 0){
        if(im >= 0)
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

// functions for rounding decimal upto 3 places 
inline double round_3(double val){
    double val_mul_1000 = val * 1000.0;
    if(val_mul_1000 < 0){
        val_mul_1000 = ceil(val_mul_1000 - 0.5);
    }
    else{
        val_mul_1000 = floor(val_mul_1000 + 0.5);
    }
    return val_mul_1000/1000.0 ; 
}

// comparison function to sort the sources based on frequencies 
bool compareByFreq(const source &a, const source &b){
    return a.freq <= b.freq;
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
        return 0;
    }
    
    /* INITIALIZATION */
    vector <source> vSource, iSource; // seperate the two types of sources
    
    printf("\nElements:\n");
    for(int i = 0 ; i < circuitElements.size(); i ++){
        element tempE = circuitElements[i];
        printf("%s->%d->NetStart:%d->NetEnd:%d->Value:%f->Unit:%s\n",tempE.elementName, tempE.elementNum, tempE.netStart, tempE.netEnd, tempE.value, tempE.unit);
    }
    printf("\nSource:\n");
    for(int i = 0 ; i < sourceElements.size(); i ++){
        source tempS = sourceElements[i];
        printf("%s->%d->NetStart:%d->NetEnd:%d->dcOffset:%f->Amp:%f->Freq:%f->Delay:%f->Damping:%f\n",tempS.sourceName, tempS.sourceNum, tempS.netStart, tempS.netEnd, tempS.dcOffset, tempS.amplitude, tempS.freq, tempS.delay, tempS.dampingFactor);
    }
    printf("\n");
    
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
    
    // handling multiple sources with different frequencies 
    // sort the sources in increasing order of their frequencies 
    sort(sourceElements.begin(), sourceElements.end(), compareByFreq);
    
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
    
    /* for interconnections between passive circuit elements */
    MatrixXcd G(totalNodes, totalNodes); // x-arbitrary_size, c-complex, d-double
    /*
    1. each element in the diagonal matrix is equal to the sum of admittance of each element connected to the corresponding node 
    2. the off-diagonal elements are sum of negative admittance of elements connected to the pair of corresponding nodes 
    */
    
    /* 
    B & C for connections of voltage sources
    E is for the values of known voltage sources  
    => B and C will have values only either 0, 1 or -1
    => C = B transpose ( no dependent sources involved )
    */
    MatrixXcd B(totalNodes, totalVoltageSources);
    MatrixXcd C(totalVoltageSources, totalNodes);
    MatrixXcd E(totalVoltageSources, 1);
    /*
    1. if +ve terminal (netStart) of ith voltage source is connected to node k then C(i, k) = 1
    2. if -ve terminal (netEnd) of ith voltage source is connected to node k then C(i, k) = -1 
    3. E(i, 0) = value of voltage of ith voltage source 
    */
    B = MatrixXd::Constant(totalNodes, totalVoltageSources, 0); // assign all values to 0
    C = MatrixXd::Constant(totalVoltageSources, totalNodes, 0); // assign all values to 0 
    E = MatrixXd::Constant(totalVoltageSources, 1, 0); // assign all values to 0 
    for(int i = 0 ; i < vSource.size(); i ++){
        double mag = vSource[i].amplitude;
        int ns = vSource[i].netStart;
        int ne = vSource[i].netEnd;
        complex <double> One(1, 0);
        if(ns != 0 && ne != 0){
            C(i, ns - 1) += One;
            B(ns - 1, i) += One;
            C(i, ne - 1) -= One;
            B(ne - 1, i) -= One;
        }
        else if(ns == 0){
            C(i, ne - 1) -= One;
            B(ne - 1, i) -= One;
        }
        else if(ne == 0){
            C(i, ns - 1) += One;
            B(ns - 1, i) += One;
        }
    }
    /*
    Matrix D just contains all zeroes (all sources independent)
    */
    MatrixXcd D(totalVoltageSources, totalVoltageSources);
    D = MatrixXd::Constant(totalVoltageSources, totalVoltageSources, 0);
    
    /*
    Matrix A => |G  B|
                |C  D|
    */
    MatrixXcd A(totalNodes + totalVoltageSources, totalNodes + totalVoltageSources);
    // assign B, C, D in the beginning only, no changes required later 
    for(int i = totalNodes; i < totalNodes + totalVoltageSources; i ++){
        for(int j = 0; j < totalNodes ; j ++){
            A(i, j) = C(i - totalNodes, j);
        }
    }
    for(int i = 0 ; i < totalNodes ; i ++){
        for(int j = totalNodes ; j < totalNodes + totalVoltageSources ; j ++){
            A(i, j) = B(i, j - totalNodes);
        }
    }
    for(int i = totalNodes ; i < totalNodes + totalVoltageSources ; i ++){
        for(int j = totalNodes ; j < totalNodes + totalVoltageSources ; j ++){
            A(i, j) = D(i - totalNodes, j - totalNodes);
        }
    }
    /*
    Matrix Z (which contains the known values of current sources and voltages)
    Z = [I  E] transpose 
    where   I contains net outward current at each node (either 0 or value of current source) 
            E contains the voltage source values, already declared earlier 
    */
    
    MatrixXcd Z(totalNodes + totalVoltageSources, 1);
    MatrixXcd I(totalNodes, 1);
    
    /*
        Matrix X will be obtained by solving 
            AX = Z
        It will be of the size (n + m) * 1 where n : totalNodes, m : totalVoltageSources
        So, the first n elements will give the node voltages 
        and the next m elements will give the currents flowing from the positive terminal of battery to its negative terminal (from inside) as convention 
    */
    
    MatrixXcd X(totalNodes + totalVoltageSources, 1);

    // solving for multiple frequencies 
    // assuming that all of them have different frequencies 
    
    int currentVoltSource = 0; // for matrix E 
    for(int T = 0 ; T < sourceElements.size(); T ++){
        // currently the Tth Element is considered to be active 
        double omega = 2*pi*(sourceElements[T].freq)*KILO;
        
        // only the matrices G (thus A) & I and E (thus Z) change at each iteration  
        
        G = MatrixXd::Constant(totalNodes, totalNodes, 0); // assign all values to 0
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
            circuitElements[i].admittance = Y; // to be used in current computation 
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
        
        Z = MatrixXd::Constant(totalVoltageSources + totalNodes, 1, 0);
        E = MatrixXd::Constant(totalVoltageSources, 1, 0); // assign all values to 0 
        // only the current voltage source is active 
        if(sourceElements[T].sourceName[0] == 'V'){
            E(currentVoltSource, 0) = sourceElements[T].amplitude;
            Z(currentVoltSource + totalNodes, 0) = sourceElements[T].amplitude;
            currentVoltSource ++; 
        }
        
        for(int i = 0 ; i < totalNodes; i ++){
            for(int j = 0 ; j < totalNodes ; j ++){
                A(i, j) = G(i, j);
            }
        }
    
        // cout << "\nA : \n";
        // for(int i = 0 ; i < totalVoltageSources + totalNodes; i ++){
        //     for(int j = 0 ; j < totalNodes + totalVoltageSources; j ++){
        //         cout << A(i, j) << " ";
        //     }
        //     cout << "\n";
        // }
        
        I = MatrixXd::Constant(totalNodes, 1, 0);
        // only if the current CURRENT SOURCE is active, it will reflect in I
        // otherwise net CURRENT at all nodes will be zero 
        if(sourceElements[T].sourceName[0] == 'I'){
            int ns = sourceElements[T].netStart;
            int ne = sourceElements[T].netEnd;
            // if current flows from netEnd to netStart 
            // this also means that netStart is at higher potential
            // so same notation used as given in assignmentPDF
            if(ns != 0 && ne != 0){
                I(ns - 1, 0) = sourceElements[T].amplitude;
                Z(ns - 1, 0) = sourceElements[T].amplitude;
                I(ne - 1, 0) = sourceElements[T].amplitude;
                Z(ne - 1, 0) = sourceElements[T].amplitude;
            }
            else if(ns == 0){
                I(ne - 1, 0) = sourceElements[T].amplitude;
                Z(ne - 1, 0) = sourceElements[T].amplitude;
            }
            else if(ne == 0){
                I(ns - 1, 0) = sourceElements[T].amplitude;
                Z(ns - 1, 0) = sourceElements[T].amplitude;
            }
        }
        
        // cout << "\nZ : \n";
        // for(int i = 0 ; i < totalVoltageSources + totalNodes; i ++){
        //     for(int j = 0 ; j < 1; j ++){
        //         cout << Z(i, j) << " ";
        //     }
        //     cout << "\n";
        // }
        
        X = A.colPivHouseholderQr().solve(Z); // used to solve AX = Z    
        // changing the direction of current assumed wrongly for convenience across the voltage sources 
        for(int i = totalNodes ; i < totalNodes + totalVoltageSources ; i ++){
            double re = -X(i, 0).real(), im = -X(i, 0).imag();
            complex <double> temp(re, im);
            X(i, 0) = temp;
        }
        
        // store the node voltages in the appropriate vector 
        for(int i = 0 ; i < totalNodes ; i ++){
            VoltageNode[i+1] = X(i, 0);
        }
        
        // cout << "\nX : \n";
        // for(int i = 0 ; i < totalVoltageSources + totalNodes; i ++){
        //     for(int j = 0 ; j < 1; j ++){
        //         cout << abs(X(i, j)) << " ";
        //     }
        //     cout << "\n";
        // }
        
        // print voltages on the screen 
        cout << "\n";
        cout << "VOLTAGES OF ELEMENTS\n";
        for(int i = 0; i < circuitElements.size(); i ++){
            int ns = circuitElements[i].netStart;
            int ne = circuitElements[i].netEnd;
            cout << circuitElements[i].elementName[0] << circuitElements[i].elementNum << " ";
            complex <double> voltDiff = VoltageNode[ns] - VoltageNode[ne];
            circuitElements[i].voltage = voltDiff; // to be used in current computation 
            cout << round_3(abs(voltDiff)) << " " << round_3(phase(voltDiff)) << "\n";
        }
        cout << "\nVOLTAGE OF ACTIVE SOURCE\n";
        int ns = sourceElements[T].netStart;
        int ne = sourceElements[T].netEnd;
        cout << sourceElements[T].sourceName[0] << sourceElements[T].sourceNum << " ";
        complex <double> voltDiff;
        if(sourceElements[T].sourceName[0] == 'V')
            voltDiff = sourceElements[T].amplitude;
        else
            voltDiff = VoltageNode[ns] - VoltageNode[ne];
        sourceElements[T].voltage = voltDiff;
        cout << round_3(abs(voltDiff)) << " " << round_3(phase(voltDiff)) << "\n";        
        
        // current values are to be computed, impedance will also be required 
        cout << "\nCURRENTS OF ELEMENTS\n";
        for(int i = 0 ; i < circuitElements.size(); i ++){
            complex<double> res = circuitElements[i].voltage * circuitElements[i].admittance;
            circuitElements[i].current = res;
            cout << circuitElements[i].elementName[0] << circuitElements[i].elementNum << " ";
            cout << round_3(abs(res)) << " " << round_3(phase(res)) << "\n";
        }
        cout << "\nCURRENT OF ACTIVE SOURCE\n";
        cout << sourceElements[T].sourceName[0] << sourceElements[T].sourceNum << " ";
        complex <double> res;
        switch(sourceElements[T].sourceName[0]){
            case 'V':
                    res = X(totalNodes + currentVoltSource - 1);
                    break;
            case 'I':
                    res = sourceElements[T].amplitude;
                    break;
            default:
                    break;
        }
        sourceElements[T].current = res;
        cout << round_3(abs(res)) << " " << round_3(phase(res)) << "\n";        
    }
    return 0;
}