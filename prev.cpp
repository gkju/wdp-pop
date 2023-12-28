#include <vector>
#include <memory>
#include <climits>

struct Node {
    int value;
    std::shared_ptr<Node> left, right;
};

std::vector<std::shared_ptr<Node>> roots;
const int MIN = INT_MIN;
const int MAX = INT_MAX;

std::shared_ptr<Node> descend_l(std::shared_ptr<Node> &node) {
    if (node == nullptr) {
        return nullptr;
    }
    return node->left;
}

std::shared_ptr<Node> descend_r(std::shared_ptr<Node> &node) {
    if (node == nullptr) {
        return nullptr;
    }
    return node->right;
}

void set_pom(int query_val, std::pair<int,int> query, std::pair<long long int,long long int> my_range, std::shared_ptr<Node> node, std::shared_ptr<Node> old_node) {
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
    long long int mid = (my_range.first + my_range.second) / 2;
    node->left = std::make_shared<Node>();
    node->right = std::make_shared<Node>();

    set_pom(query_val, query, {my_range.first, mid}, descend_l(node), descend_l(old_node));
    set_pom(query_val, query, {mid + 1, my_range.second}, descend_r(node), descend_r(old_node));
    node->value = std::max(node->left->value, node->right->value);
}

void set(int value, int lo, int hi) {
    roots.push_back(std::make_shared<Node>());
    set_pom(value, {lo, hi}, {MIN, MAX}, roots.back(), roots.size() > 1 ? roots[roots.size() - 2] : nullptr);
}

int query_pom(std::pair<int,int> query, std::pair<long long int,long long int> my_range, std::shared_ptr<Node> node) {
    if (node == nullptr) {
        return -1;
    }
    if (query.first <= my_range.first && query.second >= my_range.second) {
        return node->value;
    }
    if (query.first > my_range.second || query.second < my_range.first) {
        return -1;
    }
    long long int mid = (my_range.first + my_range.second) / 2;
    return std::max(query_pom(query, {my_range.first, mid}, descend_l(node)), query_pom(query, {mid + 1, my_range.second}, descend_r(node)));
}

int query(int lo, int hi, std::shared_ptr<Node> &node) {
    return query_pom({lo, hi}, {MIN, MAX}, node);
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