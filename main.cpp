#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{

    while (1) {
        string input, n1, n2, op;
        inf_int result;
        cout << "Input : ";
        getline(cin, input);        //  input에 엔터까지 입력받기
        if (input == "0") {
            cout << "Exit the program.";
            break;
        }
        int length = input.length();
        int space_first = 0, space_second = 0;      //1, 2번 째 스페이스바 위치
        for (int i = 0; i < length; i++) {
            if (input[i] == ' ') {
                if (space_first == 0)
                    space_first = i;
                else {
                    space_second = i;
                    break;
                }
            }
        }   
        n1 = input.substr(0, space_first);                 //앞 숫자 
        op = input.substr(space_first + 1, 1);            //연산자
        n2 = input.substr(space_second + 1);                   //뒷 숫자
        if (op == "+") {    
            result = inf_int(n1.c_str()) + inf_int(n2.c_str());
        }
        else if (op == "-") {
            result = inf_int(n1.c_str()) - inf_int(n2.c_str());
        }
        else if (op == "*") {
            result = inf_int(n1.c_str()) * inf_int(n2.c_str());
        }
        else {
            cout << "Invalid operator." << endl;
        }
        cout << "Output : " << result << endl;
    }

    return 0;
}
