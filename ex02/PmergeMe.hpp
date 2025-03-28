#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <algorithm>
#include <set>

class PmergeMe {
    public:
        PmergeMe();
        PmergeMe(PmergeMe& cpy);
        PmergeMe& operator=(PmergeMe& cpy);
        ~PmergeMe();
        void    parse(int argc, char**argv, std::vector<int>& vec, std::deque<int>& deq);
        static void sortVec(std::vector<int>& vec);
        static void sortDeq(std::deque<int>& deq);
        

};

#endif