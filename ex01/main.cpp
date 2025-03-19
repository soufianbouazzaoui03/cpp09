#include "RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr<<"args error\n";
        exit(1);
    }
    RPN rpn;
    rpn.parsInput(argv[1]);
    rpn.calculate(argv[1]);
}