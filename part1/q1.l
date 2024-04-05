%{
#include <stdio.h>
int word_count = 0; //initializing variables for storing the count
int special_char_count = 0;
int line_count = 0;
int space_count = 0;
int tab_count = 0;
%}

%%
[A-Za-z0-9]+ { word_count++; } //counting anything that has alphabets and/or numbers as a word
[^a-zA-Z0-9\n\t ] { special_char_count++; } //counting any character other than alphabets, numbers, newline, tab and space as special characters
[\n]    { line_count++; } //counting no. of lines through \n or newline character
[ ]+    { space_count++; } //counting no.of spaces through ' '
[\t]+   { tab_count++; } //counting no. of tab spaces through \t or tab character
%%

int main() {
    printf("Objective: Calculate the count of words, special characters, lines, spaces, and tabs within an English paragraph.\n");
    printf("Enter the paragraph (End in a new line and press Ctrl+D to process):\n");
    yylex();
    printf("\nWord count: %d\n", word_count); //printing the counts
    printf("Special characters count: %d\n", special_char_count);
    printf("Line count: %d\n", line_count);
    printf("Space count: %d\n", space_count);
    printf("Tab count: %d\n", tab_count);
    return 0;
}
