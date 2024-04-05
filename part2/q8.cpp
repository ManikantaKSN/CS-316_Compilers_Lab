#include <iostream>  
#include <string> 
#include <vector>
#include <unordered_map>
#include <set>
#include <bits/stdc++.h> 
#include <algorithm>
using namespace std; 

const std::string EPSILON = "#";
vector<string> str, nT;
vector<int> newNT;

// Function to remove white spaces from the input string
string trimWhiteSpace(string expression){
    string trimExp = "";
    for(int i = 0; i < (int)expression.size(); i++){
        if(expression[i] != ' ') trimExp = trimExp + expression[i];
    }
    return trimExp;
}

// Function checks if its a number(from our mapping)
bool isNumber(const std::string& str) {
    try {
        int k = std::stoi(str); // Try converting to integer
        return true;
    } catch(const std::invalid_argument&) {
        return false;
    }
}

// Function to check if a string is a non-terminal
bool isNonTerminal(const std::string& symbol) {
    if(isNumber(symbol)){
        return std::find(newNT.begin(), newNT.end(), stoi(symbol)) != newNT.end();
    }
    return false;
}

// Function to calculate FIRST sets
void calculateFirstSets(std::unordered_map<int, std::set<char>>& first) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i=str.size()-1; i>=0; i--) {
            std::string rule = str[i];
            int nonTerminal = stoi(rule.substr(0, rule.find("->")));
            std::string productions = rule.substr(rule.find("->") + 2);

            size_t start = 0;
            size_t end = productions.find('|');
            while (end != std::string::npos) {
                std::string production = productions.substr(start, end - start);

                // Process each production individually
                // Rule: X -> epsilon
                if (production == EPSILON) {
                    if (first[nonTerminal].find(EPSILON[0]) == first[nonTerminal].end()) {
                        first[nonTerminal].insert(EPSILON[0]);
                        changed = true;
                    }
                }
                // Rule: X -> terminal symbol
                else if (!isNonTerminal(production.substr(0, 1))) {
                    if (first[nonTerminal].find(production[0]) == first[nonTerminal].end()) {
                        first[nonTerminal].insert(production[0]);
                        changed = true;
                    }
                }
                // Rule: X -> Y1Y2...Yn
                else {
                    bool epsilonInProduction = true;
                    for (char symbol : production) {
                        std::string symbolStr(1, symbol);
                        if (isNumber(symbolStr)) {
                            // Add FIRST(Yi) to FIRST(X), excluding epsilon
                            if (first[stoi(symbolStr)].find(EPSILON[0]) == first[stoi(symbolStr)].end()) {
                                if (first[nonTerminal].find(*first[stoi(symbolStr)].begin()) == first[nonTerminal].end()) {
                                    first[nonTerminal].insert(*first[stoi(symbolStr)].begin());
                                    changed = true;
                                }
                            }
                            // If epsilon not in FIRST(Yi), stop
                            if (first[stoi(symbolStr)].find(EPSILON[0]) == first[stoi(symbolStr)].end()) {
                                epsilonInProduction = false;
                                break;
                            }
                        }                       
                    }
                    // If epsilon in FIRST(Yi) for all i, add epsilon to FIRST(X)
                    if (epsilonInProduction) {
                        if (first[nonTerminal].find(EPSILON[0]) == first[nonTerminal].end()) {
                            first[nonTerminal].insert(EPSILON[0]);
                            changed = true;
                        }
                    }
                }
                // Move to the next production
                start = end + 1;
                end = productions.find('|', start);
            }

            // Process the last production
            std::string production = productions.substr(start);
            // Rule: X -> epsilon
            if (production == EPSILON) {
                if (first[nonTerminal].find(EPSILON[0]) == first[nonTerminal].end()) {
                    first[nonTerminal].insert(EPSILON[0]);
                    changed = true;
                }
            }
            // Rule: X -> terminal symbol
            else if (!isNonTerminal(production.substr(0, 1))) {
                if (first[nonTerminal].find(production[0]) == first[nonTerminal].end()) {
                    first[nonTerminal].insert(production[0]);
                    changed = true;
                }
            }
            // Rule: X -> Y1Y2...Yn
            else {
                bool epsilonInProduction = true;
                for (char symbol : production) {
                    std::string symbolStr(1, symbol);
                    if (isNumber(symbolStr)) {
                        // Add FIRST(Yi) to FIRST(X), excluding epsilon
                        if (first[stoi(symbolStr)].find(EPSILON[0]) == first[stoi(symbolStr)].end()) {
                            if (first[nonTerminal].find(*first[stoi(symbolStr)].begin()) == first[nonTerminal].end()) {
                                first[nonTerminal].insert(*first[stoi(symbolStr)].begin());
                                changed = true;
                            }
                        }
                        // If epsilon not in FIRST(Yi), stop
                        if (first[stoi(symbolStr)].find(EPSILON[0]) == first[stoi(symbolStr)].end()) {
                            epsilonInProduction = false;
                            break;
                        }
                    } 
                    else{
                      if (production == EPSILON) {
                        if (first[nonTerminal].find(EPSILON[0]) == first[nonTerminal].end()) {
                            first[nonTerminal].insert(EPSILON[0]);
                            changed = true;
                        }
                      }
                      // Rule: X -> terminal symbol
                      else if (!isNonTerminal(production.substr(0, 1))) {
                        if (first[nonTerminal].find(production[0]) == first[nonTerminal].end()) {
                            first[nonTerminal].insert(production[0]);
                            changed = true;
                        }
                      }
                    }                      
                }
                // If epsilon in FIRST(Yi) for all i, add epsilon to FIRST(X)
                if (epsilonInProduction) {
                    if (first[nonTerminal].find(EPSILON[0]) == first[nonTerminal].end()) {
                        first[nonTerminal].insert(EPSILON[0]);
                        changed = true;
                    }
                }
            }
        }
    }
}

