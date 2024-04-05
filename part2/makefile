q6: q6.l
	lex q6.l
	yacc -d q6.y
	cc lex.yy.c y.tab.c -ll -o q6
	./q6
	
q7: q7.cpp
	g++ q7.cpp -o q7
	./q7
	
q8: q8.cpp
	g++ q8.cpp -o q8
	./q8
	
q9: q9.cpp
	g++ q9.cpp -o q9
	./q9
	
q10: q10.cpp
	g++ q10.cpp -o q10
	./q10
	
clean:
	rm -f q6 q7 q8 q9 q10 lex.yy.c y.tab.h y.tab.c
