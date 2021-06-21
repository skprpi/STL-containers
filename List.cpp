#include <iostream>
#include <memory>


//Дз.
//Insert(по итератору, след элементом)
//Erase по итератору
//        Сделать указатели умными.
//push back, pop back
//        Push front
//        Pop front
//size()
//front()
//back()
//empty()
//clear()
//reverse()
//unique()
//remove_if() *(если выйдет)
//
//
//Важно. Первыми сделать insert и erase
//        Остальное через них
//
//Также сделать Const iterator, и методы cbegin, cend


template<class T>
class List {
public:
    class Node;
    class iterator {
        friend List;
    public:
        T& operator*() {
            return now_node->data;
        }

        iterator& operator++() {
            now_node = now_node->next;
            return now_node;
        }

        iterator& operator--() {
            now_node = now_node->prev;
            return now_node;
        }

        bool operator==(const iterator& other) {
            return now_node == other.now_node;
        }

        bool operator!=(const iterator& other) {
            return now_node != other.now_node;
        }



    private:

        std::unique_ptr<Node> now_node;
    };

    class Node{
    public:
        std::weak_ptr<Node> next;
        std::weak_ptr<Node> prev;
        T data;

        // ERROR!
        Node(): next(nullptr), prev(nullptr) {}

        Node(std::weak_ptr<Node> prev, std::weak_ptr<Node> next, T& data): next(next), prev(prev), data(data) {}
    };


    void insert(iterator& it, T& data) {
        if (size_++ == 0) {
            begin_ptr = new Node(nullptr, end_ptr, data);
            end_ptr.prev = begin_ptr;
            return;
        }
        std::weak_ptr<Node> new_node = new Node(it.now_node, it.now_node.next, data);
        it.now_node.next = new_node;
        it.now_node.next.now_node.prev = new_node;
    }

    void erase(iterator& it) {
        --size_;
        if (it.now_node == begin_ptr) {
            it.now_node = it.now_node.next;
            return;
        }
        if (it.now_node == end_ptr) {
            it.now_node = it.now_node.prev;
            return;
        }
        it.now_node.prev.next = it.now_node.next;
        it.now_node.next.prev = it.now_node.prev;
    }

    size_t size() const {
        return size_;
    }

    // ERROR!
    List(): begin_ptr(new Node()), size_(0), end_ptr(begin_ptr) {}

private:
    std::weak_ptr<Node> begin_ptr;
    std::weak_ptr<Node> end_ptr;
    size_t size_;
};


int main() {
    List<int> list;
}






