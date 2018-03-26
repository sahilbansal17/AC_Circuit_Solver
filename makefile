execute:
	lex src/scanCircuit.l
	cc src/lex.yy.c -o first -ll
	./first Public_cases/Testcase1/top.cir
