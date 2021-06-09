#include <iostream>
#include <memory>

using std::cout;

template <class T, size_t size>
class Array{
public:

    // copy constructor
    Array(): data_(new T[size]) {}


    Array(const Array<T, size>& data): Array() {
        for (int i = 0; i < size; i++) {
            data_[i] = data[i];
        }
    }

    const T& operator[] (size_t i) const {
        return data_[i];
    }

    T& operator[] (size_t i) {
        return data_[i];
    }

    Array& operator= (const Array<T, size>& arr) {
        if (&arr == this) {
            return *this;
        }
        Array<T, size>(arr).swap(*this);
    }

    void swap(Array<T, size>& arr) {
        std::swap(arr.data_, data_);
    }

    friend std::ostream& operator<< (std::ostream& out, const Array<T, size>& arr) {
        for (int i = 0; i < size; i++) {
            out << arr[i] << " ";
        }
        cout << "\n";
        return out;
    }

    friend std::istream& operator>> (std::istream& in, Array<T, size>& arr) {
        for (int i = 0; i < size; i++) {
            in >> arr[i];
        }
        cout << "\n";
        return in;
    }

    Array<T, size>& operator += (const Array<T, size>& arr) {
        for (int i = 0; i < size; ++i) {
            data_[i] += arr[i];
        }
        return *this;
    }

    // don't work
    Array<T, size>& operator -= (const Array<T, size>& arr) {
        for (int i = 0; i < size; ++i) {
            data_[i] -= arr[i];
        }
        return *this;
    }


    // postfix increment    something wrong !!! - have some warnings
    Array<T, size> operator++(int) {
        Array<T, size> res = *this;
        for (int i = 0; i < size; ++i) {
            data_[i] += 1;
        }
        return res;
    }

    // prefix increment
    Array<T, size>& operator++() {
        for (int i = 0; i < size; ++i) {
            data_[i] += 1;
        }
        return *this;
    }


    Array<T, size> operator--(int) {
        Array<T, size> res = *this;
        for (int i = 0; i < size; ++i) {
            data_[i] -= 1;
        }
        return res;
    }

    // prefix increment
    Array<T, size>& operator--() {
        for (int i = 0; i < size; ++i) {
            data_[i] -= 1;
        }
        return *this;
    }

    ~Array() = default;

private:
    std::unique_ptr<T[]> data_;
};

template <typename T, size_t size>
Array<T, size> operator-(const Array<T, size>& arr) {
    Array<T, size> tmp = Array<T, size>(arr);
    for (int i = 0; i < size; ++i) {
        tmp[i] *= -1;
    }
    return tmp;
}

template <typename T, size_t size>
Array<T, size> operator + (const Array<T, size>& arr1, const Array<T, size>& arr2) {
    Array<T, size> tmp = arr1;
    tmp += arr2;
    return tmp;
}

template <typename T, size_t size>
Array<T, size> operator - (const Array<T, size>& arr1, const Array<T, size>& arr2) {
    Array<T, size> tmp = arr1;
    tmp -= arr2;
    return tmp;
}


template <typename T, size_t size>
bool operator<(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return arr1[i] < arr2[i];
        }
    }
    return false;
}

template <typename T, size_t size>
bool operator>(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    return arr2 < arr1;
}

template <typename T, size_t size>
bool operator==(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    return !(arr2 < arr1) && !(arr1 < arr2);
}

template <typename T, size_t size>
bool operator!=(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    return !(arr1 == arr2);
}

template <typename T, size_t size>
bool operator<=(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    return (arr1 == arr2) || (arr1 < arr2);
}

template <typename T, size_t size>
bool operator>=(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    return (arr1 == arr2) || (arr1 > arr2);
}


template <typename T, size_t size>
T operator*(const Array<T, size>& arr1, const Array<T, size>& arr2)  {
    T res = 0;
    for (int i = 0; i < size; ++i) {
        res += arr1[i] * arr2[i];
    }
    return res;
}



int main() {
    Array<int, 4> arr1;
    arr1[0] = 100;
    arr1[1] = 3;
    arr1[2] = 12;
    arr1[3] = -15;
    std::cout << arr1;
    Array<int, 4> arr2 = arr1;
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
    cout << arr2 ++;

    cout << arr2 * arr1;

    Array<int, 4> arr3;
    std::cin >> arr3;
    cout << arr3;
}
