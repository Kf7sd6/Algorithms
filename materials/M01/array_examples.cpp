#include <array>
#include <iostream>

constexpr int CAPACITY = 8;

// Во всех функциях 0 <= n <= CAPACITY; данные занимают [0, n).
// const ...&: читать исходный массив без копирования и изменения.
int find_first(const std::array<int, CAPACITY>& a, int n, int x) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}

// int& n: изменение длины должно остаться у вызывающего кода.
bool insert_at(std::array<int, CAPACITY>& a, int& n, int pos, int x) {
    if (pos < 0 || pos > n || n == CAPACITY) {
        return false;
    }
    for (int j = n; j > pos; --j) {
        a[j] = a[j - 1];
    }
    a[pos] = x;
    ++n;
    return true;
}

bool erase_at(std::array<int, CAPACITY>& a, int& n, int pos) {
    if (pos < 0 || pos >= n) {
        return false;
    }
    for (int j = pos; j + 1 < n; ++j) {
        a[j] = a[j + 1];
    }
    --n;
    return true;
}

bool erase_unordered(std::array<int, CAPACITY>& a, int& n, int pos) {
    if (pos < 0 || pos >= n) {
        return false;
    }
    a[pos] = a[n - 1];
    --n;
    return true;
}

void print_sequence(const std::array<int, CAPACITY>& a, int n) {
    std::cout << '[';
    for (int i = 0; i < n; ++i) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << a[i];
    }
    std::cout << "]\n";
}

int main() {
    std::array<int, CAPACITY> a{6, -1, 6, 4};
    int n = 4;

    print_sequence(a, n);
    std::cout << "find 4: " << find_first(a, n, 4) << '\n';

    if (insert_at(a, n, 2, 9)) {
        print_sequence(a, n);
    }
    if (erase_at(a, n, 1)) {
        print_sequence(a, n);
    }
    if (erase_unordered(a, n, 1)) {
        print_sequence(a, n);
    }
    return 0;
}
