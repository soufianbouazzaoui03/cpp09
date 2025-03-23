#include "PmergeMe.hpp"

void    print2(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout<<"\n";
}
void    print3(std::deque<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout<<"\n";
}

int main(int argc, char** argv) {

    try {
        std::vector<int> vec;
        std::deque<int> deq;
        PmergeMe pm;

        pm.parse(argc, argv, vec, deq);

        clock_t startVec = clock();
        pm.sortVec(vec);
        clock_t endVec = clock();
        double durationVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;

        clock_t startDeq = clock();
        pm.sortDeq(deq);
        clock_t endDeq = clock();
        double durationDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

        std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: "
              << durationVec << " us" << std::endl;
        std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: "
              << durationDeq << " us" << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}