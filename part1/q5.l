%{
#include <stdio.h>
int state = 0; // Initial state
%}

%%
"a" { 
    if (state == 0 || state == 2) state = 0; //state transitions on input 'a'
    if (state == 1) state = 2;
    if (state == 3 || state == 6 || state == 7) state = 4;
    if (state == 4 || state == 5) state = 5;
}
"b" {
    if (state == 0 || state == 1 || state == 3) state = 1; //state transitions on input 'b'
    if (state == 2) state = 3;
    if (state == 4) state = 6;
    if (state == 5 || state == 6 || state == 7) state = 7;
}
\n {
    if (state == 4 || state == 5 || state == 6 || state == 7) printf("Accepted\n"); //final states
    else if (state == -1) printf("Invalid input\n");
    else printf("Rejected\n");
    state = 0; // Going back to the initial state after processing input string
}
. { state = -1; } // Transition to error state for any character other than 'a' and 'b'
%%

int main() {
    printf("Objective: Accepting ’baba’ as a substring over input alphabet a, b.\n");
    printf("Enter the string and press 'enter':\n");
    yylex();
    return 0;
}
