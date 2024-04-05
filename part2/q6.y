%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER ID
// setting the precedence and associativity of operators 
%left '+' '-'
%left '*' '/'

/* Rule Section */
%% 
E : T	 {printf("Valid Expression. Result = %d\n", $$);
		return 0;
	}

T : 
	T '+' T { $$ = $1 + $3; }
	| T '-' T { $$ = $1 - $3; }
	| T '*' T { $$ = $1 * $3; }
	| T '/' T { if ($3 != 0) { $$ = $1 / $3;} else {
            fprintf(stderr, "Invalid: Division by zero\n");
            exit(1);
        	}
			}
	| '(' T ')' { $$ = $2; }
	| '-' NUMBER { $$ = -$2; }
	| '-' ID { fprintf(stderr, "Invalid Arithmetic Expression\n"); exit(1);}
	| NUMBER { $$ = $1; }
	| ID { fprintf(stderr, "Invalid Arithmetic Expression\n"); exit(1); }
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
	printf("Enter the expression\n");
	yyparse();
}
