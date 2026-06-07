#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

int main() {
    const int MAX_N = 8;
    const int K = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << "n\tgetAllPerms(ms)\tgetPerm1(mks)\tgetPerm2(mks)\n";
    std::cout << "--------------------------------------------------------\n";
    for (int n = 1; n <= MAX_N; ++n) {
        std::vector<char> in;
        for (int i = 0; i < n; ++i) {
            in.push_back('1' + i);
        }
        PMTree tree(in);
        int64_t total = tree.getTotal();
        if (total == 0) continue;
        auto start = std::chrono::steady_clock::now();
        auto all = getAllPerms(tree);
        auto end = std::chrono::steady_clock::now();
        auto time_all = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::vector<int> rand_nums(K);
        std::uniform_int_distribution<int> dist(1, static_clock::duration::rep(total));
        for (int i = 0; i < K; ++i) {
            rand_nums[i] = dist(gen);
        }
        int64_t time1_sum = 0;
        for (int num : rand_nums) {
            start = std::chrono::steady_clock::now();
            auto p1 = getPerm1(tree, num);
            end = std::chrono::steady_clock::now();
            time1_sum += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        double avg1 = static_cast<double>(time1_sum) / K;
        int64_t time2_sum = 0;
        for (int num : rand_nums) {
            start = std::chrono::steady_clock::now();
            auto p2 = getPerm2(tree, num);
            end = std::chrono::steady_clock::now();
            time2_sum += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        double avg2 = static_cast<double>(time2_sum) / K;
        std::cout << n << "\t" << std::fixed << std::setprecision(2) << time_all << "\t\t"  << avg1 << "\t\t"  << avg2 << "\n";
    }

    return 0;
}
