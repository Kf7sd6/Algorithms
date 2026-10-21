#include <iostream>
#include <vector>

// Input: 0 <= n <= 200000, then n integers in [-1000000000, 1000000000].
// The input is valid. Output: the number of strictly positive elements.
long long count_positive(const std::vector<long long>& values) {
    long long count = 0;
    for (long long x : values) {
        if (x > 0) {
            count = count + 1;
        }
    }
    return count;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::vector<long long> values;
    long long processed = 0;

    while (processed < n) {
        long long x = 0;
        std::cin >> x;
        values.push_back(x);
        processed = processed + 1;
    }

    long long answer = count_positive(values);
    std::cout << answer << '\n';
    return 0;
}
