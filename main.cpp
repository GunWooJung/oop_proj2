#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>
                  
using namespace std;

void showVector(vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
};
int prior(string s) {
    if (s == "+") return 1;
    else if (s == "-") return 1;
    else if (s == "*") return 2;
    else return -1;
};
int main()
{
    while (1) {
        vector<string> token;
        cout << "Input : ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "Exit the program";
            break;
        }
        int length = input.length();
        int index = 0;
        for (int i = 0; i < length; i++) {
            if (input[i] == ' ') {
                string addToken = input.substr(index, i - index);
                token.push_back(addToken);
                index = i + 1;
            }
        }
        string addToken = input.substr(index);
        token.push_back(addToken);
        vector<string> postFix;
        vector<string> stack;
        for (int i = 0; i < token.size(); i++) {
            if (token[i] == "(") {
                stack.push_back(token[i]);
            }
            else if (token[i] == ")") {
                string pop = stack[stack.size() - 1];
                while (pop != "(") {
                    postFix.push_back(pop);
                    stack.pop_back();
                    pop = stack[stack.size() - 1];
                }
                stack.pop_back();
            }
            else if (token[i] == "+" || token[i] == "-" || token[i] == "*") {
                if (stack.size() == 0)
                    stack.push_back(token[i]);
                else {
                    while (prior(token[i]) <= prior(stack[stack.size() - 1])) {
                        string pop = stack[stack.size() - 1];
                        postFix.push_back(pop);
                        stack.pop_back();
                        if (stack.size() == 0) break;
                    }
                    stack.push_back(token[i]);
                }
            }
            else {
                postFix.push_back(token[i]);
            }
        }
        while (stack.size() != 0) {
            string pop = stack[stack.size() - 1];
            postFix.push_back(pop);
            stack.pop_back();
        }

        vector<inf_int> postStack;
        for (int i = 0; i < postFix.size(); i++) {
            if (postFix[i] == "+") {
                inf_int result;
                result = result + postStack[postStack.size() - 1];
                postStack.pop_back();
                result = result + postStack[postStack.size() - 1];
                postStack.pop_back();
                postStack.push_back(result);
            }
            else if (postFix[i] == "-") {
                inf_int result;
                result = result + postStack[postStack.size() - 1];
                postStack.pop_back();
                result = result - postStack[postStack.size() - 1];
                postStack.pop_back();
                postStack.push_back(result);
            }
            else if (postFix[i] == "*") {
                inf_int result;
                result = result + postStack[postStack.size() - 1];
                postStack.pop_back();
                result = result * postStack[postStack.size() - 1];
                postStack.pop_back();
                postStack.push_back(result);
            }
            else {
                postStack.push_back(inf_int(postFix[i].c_str()));
            }
        }
        cout << "Output : "<< postStack[0]<<endl;
    }
    return 0;
}
