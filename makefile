CXX = g++
CFLAGS = -std=c++11 -w
DIR = src
# make execute 
execute:  
	yacc -d src/parseCircuit.y
	lex src/scanCircuit.l
	$(CXX) lex.yy.c y.tab.c $(DIR)/ac_circuit_solver.cpp $(DIR)/svg.cpp $(DIR)/draw.cpp -o ac_circuit_solver $(CFLAGS)
	
# make clean
clean:
	rm ac_circuit_solver  
	
# to run :
# ./ac_circuit_solver Public_cases/solveCases/solveTest1.cir ../test1.svg ../test1.txt