#include "PmergeMe.hpp"

// std::vector<int> jacobsequence1(int n) {
//     std::vector<int> veq;
//     std::vector<int> full;
//     std::set<int> inserted;

//     if (n <= 0) return full; // Edge case

//     // Generate Jacobsthal sequence
//     veq.push_back(1);
//     if (n > 1) veq.push_back(3);

//     for (int i = 2;; i++) {
//         int num = veq[i - 1] + 2 * veq[i - 2];
//         if (num >= n) break;
//         veq.push_back(num);
//     }

//     // Insert Jacobsthal numbers and backfill missing numbers
//     for (size_t i = 0; i < veq.size(); i++) {
//         full.push_back(veq[i]);
//         inserted.insert(veq[i]);

//         // Backfill numbers until we reach an existing one
//         int backfill = veq[i] - 1;
//         while (backfill > 0 && inserted.find(backfill) == inserted.end()) {
//             full.push_back(backfill);
//             inserted.insert(backfill);
//             --backfill;
//         }
//     }

//     return full;
// }

// void    print(std::vector<int>& vec) {
//     for (size_t i = 0; i < vec.size(); i++) {
//         std::cout << vec[i] << " ";
//     }
// }

void    print2(std::vector<int>& vec) {
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