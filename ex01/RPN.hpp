#ifndef RPN_HPP
#define RPN_HPP

#include<iostream>
#include <stack>

class RPN {
    private:
        std::stack<int> st;
    public:
        RPN();
        RPN(RPN& cpy);
        RPN& operator=(RPN& cpy);
        ~RPN();
        void    parsInput(std::string str);
        void    calculate(std::string str);
};

#endif