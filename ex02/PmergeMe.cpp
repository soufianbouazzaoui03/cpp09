#include "PmergeMe.hpp"

static bool parseArg(std::string& str) {
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.size(); i++) {
        if (!isspace(str[i]) && !isdigit(str[i]))
            return false;
    }
    return true;
}

void    PmergeMe::parse(int argc, char**argv, std::vector<int>& vec, std::deque<int>& deq) {

    if (argc < 2)
        throw std::runtime_error("needs more args");
    
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if (!parseArg(str))
            throw std::runtime_error("Error!");
        int num = atoi(argv[i]);
        vec.push_back(num);
        deq.push_back(num);
    }
}

std::vector<int> jacobsquence1(int n) {
    std::vector<int> veq(n);
    std::vector<int> full;
    if (n > 0) {
        veq[0] = 0;
        full.push_back(0);
    }
    if (n > 1) {
        veq[1] = 1;
        full.push_back(1);
    }
    for (int i = 2; i < n; i++) {
        int num = veq[i - 1] + 2 * veq[i - 2];
        if (num >= n)
            break ;
        veq[i] = num;
    }
    for (int i = 2; i < veq.size(); i++) {
        int num = veq[i];
        full.push_back(num);
        while (1) {
            if (find(veq.begin(), veq.end(), num - 1) == veq.end())
                full.push_back(--num);
            else
                break;
        }
    }
    return full;
}

std::deque<int> jacobsquence2(int n) {
    
}

void PmergeMe::sortVec(std::vector<int>& vec) {
    if (vec.size() < 2)
        return ;
    std::vector<int> big, small;
    for (size_t i = 0; i < vec.size(); i += 2) {
        int num1 = vec[i];
        int num2 = vec[i + 1];

        if (num1 > num2) {
            big.push_back(num1);
            small.push_back(num2);
        } else {
            big.push_back(num2);
            small.push_back(num1);
        }
        if (vec.size() % 2)
            big.push_back(vec.back());
    }
    if (big.size() > 1)
        sortVec(vec);
    
    std::vector<int> jacobvec = jacobsquence1(small.size());
    for (size_t i = 0; i < jacobvec.size(); i++) {
        size_t index = jacobvec[i] - 1;
        if (small.size() > jacobvec[i]) {
            std::vector<int>::iterator it = big
        }
    }
    
}
void PmergeMe::sortDeq(std::deque<int>& deq) {

}