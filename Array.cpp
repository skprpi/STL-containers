#include <iostream>
#include <memory>
#include <cassert>

using std::cout;

template<class T, size_t size>
class StaticVector {
public:

    StaticVector() : data_(new T[size]) {}


    StaticVector(const StaticVector<T, size> &data) : StaticVector() {
        for (int i = 0; i < size; i++) {
            data_[i] = data[i];
        }
    }

    StaticVector &operator=(const StaticVector<T, size> &arr) {
        if (&arr == this) {
            return *this;
        }
        StaticVector<T, size>(arr).swap(*this);
    }

    ~StaticVector() = default;

    const T &operator[](size_t i) const {
        return data_[i];
    }

    T &operator[](size_t i) {
        return data_[i];
    }


    void swap(StaticVector<T, size> &arr) {
        std::swap(arr.data_, data_);
    }

    friend std::ostream &operator<<(std::ostream &out, const StaticVector<T, size> &arr) {
        for (int i = 0; i < size; i++) {
            out << arr[i] << " ";
        }
        out << std::endl;
        return out;
    }

    friend std::istream &operator>>(std::istream &in, StaticVector<T, size> &arr) {
        for (int i = 0; i < size; i++) {
            in >> arr[i];
        }
        return in;
    }

    StaticVector<T, size> &operator+=(const StaticVector<T, size> &arr) {
        for (int i = 0; i < size; ++i) {
            data_[i] += arr[i];
        }
        return *this;
    }

    // don't work
    StaticVector<T, size> &operator-=(const StaticVector<T, size> &arr) {
        for (int i = 0; i < size; ++i) {
            data_[i] -= arr[i];
        }
        return *this;
    }


    // postfix increment    something wrong !!! - have some warnings
    StaticVector<T, size> operator++(int) {
        StaticVector<T, size> res = *this;
        for (int i = 0; i < size; ++i) {
            data_[i] += 1;
        }
        return res;
    }

    // prefix increment
    StaticVector<T, size> &operator++() {
        for (int i = 0; i < size; ++i) {
            data_[i] += 1;
        }
        return *this;
    }


    StaticVector<T, size> operator--(int) {
        StaticVector<T, size> res = *this;
        for (int i = 0; i < size; ++i) {
            data_[i] -= 1;
        }
        return res;
    }

    // prefix increment
    StaticVector<T, size> &operator--() {
        for (int i = 0; i < size; ++i) {
            data_[i] -= 1;
        }
        return *this;
    }


private:
    std::unique_ptr<T[]> data_;
};

template<typename T, size_t size>
StaticVector<T, size> operator-(const StaticVector<T, size> &arr) {
    StaticVector<T, size> tmp = StaticVector<T, size>(arr);
    for (int i = 0; i < size; ++i) {
        tmp[i] *= -1;
    }
    return tmp;
}

template<typename T, size_t size>
StaticVector<T, size> operator+(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    StaticVector<T, size> tmp = arr1;
    tmp += arr2;
    return tmp;
}

template<typename T, size_t size>
StaticVector<T, size> operator-(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    StaticVector<T, size> tmp = arr1;
    tmp -= arr2;
    return tmp;
}


template<typename T, size_t size>
bool operator<(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    for (size_t i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return arr1[i] < arr2[i];
        }
    }
    return false;
}

template<typename T, size_t size>
bool operator>(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    return arr2 < arr1;
}

template<typename T, size_t size>
bool operator==(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    return !(arr2 < arr1) && !(arr1 < arr2);
}

template<typename T, size_t size>
bool operator!=(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    return !(arr1 == arr2);
}

template<typename T, size_t size>
bool operator<=(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    return !(arr1 > arr2);
}

template<typename T, size_t size>
bool operator>=(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    return !(arr1 < arr2);
}


template<typename T, size_t size>
T operator*(const StaticVector<T, size> &arr1, const StaticVector<T, size> &arr2) {
    T res = 0;
    for (int i = 0; i < size; ++i) {
        res += arr1[i] * arr2[i];
    }
    return res;
}


int main() {
    StaticVector<int, 4> arr1;
    arr1[0] = 100;
    arr1[1] = 3;
    arr1[2] = 12;
    arr1[3] = -15;
    std::cout << arr1;
    StaticVector<int, 4> arr2 = arr1;
    arr2[1] = 1;
    std::cout << arr2;

    if (arr2 > arr1) {
        cout << "ok";
    }
    arr2 = -arr1;
    cout << arr2;

    arr2 = arr2 + arr1;
    cout << arr2;
    cout << ++arr2;
    cout << arr2++;
    cout << arr2;
    cout << --arr2;
    cout << arr2--;
    cout << arr2++;

    cout << arr2 * arr1;

    StaticVector<int, 4> arr3;
    std::cin >> arr3;
    cout << arr3;
    return 0;
}
