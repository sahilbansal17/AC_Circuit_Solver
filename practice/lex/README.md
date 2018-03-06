## PRACTICE FOR LEX

Lex translates the lex specification (specified in **.l** file) into a C source file called **lex.yy.c** which we then compile and link with the lex library -ll.

So, to run the practice code :
1. `lex filename.l`
2. `cc lex.yy.c -o first -ll`

### verbRecognize.l
This lex specification recognizes whether the words in the input are verbs or not.

To run :
1. `lex verbRecognize.l`
2. `cc lex.yy.c -o first -ll`
3. `./first`

Now, provide the input as a line terminated by newline. It then provides the desired output. Hit `Ctrl+C` to terminate.
