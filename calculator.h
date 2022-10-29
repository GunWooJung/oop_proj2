#ifndef OOP_PROJ2_CALCULATOR_H
#define OOP_PROJ2_CALCULATOR_H

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include "inf_int.h"

class calculator {
private:
    static int prior(std::string);
    static bool verifyToken(std::string);
public:
    static void run();
};

#endif //OOP_PROJ2_CALCULATOR_H
