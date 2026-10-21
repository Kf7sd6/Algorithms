#include <array>
#include <iostream>
#include <string>
#include <vector>

// Educational implementations. Mutate fields only through these operations.
constexpr int CAPACITY = 3;

struct Stack {
    std::array<int, CAPACITY> a{};
    int n = 0;

    bool push(int x) {
        if (n == CAPACITY) return false;
        a[n] = x;
        ++n;
        return true;
    }

    bool pop(int& out) {
        if (n == 0) return false;
        --n;
        out = a[n];
        return true;
    }

    bool top(int& out) const {
        if (n == 0) return false;
        out = a[n - 1];
        return true;
    }
};

struct Queue {
    std::array<int, CAPACITY> a{};
    int head = 0;
    int n = 0;

    bool enqueue(int x) {
        if (n == CAPACITY) return false;
        a[(head + n) % CAPACITY] = x;
        ++n;
        return true;
    }

    bool dequeue(int& out) {
        if (n == 0) return false;
        out = a[head];
        head = (head + 1) % CAPACITY;
        --n;
        return true;
    }

    bool front(int& out) const {
        if (n == 0) return false;
        out = a[head];
        return true;
    }
};

struct Node {
    int value;
    Node* next;
};

struct SinglyList {
    Node* head = nullptr;

    SinglyList() = default;
    SinglyList(const SinglyList&) = delete;
    SinglyList& operator=(const SinglyList&) = delete;
    ~SinglyList() { clear(); }

    void push_front(int x) {
        head = new Node{x, head};
    }

    Node* find(int x) const {
        Node* p = head;
        while (p != nullptr && p->value != x) p = p->next;
        return p;
    }

    // p must be nullptr or a live node belonging to this list.
    bool insert_after(Node* p, int x) {
        if (p == nullptr) return false;
        Node* u = new Node{x, p->next};
        p->next = u;
        return true;
    }

    // Membership is a precondition; it is not checked by a traversal.
    bool erase_after(Node* p) {
        if (p == nullptr || p->next == nullptr) return false;
        Node* victim = p->next;
        p->next = victim->next;
        delete victim;
        return true;
    }

    bool pop_front(int& out) {
        if (head == nullptr) return false;
        Node* victim = head;
        out = victim->value;
        head = victim->next;
        delete victim;
        return true;
    }

    void clear() {
        while (head != nullptr) {
            Node* victim = head;
            head = victim->next;
            delete victim;
        }
    }
};

// A separate, non-owning example. Nodes below have automatic lifetime.
struct DNode {
    int value;
    DNode* prev;
    DNode* next;
};

void init_ring(DNode* sentinel) {
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
}

// w is in the ring (possibly the sentinel); u is a detached live node.
void insert_before(DNode* w, DNode* u) {
    u->prev = w->prev;
    u->next = w;
    w->prev->next = u;
    w->prev = u;
}

// u is a live linked data node, never the sentinel.
void unlink_node(DNode* u) {
    u->prev->next = u->next;
    u->next->prev = u->prev;
    u->prev = nullptr;
    u->next = nullptr;
}

bool brackets_ok(const std::string& s) {
    std::vector<char> pending;
    pending.reserve(s.size());
    for (char c : s) {
        if (c == '(' || c == '[') {
            pending.push_back(c);
        } else if (c == ')' || c == ']') {
            if (pending.empty()) return false;
            const char expected = (c == ')') ? '(' : '[';
            if (pending.back() != expected) return false;
            pending.pop_back();
        } else {
            return false;
        }
    }
    return pending.empty();
}

#ifndef M03_NO_MAIN
int main() {
    Stack s;
    s.push(6);
    s.push(-3);
    int out = 0;
    if (s.pop(out)) std::cout << "stack: " << out << '\n';

    Queue q;
    q.enqueue(6);
    q.enqueue(-3);
    q.enqueue(8);
    q.dequeue(out);
    q.enqueue(11);
    std::cout << "queue:";
    while (q.dequeue(out)) std::cout << ' ' << out;
    std::cout << '\n';

    SinglyList list;
    list.push_front(8);
    list.push_front(5);
    list.push_front(9);
    list.erase_after(list.head);
    std::cout << "list:";
    while (list.pop_front(out)) std::cout << ' ' << out;
    std::cout << '\n';

    DNode sentinel{0, nullptr, nullptr};
    DNode u{6, nullptr, nullptr};
    init_ring(&sentinel);
    insert_before(&sentinel, &u);
    unlink_node(&u);
    std::cout << "ring empty: " << (sentinel.next == &sentinel) << '\n';
    std::cout << "brackets: " << brackets_ok("[()()]") << '\n';
}
#endif