//Function to calculate FOLLOW sets
void calculateFollowSets(const std::unordered_map<int, std::set<char>>& first,
                         std::unordered_map<int, std::set<char>>& follow) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = str.size() - 1; i >= 0; --i) {
            std::string rule = str[i];
            int nonTerminal = stoi(rule.substr(0, rule.find("->")));
            std::string productions = rule.substr(rule.find("->") + 2);

            // Iterate over each production in the rule
            size_t start = 0;
            size_t end = productions.find('|');

            while (end != std::string::npos) {
                std::string production = productions.substr(start, end - start);
                for (size_t j = 0; j < production.length(); ++j) {
                    char symbol = production[j];
                    // If the symbol is a non-terminal, update its FOLLOW set
                    if (isNumber(std::string(1, symbol))) {
                        int symbolInt = stoi(std::string(1, symbol));
                        bool epsilonInBeta = true;
                        for (size_t k = j + 1; k < production.length(); ++k) {
                            char nextSymbol = production[k];
                            if (isNumber(std::string(1, nextSymbol))) {
                                int nextSymbolInt = stoi(std::string(1, nextSymbol));
                                // Add FIRST of the following symbols to FOLLOW
                                if (follow[symbolInt].size() > 0) {
                                    size_t originalSize = follow[symbolInt].size();
                                    follow[symbolInt].insert(
                                        first.at(nextSymbolInt).begin(),
                                        first.at(nextSymbolInt).end());
                                    follow[symbolInt].erase(EPSILON[0]);
                                    if (follow[symbolInt].size() != originalSize) {
                                        changed = true;
                                    }
                                }
                                // Check if epsilon is in FIRST(nextSymbol)
                                if (first.at(nextSymbolInt).find(EPSILON[0]) == first.at(nextSymbolInt).end()) {
                                    epsilonInBeta = false;
                                    break;
                                }
                            }
                        }
                        // If epsilon is in all FIRST(nextSymbol), add FOLLOW(nonTerminal) to FOLLOW(symbol)
                        if (epsilonInBeta && follow[nonTerminal].size() > 0) {
                            size_t originalSize = follow[symbolInt].size();
                            follow[symbolInt].insert(
                                follow[nonTerminal].begin(),
                                follow[nonTerminal].end());
                            if (follow[symbolInt].size() != originalSize) {
                                changed = true;
                            }
                        }
                    }
                }
                // Move to the next production
                start = end + 1;
                end = productions.find('|', start);
            }

            // Process the last production
            std::string production = productions.substr(start);
            for (size_t j = 0; j < production.length(); ++j) {
                char symbol = production[j];
                if (isNumber(std::string(1, symbol))) {
                    int symbolInt = stoi(std::string(1, symbol));
                    bool epsilonInBeta = true;
                    for (size_t k = j + 1; k < production.length(); ++k) {
                        char nextSymbol = production[k];
                        if (isNumber(std::string(1, nextSymbol))) {
                            int nextSymbolInt = stoi(std::string(1, nextSymbol));
                            // Add FIRST of the following symbols to FOLLOW
                            if (follow[symbolInt].size() > 0) {
                                size_t originalSize = follow[symbolInt].size();
                                follow[symbolInt].insert(
                                    first.at(nextSymbolInt).begin(),
                                    first.at(nextSymbolInt).end());
                                follow[symbolInt].erase(EPSILON[0]);
                                if (follow[symbolInt].size() != originalSize) {
                                    changed = true;
                                }
                            }
                            // Check if epsilon is in FIRST(nextSymbol)
                            if (first.at(nextSymbolInt).find(EPSILON[0]) == first.at(nextSymbolInt).end()) {
                                epsilonInBeta = false;
                                break;
                            }
                        }
                    }
                    // If epsilon is in all FIRST(nextSymbol), add FOLLOW(nonTerminal) to FOLLOW(symbol)
                    if (epsilonInBeta && follow[nonTerminal].size() > 0) {
                        size_t originalSize = follow[symbolInt].size();
                        follow[symbolInt].insert(
                            follow[nonTerminal].begin(),
                            follow[nonTerminal].end());
                        if (follow[symbolInt].size() != originalSize) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

int main () {  
    char non_terminal;  
    char beta;
    vector<char> alpha(10);
    string temp; //stores the final grammar rules temporarily
    int num;    
    int index=3;  
    vector<string> production(3); //stores the initial and final grammar rules
    int k = 0;
    if(k==1){ //accepting grammar as input from user
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
    for(int i=0;i<num;i++){  
        std::cout << endl << "RULE : " << production[i] << endl;
        non_terminal=production[i][0];  
        if(non_terminal==production[i][index]) {  //if there is left recursion
            int j =0;
            for(j = index+1; production[i][j] != '|'; j++){ //extracting alpha
            alpha[j-index-1]=production[i][j];
            }  
            alpha[j-index-1]='\0';  
            while(production[i][index]!=0 && production[i][index]!='|')  
                    index++;  
                    if(production[i][index]!=0) {   
                    std::cout << "It is left recursive. Eliminating left recursion: " << endl;
                    string alp(alpha.begin(), alpha.end());
                    string beta = production[i].substr(index+1); //extracting beta
                    string nt(1, non_terminal);
                    temp = nt + "->" + beta + nt + "\'"; //new rule after removing left recursion
                    std::cout << temp << endl;
                    str.push_back(temp); //adding the new rule to the final grammar rules
                    temp = nt + "\'" + "->" + alp + nt + "\'" + "|#"; //new rule after removing left recursion
                    std::cout << temp << endl;
                    str.push_back(temp); //adding the new rule to the final grammar rules
                    }  
                    else { 
                    std::cout << "can't be reduced" << endl; 
                    str.push_back(production[i]);
                    }
            }  
        else {
            std::cout << "It is not left recursive" << endl;  
            str.push_back(production[i]);
        }
        index=3;  
    } 

    std::cout << endl << "Final Grammar Rules after eliminating Left Recursion:" << endl;
    for (int i=0; i<str.size(); i++){
      std::cout << str[i] << endl;
      int j = 0;
      while(str[i][j] != '-'){
        j++;
      }
      nT.push_back(str[i].substr(0, j));
    }
    // for (int i=0; i<nT.size(); i++){
    //   std::cout << nT[i] << endl;
    // }

    unordered_map<string, int> mapping;
    unordered_map<int, string> reverseMapping;

    // Create a mapping of strings to numbers to make calculation of first and follow easy
    int count = 0;
    for (int i = 0; i < nT.size(); ++i) {
        if(nT[i].find("\'") != std::string::npos) {
          mapping[nT[i]] = count;
          reverseMapping[count] = nT[i];
          newNT.push_back(count);
          count++;
        }
        else {
          mapping[nT[i]] = count;
          reverseMapping[count] = nT[i];
          newNT.push_back(count);
          count++;
        }     
    }

    //replacing the non-terminals with numbers in the rules
    for (int i = 0; i < str.size(); ++i) {
        for (auto& nt : nT) {
          if(nt.find("\'") != std::string::npos){
            size_t pos = str[i].find(nt);
            while (pos != string::npos) {
                str[i].replace(pos, nt.length(), to_string(mapping[nt]));
                pos = str[i].find(nt);
            }}
        }
    }
    for (int i = 0; i < str.size(); ++i) {
        for (auto& nt : nT) {
          if(nt.find("\'") == std::string::npos){
            size_t pos = str[i].find(nt);
            while (pos != string::npos) {
                str[i].replace(pos, nt.length(), to_string(mapping[nt]));
                pos = str[i].find(nt);
            }}
        }
    }
    // std::cout << "Updated rules:" << endl;
    // for (const auto& rule : str) {
    //     std::cout << rule << endl;
    // }
    std::unordered_map<int, std::set<char>> first, follow;
    for (const auto& st : newNT) {
        first[st] = {};
        follow[st] = {};
    }
    follow[newNT[0]].insert('$'); // Add $ to FOLLOW of start symbol

    // Calculate FIRST and FOLLOW sets
    calculateFirstSets(first);
    calculateFollowSets(first, follow);

    // Print FIRST and FOLLOW sets
    std::cout << endl << "FIRST sets: ('#' represents epsilon)" << std::endl;
    std::cout << "------------" << endl;
    std::vector<std::pair<int, std::set<char>>> firstVec(first.begin(), first.end());
    for (auto it = firstVec.rbegin(); it != firstVec.rend(); ++it) {
        string x = reverseMapping[it->first];
        std::cout << "FIRST(" << x << "): {";
        for (char symbol : it->second) {
            if (symbol == 'i')
                std::cout << symbol << "d" << ",";
            else
                std::cout << symbol << ",";
        }
        std::cout << "}" << std::endl;
    }

    std::cout << endl << "FOLLOW sets: ('#' represents epsilon)" << std::endl;
    std::cout << "------------" << endl;
    std::vector<std::pair<int, std::set<char>>> followVec(follow.begin(), follow.end());
    for (auto it = followVec.rbegin(); it != followVec.rend(); ++it) {
        string x = reverseMapping[it->first];
        std::cout << "FOLLOW(" << x << "): {";
        for (char symbol : it->second) {
            if (symbol == 'i')
                std::cout << symbol << "d" << ",";
            else
                std::cout << symbol << ",";
        }
        std::cout << "}" << std::endl;
    }
  return 0;
}