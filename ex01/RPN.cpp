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
    if (str.empty()) {
        throw std::runtime_error("empty input!");
    }
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]) && !isspace(str[i]) && (str[i] != '+' && str[i] != '*' && str[i] != '/' && str[i] != '-')) {
            throw std::runtime_error("bad input!");
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
            throw std::runtime_error("cant / by 0");
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
            throw std::runtime_error("not enough numbers in stack");
        }
        else {
            int num2 = st.top();
            st.pop();
            int num1 = st.top();
            st.pop();
            st.push(calcul(num1, num2, str[i]));
        }
    }
    if (st.size() != 1)
    {
        throw std::runtime_error("error");
    }
    std::cout<<st.top();
}