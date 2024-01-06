/// wszystkie moje komentarze zaczynają się od "///"
/// przetestowałem na milionie losowych testów (dużych i małych) i wygląda na to że działa :) (+ kilka valgrindów)
/// zatem dalej już tylko uwagi do stylu
/// generalna uwaga: mało komentarzy, np. funkcje set_pom, query_pom są długie, przydałby się jakiś komentarz co one robią i ewentualnie drobne komentarze w środku
#include <vector>
#include <memory>
#include <climits>

class Node {
public:
    std::shared_ptr<Node> left, right;
    int value;

    Node(int val) : value(val) {}
};

std::vector<std::shared_ptr<Node>> roots;
const int MIN = INT_MIN;
const int MAX = INT_MAX;

std::shared_ptr<Node> descend_l(const std::shared_ptr<Node> &node) {
    if (node == nullptr) {
        return nullptr;
    }
    return node->left;
}

std::shared_ptr<Node> descend_r(const std::shared_ptr<Node> &node) {
    if (node == nullptr) {
        return nullptr;
    }
    return node->right;
}

long long int get_mid(long long int lo, long long int hi) {
    // dla border case gdy bierzemy srednia z dwoch kolejnych ujemnych liczb
    return lo +  (hi - lo) / 2; /// tu Ci się walnęła spacja za dużo (tak wiem drobnostka ale akurat się rzuciła mi w oczy to piszę (: )
}

/// raczej nie mieszamy języków w których nazywamy zmienne (np. set_pom - możnaby nazwać choćby _set albo set_help?)
void _set(int query_val, std::pair<int,int> query, std::pair<long long int,long long int> my_range, 
        const std::shared_ptr<Node> &node, const std::shared_ptr<Node> &old_node) {
    /// strasznie długa linijka z nagłówkiem funkcji, warto jakiś enter dać; PS long long int możesz pisać krócej long long (co imo nie odbija się źle na czytelności, a skraca trochę), ale tak też jest git ofc
    if(old_node != nullptr) {
        node->left = old_node->left;
        node->right = old_node->right;
        node->value = old_node->value;
    }
    
    if (query.first <= my_range.first && query.second >= my_range.second) {
        node->value = query_val;
        return;
    }
    if (query.first > my_range.second || query.second < my_range.first) {
        return;
    }

    long long int mid = get_mid(my_range.first, my_range.second);
    node->left = std::make_shared<Node>(-1); /// zamiast pisać wielokrotnie -1 warto zrobić stałą
    node->right = std::make_shared<Node>(-1);

    _set(query_val, query, {my_range.first, mid}, descend_l(node), descend_l(old_node));
    _set(query_val, query, {mid + 1, my_range.second}, descend_r(node), descend_r(old_node));
    node->value = std::max(node->left->value, node->right->value);
}

void set(int value, int lo, int hi) {
    roots.push_back(std::make_shared<Node>(-1));
    _set(value, {lo, hi}, {MIN, MAX}, roots.back(), roots.size() > 1 ? roots[roots.size() - 2] : nullptr);
}

int _query(std::pair<int,int> query, std::pair<long long int,long long int> my_range, const std::shared_ptr<Node> &node) {
    if (node == nullptr) {
        return -1;
    }
    if (query.first <= my_range.first && query.second >= my_range.second) {
        return node->value;
    }
    if (query.first > my_range.second || query.second < my_range.first) {
        return -1;
    }

    long long int mid = get_mid(my_range.first, my_range.second);
    return std::max(_query(query, {my_range.first, mid}, descend_l(node)), _query(query, {mid + 1, my_range.second}, descend_r(node))); /// tu też długa linijka, proponowałbym enter dać
}

int query(int lo, int hi, const std::shared_ptr<Node> &node) {
    return _query({lo, hi}, {MIN, MAX}, node);
}

void init(const std::vector<int> &seq) {
    for (size_t i = 0; i < seq.size(); i++) {
        set((int) i, seq[i], seq[i]);
    }
}

int prevInRange(int i, int lo, int hi) {
    return query(lo, hi, roots[i]);
}

void pushBack(int value) {
    set((int) roots.size(), value, value);
}

void done() {
    // gwarantuje zniszczenie bufora po wyjściu z done
    std::vector<std::shared_ptr<Node>>().swap(roots);
}