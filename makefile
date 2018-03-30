CXX = g++
CFLAGS = -std=c++11 -w

# make execute 
execute: first 
	yacc -d src/parseCircuit.y
	lex src/scanCircuit.l
	$(CXX) lex.yy.c y.tab.c src/ac_circuit_solver.cpp -o first $(CFLAGS)
	
# make clean
clean:
	rm first  
	
# make run = Public_cases/solveCases/solveTest1.cir	
run:
	./first $(input) 
	