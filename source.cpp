#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>

void sum(const std::vector<int>& arr, int start, int end, long &result) {
    result = std::accumulate(arr.begin() + start, arr.begin() + end, 0LL);
}

int main() {
    const int N = 1000;
    const int M = 5;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<int> arr(N);
    for(int i = 0; i < N; ++i) arr[i] = std::rand() % 100;

    std::vector<std::thread> threads;
    std::vector<long> results(M,0);

    int size = N / M;
    for(int i = 0; i < M; ++i) {
        int start = i * size;
        int end = (i == M - 1) ? N : start + size;
        threads.emplace_back(sum, std::ref(arr), 
            start, end, std::ref(results[i]));
    }
    for(auto& thread : threads) thread.join();
        
    long total_sum = std::accumulate(results.begin(), results.end(), 0LL);
    std::cout << "Sum all elements: " << total_sum << std::endl;
    return 0;
}