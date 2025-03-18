#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

class BitcoinExchange {
    private:
        std::map<std::string, double> data;
        
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange& cpy);
        BitcoinExchange& operator=(BitcoinExchange& cpy);
        ~BitcoinExchange();

        bool isValidDate(std::string);
        void loadData(std::string fname);
        void loadInPut(std::string fname);

        double getPrice(std::string date);

};

#endif