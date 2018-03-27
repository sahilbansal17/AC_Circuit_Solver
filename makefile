CXX = g++
CFLAGS = -std=c++11 -w

execute:
	yacc -d src/parseCircuit.y
	lex src/scanCircuit.l
	$(CXX) lex.yy.c y.tab.c src/draw.cpp -o first $(CFLAGS)
clean:
	rm first
runAll:
	echo "Case1:\n"
	./first Public_cases/Testcase1/top.cir
	echo "Case2:\n"
	./first Public_cases/Testcase2/top.cir
	echo "Case3:\n"
	./first Public_cases/Testcase3/top.cir
	echo "Case4:\n"
	./first Public_cases/Testcase4/top.cir
	echo "Case5:\n"
	./first Public_cases/Testcase5/top.cir
