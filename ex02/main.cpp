#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <algorithm>
#include <set>


std::vector<int> jacobsequence1(int n) {
    std::vector<int> veq;
    std::vector<int> full;
    std::set<int> inserted;

    if (n <= 0) return full; // Edge case

    // Generate Jacobsthal sequence
    veq.push_back(1);
    if (n > 1) veq.push_back(3);

    for (int i = 2;; i++) {
        int num = veq[i - 1] + 2 * veq[i - 2];
        if (num >= n) break;
        veq.push_back(num);
    }

    // Insert Jacobsthal numbers and backfill missing numbers
    for (size_t i = 0; i < veq.size(); i++) {
        full.push_back(veq[i]);
        inserted.insert(veq[i]);

        // Backfill numbers until we reach an existing one
        int backfill = veq[i] - 1;
        while (backfill > 0 && inserted.find(backfill) == inserted.end()) {
            full.push_back(backfill);
            inserted.insert(backfill);
            --backfill;
        }
    }

    return full;
}

void    print(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
}

int main() {
    std::vector<int> vec = jacobsequence1(21);
    print(vec);
}