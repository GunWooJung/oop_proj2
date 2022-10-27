#include "calculator.h"

int calculator::prior(std::string s) {
    if (s == "+") return 1;
    else if (s == "-") return 1;
    else if (s == "*") return 2;
    else if (s == "^") return 3;
    else return -1;
};

void calculator::run() {
    while (true) {
        std::vector<std::string> token;
        std::cout << "Input : ";
        std::string input;

        std::getline(std::cin, input);

        if (input == "0") {
            std::cout << "Exit the program";
            break;
        }
        int length = input.length();
        int index = 0;
        for (int i = 0; i < length; i++) {
            if (input[i] == ' ') {
                std::string addToken = input.substr(index, i - index);
                token.push_back(addToken);
                index = i + 1;
            }
        }
        std::string addToken = input.substr(index);
        token.push_back(addToken);
        std::vector<std::string> postFix;
        std::vector<std::string> stack;
        for (int i = 0; i < token.size(); i++) {
            if (token[i] == "(") {
                stack.push_back(token[i]);
            }
            else if (token[i] == ")") {
                std::string pop = stack[stack.size() - 1];
                while (pop != "(") {
                    postFix.push_back(pop);
                    stack.pop_back();
                    pop = stack[stack.size() - 1];
                }
                stack.pop_back();
            }
            else if (token[i] == "+" || token[i] == "-" || token[i] == "*" || token[i] == "^") {
                if (stack.empty())
                    stack.push_back(token[i]);
                else {
                    while (prior(token[i]) <= prior(stack[stack.size() - 1])) {
                        std::string pop = stack[stack.size() - 1];
                        postFix.push_back(pop);
                        stack.pop_back();
                        if (stack.empty()) break;
                    }
                    stack.push_back(token[i]);
                }
            }
            else {
                postFix.push_back(token[i]);
            }
        }
        while (!stack.empty()) {
            std::string pop = stack[stack.size() - 1];
            postFix.push_back(pop);
            stack.pop_back();
        }
        std::vector<inf_int> postStack;
        for (int i = 0; i < postFix.size(); i++) {
            if (postFix[i] == "+" || postFix[i] == "-" || postFix[i] == "*" || postFix[i] == "^") {
                inf_int n2 = postStack[postStack.size() - 1];
                postStack.pop_back();
                inf_int n1 = postStack[postStack.size() - 1];
                postStack.pop_back();

                if (postFix[i] == "+") {
                    postStack.push_back(n1 + n2);
                }
                else if (postFix[i] == "-") {
                    postStack.push_back(n1 - n2);
                }
                else if (postFix[i] == "*") {
                    postStack.push_back(n1 * n2);
                }
                else if (postFix[i] == "^") {                    
                    postStack.push_back(n1 ^ n2);
                }
            }
            else {
                postStack.push_back(inf_int(postFix[i].c_str()));
            }
        }
        std::cout << "Output : "<< postStack[0]<< std::endl;
    }
}
