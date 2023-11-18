// task_3.cpp: определяет точку входа для приложения.
//

#include "task_3.h"
#include "rational.h"

int main() {
    std::string input;
    getline(std::cin, input);
    std::stringstream ss(input);
    Rational r1, r2;
    char operation;
    // num/demon operator num2/denom2 =
    try {
        ss >> r1;
        ss.ignore(1);
        ss >> operation;
        ss.ignore(1);
        ss >> r2;
    }
    catch (std::exception& ex) {
        std::cout << "Invalid argument" << std::endl;
        return 1;
    }
    //std::cout << operation << '\n';
    Rational res;
    try {
        switch (operation) {
        case '+': {
            res = r1 + r2;
            break;
        }
        case '-': {
            res = r1 - r2;
            break;
        }
        case '*': {
            res = r1 * r2;
            break;
        }
        case '/': {
            res = r1 / r2;
            break;
        }
        default: {
            std::cout << "Invalid operation" << std::endl;
        }
        }
    }
    catch (std::exception& ex) {
        std::cout << "Division by zero" << std::endl;
        return 2;
    }
    //ss << res;
    //if (r1 == r2) std::cout << "EQUAL!!\n";
    std::cout << "RESULT : " << res.Numerator() << " / " << res.Denominator() << '\n';
    return 0;
}
