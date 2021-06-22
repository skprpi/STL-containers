#include <iostream>
#include <memory>
#include <algorithm>


//Дз.
//Insert(по итератору, след элементом)
//Erase по итератору
//        Сделать указатели умными.
//push back, pop back
//        Push front
//        Pop front
//size() +
//front() +
//back() +
//empty() +
//clear() +
//reverse() 
//unique() +
//remove_if() *(если выйдет)
//
//
//Важно. Первыми сделать insert (+) и erase (+)
//        Остальное через них
//
//Также сделать Const iterator, и методы cbegin, cend


template<class T>
class List {
public:
    class Node;
    class iterator {
    public:
        friend List<T>;

        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = long long;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        explicit iterator(Node* other): now_node(other) {}

        T& operator*() {
            return now_node->data;
        }

        iterator& operator++() {
            now_node = now_node->next;
            return *this;
        }

        iterator& operator--() {
            now_node = now_node->prev;
            return *this;
        }

        iterator& operator+(long long step) {
            for (int i = 0; i < step; ++i) {
                now_node = now_node->next;
            }
            return *this;
        }

        bool operator==(const iterator& other) {
            return now_node == other.now_node;
        }

        bool operator!=(const iterator& other) {
            return now_node != other.now_node;
        }

        T& operator*() const {
            return now_node->data;
        }





        Node* now_node;
    };

    class Node{
    public:
        Node* next;
        Node* prev;
        T data;

        // ERROR!
        Node(): next(nullptr), prev(nullptr) {}

        explicit Node(Node* n1): prev(n1->prev), next(n1->next), data(n1->data) {}

        Node& operator=(const Node* n1) {
            prev = n1->prev;
            next = n1->next;
            data = n1->data;
            return *this;
        }

        Node(Node* prev, Node* next, T data): next(next), prev(prev), data(data) {}
    };

    iterator begin() {
        return iterator(begin_ptr);
    }

    iterator end() {
        return iterator(end_ptr);
    }


    void insert(iterator it, T data) {
        if (size_++ == 0) {
            begin_ptr = new Node(nullptr, end_ptr, data);
            end_ptr->prev = begin_ptr;
            return;
        }
        if (it.now_node == begin_ptr) {
            Node* new_node = new Node(nullptr, begin_ptr, data);
            begin_ptr->prev = new_node;
            begin_ptr = new_node;
            return;
        }

        Node* new_node = new Node(it.now_node->prev, it.now_node, data);
        it.now_node->prev->next = new_node;
        it.now_node->prev = new_node;
//        it.now_node->next->now_node.prev = new_node;

    }

    void erase(iterator it) {
        --size_;
        if (it.now_node == begin_ptr) {
            begin_ptr = begin_ptr->next;
            begin_ptr->prev = nullptr;
            delete it.now_node;
            return;
        }
        if (it.now_node == end_ptr) {
            end_ptr = end_ptr->prev;
            end_ptr->next = nullptr;
            delete it.now_node;
            return;
        }
        it.now_node->prev->next = it.now_node->next;
        it.now_node->next->prev = it.now_node->prev;
    }

    size_t size() const {
        return size_;
    }

    void unique() {
        auto b = iterator(begin_ptr);
        while (b.now_node != end_ptr) {
            while (b.now_node->data == b.now_node->next->data) {
                erase(b + 1);
            }
            ++b;
        }
    }

    void push_back(T val) {
        insert(end(), val);
    }

    void push_front(T val) {
        insert(begin(), val);
    }

    bool empty() {
        return size_ == 0;
    }

    void clear() {
        auto b = iterator(end_ptr);
        while (b.now_node != begin_ptr) {
            erase(end());
            b = iterator(end_ptr);
        }
        begin_ptr = new Node(nullptr, nullptr, 0);
        end_ptr = begin_ptr;
    }

    T& front() const {
        return begin_ptr->data;
    }

    T& back() const {
        return end_ptr->prev->data;
    }

    List(): begin_ptr(new Node()), size_(0), end_ptr(begin_ptr) {}

private:
    Node* begin_ptr;
    Node* end_ptr;
    size_t size_;
};


int main() {
    List<int> list;
    auto it = list.begin();
    list.insert(it, 100);
    int a = 2;
    it = list.begin();
    list.insert(it, a);
    list.insert(it, a*10);
    auto it2 = list.end();
    it = list.begin();

    for (int & i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    if (std::find(list.begin(), list.end(), 20) != list.end()) {
        std::cout << "Here1!" << std::endl;
    }

    if (std::find(list.begin(), list.end(), 101) != list.end()) {
        std::cout << "Here2!" << std::endl;
    }

    if (std::find(list.begin(), list.end(), 23) != list.end()) {
        std::cout << "Here3!" << std::endl;
    }

    list.erase(list.begin());


    for (int & i : list) {
        std::cout << i << " ";
    }


    list.erase(list.end());
    std::cout << std::endl;

    for (int & i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Before unique" << std::endl;
    list.insert(list.begin(), 20);
    list.insert(list.begin(), 20);
    list.insert(list.begin(), 30);
    list.insert(list.begin(), 30);
    list.insert(list.begin(), 10);
    list.insert(list.begin(), 10);
    list.insert(list.begin(), 10);
    list.insert(list.begin(), 10);
    list.insert(list.begin(), 10);
    for (int & i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "After unique" << std::endl;
    list.unique();
    for (int & i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;



    list.push_back(-1);
    list.push_front(-1);
    for (int & i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << list.front() << " " << list.back() << std::endl;

    list.clear();
    std::cout << "Cleaned" << std::endl;
    for (int & i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << list.empty() << std::endl;
    std::cout << list.size();
}
