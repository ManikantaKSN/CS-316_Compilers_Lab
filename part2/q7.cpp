#include <iostream>  
#include <string> 
#include <vector>
using namespace std; 

// Function to remove white spaces from the input string
string trimWhiteSpace(string expression){ 
    string trimExp = "";
    for(int i = 0; i < (int)expression.size(); i++){
        if(expression[i] != ' ') trimExp = trimExp + expression[i];
    }
    return trimExp;
}

int main () {  
    char non_terminal;  
    char beta;
    vector<char> alpha(10);
    string temp; //stores the final grammar rules temporarily
    int num;    
    int index=3; 
    vector<string> str, production(3); //stores the initial and final grammar rules
    int k = 0;
    if(k==1) { //accepting Grammar as input from user
        std::cout << "Enter the number of productions(no. of non-terminals):" << endl;  
        cin >> num;
        cin.ignore();
        production.resize(num);
        std::cout << "Enter the grammar as X->X+A|A (enter epsilon as '#'):" << endl;
        for(int i=0;i<num;i++){
            getline(cin, production[i]);
            production[i] = trimWhiteSpace(production[i]);
        }
    }  
    else if(k==0){
        cout << "Given Grammar: " << endl;
        cout << "--------------" << endl;
        production[0] = "E->E+T|T";
        cout << production[0] << endl;
        production[1] = "T->T*F|F";
        cout << production[1] << endl;
        production[2] = "F->id";
        cout << production[2] << endl;
        num = 3;
    }
    for(int i=0; i<num; i++){  
        cout << endl << "RULE : " << production[i] << endl;
        non_terminal=production[i][0];  
        if(non_terminal==production[i][index]) {  //if there is left recursion
          int j =0;
          for(j = index+1; production[i][j] != '|'; j++){ //extracting alpha
          alpha[j-index-1]=production[i][j];
          }  
          alpha[j-index-1]='\0';  
          while(production[i][index]!=0 && production[i][index]!='|')  index++;  
            if(production[i][index]!=0) {   
              cout << "It is left recursive. Eliminating left recursion: " << endl;
              string alp(alpha.begin(), alpha.end());
              string beta = production[i].substr(index+1); //extracting beta
              string nt(1, non_terminal);
              temp = nt + "->" + beta + nt + "\'"; //new rule after removing left recursion
              cout << temp << endl;
              str.push_back(temp); //adding the new rule to the final grammar rules
              temp = nt + "\'" + "->" + alp + nt + "\'" + "|#"; //new rule after removing left recursion
              cout << temp << endl;
              str.push_back(temp); //adding the new rule to the final grammar rules
            }  
            else { 
              cout << "It can't be reduced" << endl; 
              str.push_back(production[i]);
            }
        }  
        else {
          cout << "It is not left recursive" << endl;  
          str.push_back(production[i]);
        }
        index=3;  
    }  
    cout << endl << "Final Grammar Rules after eliminating Left Recursion: ('#' represents epsilon)" << endl;
    for (int i=0; i<str.size(); i++){
      cout << str[i] << endl;
    }
    return 0;
}   