# AC_Circuit_Solver
Given the netlist, this program draws an AC circuit and finds the current/voltage values.

## How to run 
1. `make execute`
2. `./ac_circuit_solver input.cir output1.svg output2.txt`

Command 2 runs the program taking NETLIST as input from **input.cir** and generates **output1.svg.html** as output image and **output2.txt** with the voltages and currents after solving the circuit. 

## Code structure
The entire code is in the **src/** directory and is structured in the following way:

> 1. *ac_circuit_solver.cpp*
> > This is the main file for the entire project.

> 2. *draw.h* and *draw.cpp*
> > They contain the main function to draw the circuit.

> 3. *parse.h*
> > It contains the element and source structures and their vectors obtained after parsing the input netlist. 

> 4. *parseCircuit.y*
> > It is the yacc file used while parsing.

> 5. *scanCircuit.l*
> > It is the lex file used while scanning. 

> 6. *svg.cpp* and *svg.h*
> > They contain the svg functions used for drawing individual elements and implement onClick events on text to get an alert box showing statistics of the element when clicked.
  
> 7. **Eigen/** directory
> > It is the C++ library used for generating and solving matrices. 


## Testing 
A testing script **testScript.sh** has also been written to run many cases simultaneously. It can be modified as per the usage.

All the test cases used for testing the working are included in the **Public_cases** folder. 

## Restrictions on Input Netlist 

There are some restrictions kept in the netlist format:

1. The net can have only an non-negative value as name. **eg.** *NET 0*, *Net 1*.
2. The elements can have only non-negative value as name. **eg.** *R5*, *V0*.
3. The only units allowed to specify values are **K(Kilo)**, **N(Nano)** and **M(Milli)**. This is deliberately done for the purpose of easy error reporting in case units are mismatched.
4. For resistor, only the value has to be supplied **eg.** *10K* would mean *10 kilo ohms* whereas for capacitor and inductor, *F* and *H* need to be written after unit. **eg.** *10NF*. 
5. **The frequency unit allowed for voltage and current sources is only KHz.**

