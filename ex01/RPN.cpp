#include "RPN.hpp"

RPN::RPN(){}
RPN::~RPN(){}
RPN::RPN(RPN& cpy) : st(cpy.st){}
RPN& RPN::operator=(RPN& cpy) {
    if (this != & cpy) {
        st = cpy.st;
    }
    return *this;
}
void    RPN::parsInput(std::string str) {

    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]) && !isspace(str[i]) && (str[i] != '+' && str[i] != '*' && str[i] != '/' && str[i] != '-')) {
            std::cerr<<"bad input!\n";
            exit(1);
        }
    }
}

int calcul(int num1, int num2, char op) {
    if (op == '+')
        return num1 + num2;
    if (op == '-')
        return num1 - num2;
    if (op == '*')
        return num1 * num2;
    else {
        if (num2 == 0) {
            std::cerr<<"cant / by 0\n";
            exit(1);
        }
        return num1 / num2;
    }
    return -1;
}


void    RPN::calculate(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (isspace(str[i]))
            continue;
        if (isdigit(str[i])) {
            st.push(str[i] - '0');
            continue;
        }
        if (st.size() < 2) {
            std::cerr<<"not enough numbers in stack\n";
            exit(1);
        }
        else {
            int num2 = st.top();
            st.pop();
            int num1 = st.top();
            st.pop();
            st.push(calcul(num1, num2, str[i]));
        }
        if (st.size() != 1)
        {
            std::cerr<<"error\n";
            exit(1);
        }
        std::cout<<st.top();
    }
}