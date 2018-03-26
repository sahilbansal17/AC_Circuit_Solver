CXX = g++
CFLAGS = -std=c++11 -w

execute:
	yacc -d src/parseCircuit.y
	lex src/scanCircuit.l
	$(CXX) lex.yy.c y.tab.c -o first $(CFLAGS)
	./first Public_cases/Testcase1/top.cir
clean:
	rm first
