/*
    This file will contain the code to draw the different circuit
    elements and connections between them using the functions
    defined in the svg.cpp file
*/
#include <iostream>
#include "parse.h"
using namespace std;

int main(int argc, char** argv){
    
    // first of all parse the netlist given as input 
    int status = parse(argv[1]);
    if(status == -1){
        cout << "\nErrors in input netlist...aborting!\n";
    }
    else{
        printf("\nElements:\n");
        for(int i = 0 ; i < circuitElements.size(); i ++){
            element tempE = circuitElements[i];
            printf("%s->%d->NetStart:%d->NetEnd:%d->Value:%d->Unit:%s\n",tempE.elementName, tempE.elementNum, tempE.netStart, tempE.netEnd, tempE.value, tempE.unit);
        }
        printf("\nSource:\n");
        for(int i = 0 ; i < sourceElements.size(); i ++){
            source tempS = sourceElements[i];
            printf("%s->%d->NetStart:%d->NetEnd:%d->dcOffset:%f->Amp:%f->Freq:%f->Delay:%f->Damping:%f\n",tempS.sourceName, tempS.sourceNum, tempS.netStart, tempS.netEnd, tempS.dcOffset, tempS.amplitude, tempS.freq, tempS.delay, tempS.dampingFactor);
        }
        printf("\n\n");
    }
}