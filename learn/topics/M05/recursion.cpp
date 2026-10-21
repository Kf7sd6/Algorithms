#include <iostream>
#include <limits>
#include <vector>

// Условия учебного примера; допустимая глубина зависит от среды.
constexpr int max_size = 512;
constexpr long long value_limit = 1000000000000LL;
static_assert(std::numeric_limits<int>::max() >= max_size);
static_assert(std::numeric_limits<long long>::max() >= 512000000000000LL);

// Предусловия: 0 <= i <= a.size() <= max_size, |a[j]| <= value_limit.
long long sum_suffix(const std::vector<long long>& a, int i) {
    int n = static_cast<int>(a.size());
    if (i == n) {
        return 0;
    }
    long long tail = sum_suffix(a, i + 1);
    return a[i] + tail;
}

// Предусловия: 0 <= l <= r <= a.size() <= max_size, те же границы значений.
long long sum_balanced(const std::vector<long long>& a, int l, int r) {
    if (l == r) {
        return 0;
    }
    if (r - l == 1) {
        return a[l];
    }
    int mid = l + (r - l) / 2;
    long long left = sum_balanced(a, l, mid);
    long long right = sum_balanced(a, mid, r);
    return left + right;
}

// Эталон исправления M05-P4. Предусловие: n >= 0.
int half_steps(int n) {
    if (n <= 1) {
        return 0;
    }
    return 1 + half_steps(n / 2);
}

int main() {
    int n;
    if (!(std::cin >> n) || n < 0 || n > max_size) {
        return 1;
    }
    std::vector<long long> a(n);
    for (long long& x : a) {
        if (!(std::cin >> x) || x < -value_limit || x > value_limit) {
            return 1;
        }
    }
    std::cout << sum_suffix(a, 0) << '\n';
    std::cout << sum_balanced(a, 0, n) << '\n';
    return 0;
}
