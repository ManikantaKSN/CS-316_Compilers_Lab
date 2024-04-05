#include <iostream>
#include <vector>
#include <string>
using namespace std;

int k = -1;
vector<vector<char>> quad; //vector to store quadruples

 //remove white spaces from the input string
string trimWhiteSpace(string expression){
    string trimExp = "";
    for(int i = 0; i < (int)expression.size(); i++){
        if(expression[i] != ' ') trimExp = trimExp + expression[i];
    }
    return trimExp;
}

//handle multiplication operation, i.e, replacing x * y with ti = x * y
string mul(string newExp){ 
    for (int i = 0; i < (int)newExp.size(); i++) {
            if (newExp[i] == '*') {
                k++;
                char r = k + '0'; //stores target variable number
                quad.push_back({r, newExp[i-1], newExp[i+1], newExp[i]});
                newExp.replace(i-1,3,1,r); //put target variable in the expression
                break;
            }
        }
    return newExp;
}

//handle division operation, i.e, replacing x / y with ti = x / y
string div(string newExp){
    for (int i = 0; i < (int)newExp.size(); i++) {
            if (newExp[i] == '/') {
                k++;
                char r = k + '0'; //stores target variable number
                quad.push_back({r, newExp[i-1], newExp[i+1], newExp[i]});
                newExp.replace(i-1,3,1,r); //put target variable in the expression
                break;
            }
        }
    return newExp;
}

//handle addition operation, i.e, replacing x + y with ti = x + y
string add(string newExp){
    for (int i = 0; i < (int)newExp.size(); i++) {
            if (newExp[i] == '+') {
                k++;
                char r = k + '0'; //stores target variable number
                quad.push_back({r, newExp[i-1], newExp[i+1], newExp[i]});
                newExp.replace(i-1,3,1,r); //put target variable in the expression
                break;
            }
        }
    return newExp;
}

//handle subtraction operation, i.e, replacing x - y with ti = x - y
string sub(string newExp){
    for (int i = 0; i < (int)newExp.size(); i++) {
            if (newExp[i] == '-') {
                k++;
                char r = k + '0'; //stores target variable number
                quad.push_back({r, newExp[i-1], newExp[i+1], newExp[i]});
                newExp.replace(i-1,3,1,r); //put target variable in the expression
                break;
            }
        }
    return newExp;
}

int main()
{
    string expression, newExp;
    int inp = 0;
    if (inp == 1) { //accepting expression as input from user
        std::cout << "Enter the Expression:" << endl;
        getline(cin, expression);
        cout << endl;
    }
    else if (inp == 0) {
        expression = "a+b+c*d/e+f";
        cout << "Given expression: " << expression << endl << endl;
    }
    expression = trimWhiteSpace(expression);
    if (expression[1] == '=') newExp = expression.substr(2); // getting the expression after '=', if present.
    else newExp = expression;

    // Handling unary minus at the beginning of expression.
    for (int i = 0; i < (int)newExp.size() - 1; i++){
        if (i==0 && newExp[i] == '-') { //when minus is at beginning
            if (newExp[i + 1] == '*' || newExp[i + 1] == '/' || newExp[i + 1] == '+' || newExp[i + 1] == '-') {
                cerr << "Invalid expression" << endl;
                exit(1);
            }
            else {
                k++;
                char r = k + '0'; //stores target variable number
                quad.push_back({r, newExp[i+1], ' ', newExp[i]});
                newExp.replace(i,2,1,r); //put target variable in the expression         
            }
        }
        else if (newExp[i] == '-' && (newExp[i - 1] == '*' || newExp[i - 1] == '/' || newExp[i - 1] == '+'))  
        { // when minus follows an operator
            if (newExp[i + 1] == '*' || newExp[i + 1] == '/' || newExp[i + 1] == '+' || newExp[i + 1] == '-') {
                cerr << "Invalid Expression" << endl;
                exit(1);
            }
            else {
                k++;
                char r = k + '0'; //stores target variable number
                quad.push_back({r, newExp[i+1], ' ', newExp[i]});
                newExp.replace(i,2,1,r); //put target variable in the expression
            }
        }
    }
    int x = int(newExp.size());
    // Handling multiplication and division operations due to higher precedence,
    // following left to right associativity.
    while(newExp.find('*') != string::npos || newExp.find('/') != string::npos){
        for (int i = 0; i < x; i++) {
            if (newExp[i] == '*') {
                newExp = mul(newExp); //call to mul function which handles * operation
                x = int(newExp.size());
            }
            if (newExp[i] == '/') {
                newExp = div(newExp); //call to div function which handles / operation
                x = int(newExp.size());
            }
        }
    }
    // Handling addition and subtraction operations next,
    // following left to right associativity.
    while(newExp.find('+') != string::npos || newExp.find('-') != string::npos){
        for (int i = 0; i < x; i++) {
            if (newExp[i] == '+') {
                newExp = add(newExp); //call to add function which handles + operation
                x = int(newExp.size());
            }
            if (newExp[i] == '-') {
                newExp = sub(newExp); //call to sub function which handles - operation
                x = int(newExp.size());
            }
        }
    }

    // printing the quadruples table.
    std::cout << "Quadruple Representation:" << endl;
    std::cout << "--------------------------" << endl;
    std::cout << "S.No\t" << "Target\t" << "Arg-1\t" << "Arg-2\t" << "Operator" << endl;
    std::cout << "----------------------------------------" << endl;
    int i;
    for (i = 0; i < (int)quad.size(); i++) {
        if(quad[i][1] >= 48 && quad[i][1] <= 96){
            if(quad[i][2] >= 48 && quad[i][2] <=96){
                std::cout << i+1 << "\tt" << (int)(quad[i][0]-'0') + 1 << "\tt" << (int)(quad[i][1]-'0') + 1 << "\tt" << (int)(quad[i][2]-'0') + 1 << "\t" << quad[i][3] << endl;
            }
            else{
                std::cout << i+1 << "\tt" << (int)(quad[i][0]-'0') + 1 << "\tt" << (int)(quad[i][1]-'0') + 1 << "\t" << quad[i][2] << "\t" << quad[i][3] << endl;
            }
        }
        else {
            if(quad[i][2] >= 48 && quad[i][2] <=96){
                std::cout << i+1 << "\tt" << (int)(quad[i][0]-'0') + 1 << "\t" << quad[i][1] << "\tt" << (int)(quad[i][2]-'0') + 1 << "\t" << quad[i][3] << endl;
            }
            else{
                std::cout << i+1 << "\tt" << (int)(quad[i][0]-'0') + 1 << "\t" << quad[i][1] << "\t" << quad[i][2] << "\t" << quad[i][3] << endl;
            }
        }
    }

    if (expression[1] == '=') { //final quadruple entry for the result if '=' is present in the expression
        vector<char> final_res = quad[quad.size()-1];
        std::cout << i+1 << "\t" << expression[0] << "\tt" << (int)(final_res[0]-'0') + 1 << "\t" << " " << "\t" << "=" << endl;
        quad.push_back({expression[0], final_res[0], ' ', '='});
    }
    return 0;
}