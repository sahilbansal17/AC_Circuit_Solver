execute:
	lex src/scanCircuit.l
	cc lex.yy.c -o first -ll #lex.yy.c will be generated in the same folder not src/
	./first Public_cases/Testcase1/top.cir
clean:
	rm first
