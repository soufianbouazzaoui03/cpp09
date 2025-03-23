#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(PmergeMe& cpy){
    (void)cpy;
}
PmergeMe& PmergeMe::operator=(PmergeMe& cpy) {
    (void)cpy;
    return *this;
}

static bool parseArg(const std::string& str) {
    if (str.empty())
        return false;
    
    size_t i = 0;
    if (str[i] == '+')
        i++;
    
    if (i == str.size())
        return false;

    for (; i < str.size(); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

void    PmergeMe::parse(int argc, char**argv, std::vector<int>& vec, std::deque<int>& deq) {

    if (argc < 2)
        throw std::runtime_error("needs more args");
    
    for (int i = 1; i < argc; i++) {
        std::string str = argv[i];
        if (!parseArg(str))
            throw std::runtime_error("Error!");
        int num = std::stoi(str);
        vec.push_back(num);
        deq.push_back(num);
    }
}

std::vector<int> jacobsequence1(int n) {
    std::vector<int> veq;
    std::vector<int> full;
    std::set<int> inserted;

    if (n <= 0) return veq;

    veq.push_back(1);
    if (n > 1) veq.push_back(3);

    for (int i = 2;; i++) {
        int num = veq[i - 1] + 2 * veq[i - 2];
        if (num >= n) break;
            veq.push_back(num);
    }
    return veq;
}

std::deque<int> jacobsquence2(int n) {
    std::deque<int> veq;

    if (n <= 0) return veq;

    veq.push_back(1);
    if (n > 1) veq.push_back(3);

    for (int i = 2;; i++) {
        int num = veq[i - 1] + 2 * veq[i - 2];
        if (num >= n) break;
            veq.push_back(num);
    }
    return veq;
}

// void    print(std::vector<int>& vec, std::string str) {
//     std::cout<<str << s++ << std::endl;
//     for (size_t i = 0; i < vec.size(); i++) {
//         std::cout << vec[i] << " ";
//     }
//     std::cout<<"\n";
// }

std::deque<int> merge(std::deque<int>& main, std::deque<int>& pend) {
    std::deque<int> jacobvec = jacobsquence2(pend.size());
    std::set<int> inserted_index;
    std::deque<int> sorted = main;
    for (size_t i = 0; i < jacobvec.size(); i++) {
        size_t index = jacobvec[i] - 1;
        if (index < pend.size()) {
            std::deque<int>::iterator it = std::upper_bound(sorted.begin(), sorted.end(), pend[index]);
            sorted.insert(it, pend[index]);
            inserted_index.insert(index);
        }
    }
    for (size_t i = 0; i < pend.size(); i++) {
        if (inserted_index.find(i) == inserted_index.end()) {
            std::deque<int>::iterator it = std::upper_bound(sorted.begin(), sorted.end(), pend[i]);
            sorted.insert(it, pend[i]);
        }
    }
    return sorted;
}

void PmergeMe::sortDeq(std::deque<int>& deq) {
    if (deq.size() < 2)
        return ;
    std::deque<int> big, small;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        int num1 = deq[i];
        int num2 = deq[i + 1];

        if (num1 > num2) {
            big.push_back(num1);
            small.push_back(num2);
        } else {
            big.push_back(num2);
            small.push_back(num1);
        }
    }
    if (deq.size() % 2)
        big.push_back(deq.back());
    if (big.size() > 1)
        sortDeq(big);
    deq = merge(big, small);
}

std::vector<int> merge(std::vector<int>& main, std::vector<int>& pend) {
    std::vector<int> jacobvec = jacobsequence1(pend.size());
    std::set<int> inserted_index;
    std::vector<int> sorted = main;
    for (size_t i = 0; i < jacobvec.size(); i++) {
        size_t index = jacobvec[i] - 1;
        if (index < pend.size()) {
            std::vector<int>::iterator it = std::upper_bound(sorted.begin(), sorted.end(), pend[index]);
            sorted.insert(it, pend[index]);
            inserted_index.insert(index);
        }
    }
    for (size_t i = 0; i < pend.size(); i++) {
        if (inserted_index.find(i) == inserted_index.end()) {
            std::vector<int>::iterator it = std::upper_bound(sorted.begin(), sorted.end(), pend[i]);
            sorted.insert(it, pend[i]);
        }
    }
    return sorted;
}

void PmergeMe::sortVec(std::vector<int>& vec) {
    if (vec.size() < 2)
        return ;
    std::vector<int> big, small;
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        int num1 = vec[i];
        int num2 = vec[i + 1];

        if (num1 > num2) {
            big.push_back(num1);
            small.push_back(num2);
        } else {
            big.push_back(num2);
            small.push_back(num1);
        }
    }
    if (vec.size() % 2)
        big.push_back(vec.back());
    if (big.size() > 1)
        sortVec(big);
    // print(vec, "vec ");
    // std::cout<<"----------------------\n";
    // print(big, "big ");
    // std::cout<<"----------------------\n";
    // print(small, "small ");
    // std::cout<<"----------------------\n";
    vec = merge(big, small);
}
