%{
#include <stdio.h>
int state = 0; // Initial state
%}

%%
"0" {
    if (state == 0) state = 1; //state transitions on input '0'
    else if (state == 1) state = 0;
    else if (state == 2) state = 3;
    else if (state == 3) state = 2;
}
"1" {
    if (state == 0) state = 3; //state transitions on input '1'
    else if (state == 3) state = 0;
    else if (state == 1) state = 2;
    else if (state == 2) state = 1;
}
\n {
    if (state == 0 || state == 2) printf("Accepted\n"); //final states
    else if (state == -1) printf("Invalid input\n");
    else printf("Rejected\n");
    state = 0; // Going back to the initial state after processing input string
}
. { state = -1; } // Transition to error state for any character other than '0' or '1'
%%

int main() {
    printf("Objective: Designing a DFA with an input alphabet of 0,1 accepting strings with an odd number of 0s or an even number of 1s, but not both simultaneously.\n");
    printf("Enter the String and press 'enter':\n");
    yylex();
    return 0;
}
