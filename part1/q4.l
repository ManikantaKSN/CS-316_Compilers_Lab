%{
#include <stdio.h>
int state = 0; // Initial state
%}

%%
"a" { 
    if (state == 0) state = 3; //trap state for strings starting with 'a'. state 3 has a self loop for both inputs 'a' and 'b'
    else if (state == 1 || state == 2) state = 2; //state transitions on input 'a'
}
"b" {
    if (state == 0 || state == 1 || state == 2) state = 1; //state transitions on input 'b'
}
\n {
    if (state == 2) printf("Accepted\n"); //final state
    else if (state == -1) printf("Invalid input\n");
    else printf("Rejected\n");
    state = 0; // Going back to the initial state after processing input string
}
. { state = -1; } // Transition to error state for any character other than 'a' and 'b'
%%

int main() {
    printf("Objective: Recognize strings initiated with ’b’ and concluded with ’a’ within the input alphabet a, b.\n");
    printf("Enter the string and press 'enter':\n");
    yylex();
    return 0;
}
