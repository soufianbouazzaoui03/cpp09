#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(BitcoinExchange& cpy) {
    data = cpy.data;
}
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange& cpy) {
    if (this != &cpy) {
        data = cpy.data;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange(){};

std::string trim(const std::string& str) {
    size_t start = 0;
    while (start < str.size() && std::isspace(str[start])) {
        ++start;
    }

    size_t end = str.size();
    while (end > start && std::isspace(str[end - 1])) {
        --end;
    }

    return str.substr(start, end - start);
}

void    parsPrice(std::string str, double& price) {
    std::stringstream ss(str);

    ss >> price;
    if (ss.fail() || !ss.eof()) {
        throw 1;
        return;
    }
    if (price <= 0 || price >= 1000) {
        throw 2;
        return;
    }
}

bool parsDate(std::string date) {
    std::stringstream ss(date);
    std::string yearStr;
    std::string monthStr;
    std::string dayStr;

    int year, month, day;

    if (date.empty() || date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    if (std::getline(ss, yearStr, '-') && std::getline(ss, monthStr, '-') && std::getline(ss, dayStr)) {
        try {
            year = std::stoi(yearStr);
            month = std::stoi(monthStr);
            day = std::stoi(dayStr);
        } catch(...){return false;}
        if (year < 2009) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false; 
    }
    return true;
    
}

bool isPriceValid(std::string input) {
    if (input.empty())
        return false;

    bool hasDecimal = false;

    if (!isdigit(input[0]) && input[0] != '+' && input[0] != '-')
        return false;

    for (size_t i = 1; i < input.size(); i++)
    {
        if (isdigit(input[i]))
            continue;

        if (input[i] == '.')
        {
            if (hasDecimal || i == 0 || i == input.size() - 1)
                return false;
            hasDecimal = true;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void BitcoinExchange::loadInPut(std::string fname) {
    std::ifstream file(fname);
    if (!file) {
        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    std::getline(file, line);
    if (line != "date | value")
        std::cerr << "Error: bad input => " << line << std::endl;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string date, priceStr;
        double price;

        if (!(std::getline(ss, date, '|') && std::getline(ss, priceStr)))
            continue;
        date = trim(date);
        if (!parsDate(date)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        priceStr = trim(priceStr);
        if (!isPriceValid(priceStr)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        //****
        try {
            price = std::stod(priceStr);
        }catch(...){
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        //****
        try {
            parsPrice(priceStr, price);
        }catch (int e){
            if (e == 1)
               std::cerr << "Error: bad input => " << line << std::endl; 
            else
                std::cerr << (price < 0 ? "Error: not a positive number." : "Error: too large a number.") << std::endl;
            continue;
        }

        std::map<std::string, double>::iterator it = data.lower_bound(date);
        std::cout << date << " => " << price << " = " << price * it->second << std::endl;

    }

}

void    BitcoinExchange::loadData(std::string fname) {
    std::ifstream file(fname);
    if (!file) {
        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, priceStr;
        double price;

        if (std::getline(ss, date, ',') && std::getline(ss, priceStr)) {
            try {
                price = std::stod(priceStr);
                data[date] = price;
            } catch (std::exception& e) {
                std::cerr<< e.what();
            }
        } else {
                std::cerr << "Error: bad line in database => " << line << std::endl;
        }
    }
    file.close();
}