#ifndef OOP_PROJ2_CALCULATOR_H
#define OOP_PROJ2_CALCULATOR_H

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include "inf_int.h"

class calculator {
private:
    static int priority(std::string);           //Priority of operator
    static bool verifyToken(std::string);       //Verifing whether token is vaild
    static void divideByToken(const std::string& , std::vector<std::string>&);  //Divide input string with token
    static void covertToPostFix(const std::vector<std::string>& , std::vector<std::string>&); //Convert to PostFix notation
    static inf_int calculatePostFix(const std::vector<std::string>&);     //Calculating PostFix notation
public:
    static void run();
};

#endif //OOP_PROJ2_CALCULATOR_H
