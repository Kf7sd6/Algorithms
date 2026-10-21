#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

static_assert(std::numeric_limits<int>::max() >= 200000,
              "The example needs int to represent 200000");

// All array functions require size <= 200000. Binary searches also require
// nondecreasing order. They return indices; size is the end position.
int linear_first(const std::vector<long long>& a, long long x) {
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; ++i) {
        if (a[i] == x) {
            return i;
        }
    }
    return n;
}

int lower_bound_index(const std::vector<long long>& a, long long x) {
    int l = 0;
    int r = static_cast<int>(a.size());
    while (l < r) {
        const int mid = l + (r - l) / 2;
        if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

bool contains(const std::vector<long long>& a, long long x) {
    const int pos = lower_bound_index(a, x);
    const int n = static_cast<int>(a.size());
    return pos < n && a[pos] == x;
}

int upper_bound_index(const std::vector<long long>& a, long long x) {
    int l = 0;
    int r = static_cast<int>(a.size());
    while (l < r) {
        const int mid = l + (r - l) / 2;
        if (a[mid] <= x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

int count_equal(const std::vector<long long>& a, long long x) {
    const int left = lower_bound_index(a, x);
    const int right = upper_bound_index(a, x);
    return right - left;
}

// Candidates are integer days 0..days-1; days is the no-answer position.
// Requires 0 <= days <= 200000 and 0 <= need <= 10^12.
int first_sufficient(int days, long long need) {
    int l = 0;
    int r = days;
    while (l < r) {
        const int mid = l + (r - l) / 2;
        if (7LL * mid < need) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

// Input: n q, then n sorted values, then q query values.
// Output per query: lower upper contains count.
int main() {
    int n = 0;
    int q = 0;
    if (!(std::cin >> n >> q) || n < 0 || n > 200000 ||
        q < 0 || q > 200000) {
        return 1;
    }
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> a[i]) || a[i] < -1000000000000LL ||
            a[i] > 1000000000000LL || (i > 0 && a[i - 1] > a[i])) {
            return 1;
        }
    }
    for (int j = 0; j < q; ++j) {
        long long x = 0;
        if (!(std::cin >> x) || x < -1000000000000LL ||
            x > 1000000000000LL) {
            return 1;
        }
        const int left = lower_bound_index(a, x);
        const int right = upper_bound_index(a, x);
        const bool found = left < n && a[left] == x;
        std::cout << left << ' ' << right << ' ' << found << ' '
                  << right - left << '\n';
    }
}
