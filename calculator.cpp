#include "calculator.h"

int calculator::priority(std::string s) {
    if (s == "+") return 1;
    else if (s == "-") return 1;
    else if (s == "*") return 2;
    else if (s == "/") return 2;
    else if (s == "^") return 3;
    else return -1;
};
bool calculator::verifyToken(std::string s) {
    if (s=="(" || s==")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^") return true;
    if (s[0] < '0' || s[0] > '9') {
        if (s[0] != '-') return false;
    }
    for (int i = 1; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}
void calculator::divideByToken(const std::string& input, std::vector<std::string>& token){
    int length = input.length();
    int index = 0;
    for (int i = 0; i < length; i++) {                                   //divide token by space bar
        if (input[i] == ' ') {
            std::string addToken = input.substr(index, i - index);
            if (!verifyToken(addToken)) throw addToken;
            token.push_back(addToken);
            index = i + 1;
        }
    }
    std::string addToken = input.substr(index);
    if (!verifyToken(addToken)) throw addToken;
    token.push_back(addToken);
}
void calculator::covertToPostFix(const std::vector<std::string>& token,std::vector<std::string>& postFix) {
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
        else if (token[i] == "+" || token[i] == "-" || token[i] == "*" || token[i] == "^" || token[i] == "/") {
            if (stack.empty())
                stack.push_back(token[i]);
            else {
                while (priority(token[i]) <= priority(stack[stack.size() - 1])) {
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
        postFix.push_back(stack[stack.size() - 1]);
        stack.pop_back();
    }
}
inf_int calculator::calculatePostFix(const std::vector<std::string>& postFix) {
    std::vector<inf_int> postStack;
    inf_int result;
    for (int i = 0; i < postFix.size(); i++) {                
        if (postFix[i] == "+" || postFix[i] == "-" || postFix[i] == "*" || postFix[i] == "^" || postFix[i] == "/") {
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
            else if (postFix[i] == "/") {
                if (n2 == 0) throw n2;
                postStack.push_back(n1 / n2);
            }
            else if (postFix[i] == "^") {
                if (n2 < 0) throw n2;
                postStack.push_back(n1 ^ n2);
            }
        }
        else {
            postStack.push_back(inf_int(postFix[i].c_str()));
        }
    }
    result = postStack[0];
    return result;
}

void calculator::run() {
    while (true) {
    try {
            std::string input;
            std::vector<std::string> token;
            std::vector<std::string> postFix;
            inf_int output;
            std::cout << "Format : (integer)(space)(operator)(space)(positive integer)…"<<std::endl;
            std::cout << "Operator : ( ) + - * / ^" << std::endl;
            std::cout << "Input : ";                                              
            std::getline(std::cin, input);                           //enter the input string
            if (input == "0") {                                                   //Exit the program
                std::cout << "Exit the program";
                break;
            }
            std::chrono::steady_clock::time_point begin = std::chrono::high_resolution_clock::now();
            divideByToken(input, token);
            covertToPostFix(token, postFix);
            output = calculatePostFix(postFix);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time elapsed : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            std::cout << "Output : " <<output << std::endl << std::endl;
        }
        catch (inf_int n) {
            if(n==0) std::cout << "Cannot divide by " << n  <<"."<<std::endl<< std::endl;
            if(n<0) std::cout << "Cannot power by negative integer." << std::endl<< std::endl;
        }
        catch (std::string token) {
            std::cout << "Format Error : Invaild number or operator." << std::endl<<std::endl;
        }
        catch (...) {
            std::cout << "Error : please try again." << std::endl<< std::endl;
        }
    }
}
