%{
#include <stdio.h>
int state = 0; // Initial state
%}

%%
"a" { } //state does not change-> indicating self loop.
"b" {
    if (state == 0) state = 1; //state transitions on input 'b'
    else if (state == 1) state = 0;
}
\n {
    if (state == 1) printf("Accepted\n"); //final state
    else if (state == -1) printf("Invalid input\n");
    else printf("Rejected\n");
    state = 0; // Going back to the initial state after processing input string
}
. { state = -1; } // Transition to error state for any character other than 'a' and 'b'
%%

int main() {
    printf("Objective: Designing a DFA over the input alphabet a, b to identify words containing an odd number of ’b’ occurrences.\n");
    printf("Enter the string and press 'enter':\n");
    yylex();
    return 0;
}
