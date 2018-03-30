CXX = g++
CFLAGS = -std=c++11 -w
DIR = src
# make execute 
execute:  
	yacc -d src/parseCircuit.y
	lex src/scanCircuit.l
	$(CXX) lex.yy.c y.tab.c $(DIR)/ac_circuit_solver.cpp $(DIR)/svg.cpp $(DIR)/draw.cpp -o first $(CFLAGS)
	
# make clean
clean:
	rm first  
	
# make run input=Public_cases/solveCases/solveTest1.cir	
run:
	./first $(input)