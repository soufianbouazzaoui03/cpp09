#include "BitcoinExchange.hpp"
#include <fstream>

int main(int argc, char** argv) {
    if (argc!=2) {
        return 1;
    }
    BitcoinExchange bic;
    bic.loadData("data.csv");
    bic.loadInPut(argv[1]);
}