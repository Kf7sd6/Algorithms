#include <iostream>
#include <vector>

// Valid input: 0 <= n <= 200000; x and all values are in [-1e9, 1e9].
// Return the first matching index, or -1. The input is not copied.
long long find_first(const std::vector<long long>& a, long long x) {
    long long n = static_cast<long long>(a.size());
    long long i = 0;
    while (i < n) {
        if (a[i] == x) {
            return i;
        }
        i = i + 1;
    }
    return -1;
}

// Precondition: 1 <= a.size() <= 200000.
long long maximum_nonempty(const std::vector<long long>& a) {
    long long n = static_cast<long long>(a.size());
    long long best = a[0];
    long long i = 1;
    while (i < n) {
        if (a[i] > best) {
            best = a[i];
        }
        i = i + 1;
    }
    return best;
}

// Input: n x, then n values. Output: first index; maximum or EMPTY.
int main() {
    long long n = 0;
    long long x = 0;
    std::cin >> n >> x;
    std::vector<long long> a;
    for (long long i = 0; i < n; i = i + 1) {
        long long value = 0;
        std::cin >> value;
        a.push_back(value);
    }
    std::cout << find_first(a, x) << '\n';
    if (n == 0) {
        std::cout << "EMPTY\n";
    } else {
        std::cout << maximum_nonempty(a) << '\n';
    }
    return 0;
}
